#version 330 core

const int MAX_LIGHTS = 4;
const int SPOT_LIGHT = 0;
const int DIR_LIGHT = 1;
const int POINT_LIGHT = 2;

uniform sampler2D texmap;

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

struct Light{
	int l_type;		//
	vec3 l_dir;	   // world space
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff; 
};
uniform Light lights[MAX_LIGHTS];
uniform int n_lights;

in Data {
	vec3 normal[MAX_LIGHTS];
	vec4 eye[MAX_LIGHTS];
	vec3 lightDir[MAX_LIGHTS];
} DataIn;

in vec2 tex_coord;
out vec4 colorOut;
uniform bool light_on;

void main() {
	int k;
	vec4 texel = texture(texmap, tex_coord);  // texel from lighwood.tga

	if(light_on){
		colorOut = vec4(0.0);
		for(k = 0; k < n_lights; k++){
			float intensity = 0.0; 
			vec4 spec = vec4(0.0);
			vec3 light_direction = vec3(0.0);
			
			if(lights[k].l_type == DIR_LIGHT){
				light_direction = lights[k].l_dir;
			}else {
				light_direction = normalize(DataIn.lightDir[k]);
			}
			
			vec3 n = normalize(DataIn.normal[k]);
			vec3 e = normalize(vec3(DataIn.eye[k]));
			vec3 h = vec3(0.0);
			
			if(lights[k].l_type == SPOT_LIGHT){
				
				vec3 sd = normalize(vec3(-lights[k].l_spotDir));	
				
				if (dot(sd,light_direction) > lights[k].l_spotCutOff) {
					
					intensity = max(dot(n,light_direction), 0.0);
					
					if (intensity > 0.0) {
						h = normalize(light_direction + e);
						float intSpec = max(dot(h,n), 0.0);
						spec = specular * pow(intSpec, shininess);
					}
				}
				
			}else {
				//POINT LIGHT
				if(lights[k].l_type == POINT_LIGHT){
					
					vec3 l = normalize(light_direction);
					intensity = max(dot(n,l), 0.0);

				}else if(lights[k].l_type == DIR_LIGHT) {
					
					intensity = max(dot(n,light_direction), 0.0);
					
				}
				if (intensity > 0.0) {
					vec3 h = normalize(light_direction + e);	
					float intSpec = max(dot(h,n), 0.0);
					spec = specular * pow(intSpec,shininess);
				}
			}
			colorOut = colorOut + max(intensity *  diffuse + spec, ambient);
		}
		
		colorOut /= n_lights;
		colorOut *= texel;
	}else {
		colorOut = ambient * texel;
	}

}

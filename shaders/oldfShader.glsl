#version 330 core

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

layout (std140) uniform Lights {
	int l_type;		//
	vec3 l_dir;	   // world space
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff; 
};

in Data {
	vec3 normal;
	vec4 eye;
	vec2 tex_coord;
	vec3 lightDir;
} DataIn;

out vec4 colorOut;
uniform bool light_on;

void main() {

	vec4 texel = texture(texmap, DataIn.tex_coord);  // texel from lighwood.tga

	if(light_on){
		float intensity = 0.0; 
		vec4 spec = vec4(0.0);
		vec3 light_direction = vec3(0.0);
		
		if(l_type == DIR_LIGHT){
			light_direction = l_dir;
		}else {
			light_direction = normalize(DataIn.lightDir);
		}
		
		vec3 n = normalize(DataIn.normal);
		vec3 e = normalize(vec3(DataIn.eye));
		vec3 h = vec3(0.0);
		
		if(l_type == SPOT_LIGHT){
			
			vec3 sd = normalize(vec3(-l_spotDir));	
			
			if (dot(sd,light_direction) > l_spotCutOff) {
				
				intensity = max(dot(n,light_direction), 0.0);
				
				if (intensity > 0.0) {
					h = normalize(light_direction + e);
					float intSpec = max(dot(h,n), 0.0);
					spec = specular * pow(intSpec, shininess);
				}
			}
			
		}else {

			if(l_type == POINT_LIGHT){
				
				vec3 l = normalize(light_direction);
				intensity = max(dot(n,l), 0.0);

			}else if(l_type == DIR_LIGHT) {
				
				intensity = max(dot(n,light_direction), 0.0);
				
			}
			// if the vertex is lit compute the specular color
			if (intensity > 0.0) {
				// compute the half vector
				vec3 h = normalize(light_direction + e);	
				// compute the specular term into spec
				float intSpec = max(dot(h,n), 0.0);
				spec = specular * pow(intSpec,shininess);
			}
		}
		

		colorOut = max(intensity *  diffuse + spec, ambient) * texel;
	}else {
		colorOut = ambient * texel;
	}

}

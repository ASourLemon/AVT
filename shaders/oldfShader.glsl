#version 330 core

const int MAX_SPOT_LIGHTS = 1;
const int MAX_DIR_LIGHTS = 1;
const int MAX_POINT_LIGHTS = 6;
const int MAX_LIGHTS = MAX_SPOT_LIGHTS + MAX_DIR_LIGHTS + MAX_POINT_LIGHTS;

out vec4 colorOut;

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

struct Spot_Light{
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff; 
};
uniform Spot_Light spot_lights[MAX_SPOT_LIGHTS];
uniform vec4 dir_lights[MAX_DIR_LIGHTS];
uniform vec4 point_lights[MAX_POINT_LIGHTS];


in Data {
	vec3 normal;
	vec4 eye;
	vec3 lightDir[MAX_SPOT_LIGHTS + MAX_POINT_LIGHTS];
} DataIn;

in vec2 tex_coord;
uniform sampler2D texmap;
uniform bool isDay;
uniform bool lampOn;
uniform float time;
uniform bool tex_moving;
int index=0;


vec4 processFog(){
	vec4 fogColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);
	float distance = distance(vec4(0.0), DataIn.eye);
	float density = 0.1f;
	//float fogAmount = exp(-distance * density);
	float fogAmount = -distance * density;
	
	return mix(fogColor, colorOut, fogAmount);
}

vec4 processSpotLights(){
	vec4 finalColor =  vec4(0.0);

	int l;
	float intensity;
	vec4 spec;
	vec3 ld, sd;
	
	for(l = 0; l < MAX_SPOT_LIGHTS; l++){
		intensity = 0.0;
		spec = vec4(0.0);
		ld = normalize(DataIn.lightDir[index]);
		sd = normalize(vec3(-spot_lights[l].l_spotDir));	

		// inside the cone?
		if (dot(sd,ld) > spot_lights[l].l_spotCutOff) {
			float distance = length(DataIn.lightDir[index]);
			vec3 n = normalize(DataIn.normal);
			
			intensity = max(dot(n,ld), 0.0);
			//if(distance > 10.0)
				float a, b, c;		//attenuation = 1/(a + bd + cd2) 
				a = 0.7;
				b = 0;
				c = 0.07;
				float attenuation = (1.0 / (a 
										+ (b * distance) 
										+ (c * distance * distance)));
					
				intensity *= attenuation;						//FIXME: Maybe? This is a simple attenuation
			//
			
			if (intensity > 0.0) {
				vec3 eye = normalize(vec3(DataIn.eye));
				vec3 h = normalize(ld + eye);
				float intSpec = max(dot(h,n), 0.0);
				spec = specular * pow(intSpec, shininess);

			}

		}
		finalColor = finalColor + max(intensity * diffuse + spec, 0);	
		index++;
	}
	
	return finalColor;
}
vec4 processDirLights(){
	int k;
	vec4 finalColor = vec4(0.0);
	
	for(k = 0; k < MAX_DIR_LIGHTS; k++){
		// set the specular term to black
		vec4 spec = vec4(0.0);

		// normalize both input vectors
		vec3 n = normalize(DataIn.normal);
		vec3 e = normalize(vec3(DataIn.eye));

		float intensity = max(dot(n,vec3(dir_lights[k])), 0.0);

		// if the vertex is lit compute the specular color
		if (intensity > 0.0) {
			// compute the half vector
			vec3 h = normalize(vec3(dir_lights[k]) + e);	
			// compute the specular term into spec
			float intSpec = max(dot(h,n), 0.0);
			spec = specular * pow(intSpec,shininess);
		}
		//vec4 color =  max(intensity *  diffuse, ambient);
		//colorOut = texture(texUnit, DataIn.texCoord) * color + spec;
		finalColor = finalColor + max(intensity *  diffuse + spec, 0);
	}
	
	return finalColor;
}
vec4 processPointLights(){
	int k;
	vec4 finalColor = vec4(0.0);
	vec4 spec;
	vec3 n;
	vec3 l;
	vec3 e;
	float intensity;

	for(k = 0; k < MAX_POINT_LIGHTS; k++){
		
		float distance = length(DataIn.lightDir[index]);
		float a, b, c;		//attenuation = 1/(a + bd + cd2) 
		a = 0.7;
		b = 0;
		c = 0.07;
		float attenuation;

		if(distance>10) {
			attenuation = 0;
		}else {
			attenuation = (1.0 / 
							  (a 
							+ (b * distance) 
							+ (c * distance * distance)));
		}
		spec = vec4(0.0);
		n = normalize(DataIn.normal);
		l = normalize(DataIn.lightDir[index]);
		e = normalize(vec3(DataIn.eye));
		intensity = max(dot(n,l), 0.0);
		intensity *=attenuation;
		if (intensity > 0.0) {

			vec3 h = normalize(l + e);
			float intSpec = max(dot(h,n), 0.0);
			spec = specular * pow(intSpec, shininess);
		}
			
		finalColor = finalColor + max(intensity * diffuse + spec, 0);
		index++;
	}
	
	
	return finalColor;
}

void main() {
	vec4 texel;

	if(tex_moving)
		texel = texture(texmap, vec2(tex_coord.x + sin(tex_coord.y * 60.0 + time * 2.0) / 30.0, 1.0 - tex_coord.y));  // texel from lighwood.tga
	else
		texel = texture(texmap, tex_coord);
		 
	if(isDay){
		
		colorOut = processDirLights();

	}else {		
			
		colorOut = processSpotLights();	
		if(lampOn){
			colorOut += processPointLights();

		}
	}	
	colorOut = max(colorOut, ambient * 0.5);	
	colorOut *= texel;	
	//colorOut = processFog();

}

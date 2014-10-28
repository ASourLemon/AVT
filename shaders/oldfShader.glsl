#version 330 core

const int MAX_SPOT_LIGHTS = 1;
const int MAX_DIR_LIGHTS = 1;
const int MAX_POINT_LIGHTS = 1;
const int MAX_LIGHTS = MAX_SPOT_LIGHTS + MAX_DIR_LIGHTS + MAX_POINT_LIGHTS;

const int SPOT_LIGHT = 0;
const int DIR_LIGHT = 1;
const int POINT_LIGHT = 2;

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
	vec3 normal[MAX_LIGHTS];
	vec4 eye[MAX_LIGHTS];
	vec3 lightDir[MAX_SPOT_LIGHTS + MAX_POINT_LIGHTS];
} DataIn;

in vec2 tex_coord;
uniform sampler2D texmap;
uniform bool isDay;

int index=0;

vec4 processSpotLights(){
	vec4 finalColor =  vec4(0.0);;
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
			
			vec3 n = normalize(DataIn.normal[index]);
			
			intensity = max(dot(n,ld), 0.0);
			
			if (intensity > 0.0) {
				vec3 eye = normalize(vec3(DataIn.eye[index]));
				vec3 h = normalize(ld + eye);
				float intSpec = max(dot(h,n), 0.0);
				spec = specular * pow(intSpec, shininess);

			}

		}
		finalColor = finalColor + max(intensity * diffuse + spec, ambient);	
		index++;
	}
	
	return finalColor/MAX_SPOT_LIGHTS;
}
vec4 processDirLights(){
	int k;
	vec4 finalColor = vec4(0.0);
	
	for(k = 0; k < MAX_DIR_LIGHTS; k++){
		// set the specular term to black
		vec4 spec = vec4(0.0);

		// normalize both input vectors
		vec3 n = normalize(DataIn.normal[index]);
		vec3 e = normalize(vec3(DataIn.eye[index]));

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
		finalColor = finalColor + max(intensity *  diffuse + spec, ambient);
		index++;
	}
	
	return finalColor/MAX_DIR_LIGHTS;
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
		spec = vec4(0.0);
		n = normalize(DataIn.normal[index]);
		l = normalize(DataIn.lightDir[index]);
		e = normalize(vec3(DataIn.eye[index]));
		intensity = max(dot(n,l), 0.0);
		if (intensity > 0.0) {

			vec3 h = normalize(l + e);
			float intSpec = max(dot(h,n), 0.0);
			spec = specular * pow(intSpec, shininess);
		}
			
		finalColor = finalColor + max(intensity * diffuse + spec, ambient);
		index++;
	}
	
	
	return finalColor/MAX_POINT_LIGHTS;
}

void main() {

	vec4 texel = texture(texmap, tex_coord);  // texel from lighwood.tga
	if(isDay){
		
		colorOut = processDirLights();

	}else {		
			
		colorOut = processSpotLights();	
		colorOut += processPointLights();
		colorOut /= 2; //for a better effect
	}
	colorOut *= texel;
}

#version 330

const int max_lights = 5;
out vec4 colorOut;

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

uniform int n_lights;
uniform vec4 l_spotDir[max_lights];
uniform float l_spotCutOff[max_lights];

in	vec3 normal_a[max_lights];
in	vec2 texCoord[max_lights];
in	vec3 eye[max_lights];
in	vec3 lightDir[max_lights];


void main() {
	int l;
	float intensity;
	vec4 spec;
	vec3 ld, sd;
	colorOut = vec4(0.0);
	for(l = 0; l < n_lights; l++){
		intensity = 0.0;
		spec = vec4(0.0);
		ld = normalize(lightDir[l]);
		sd = normalize(vec3(-l_spotDir[l]));	

			// inside the cone?
		if (dot(sd,ld) > l_spotCutOff[l]) {
			
			vec3 n = normalize(normal_a[l]);
			intensity = max(dot(n,ld), 0.0);
			
			if (intensity > 0.0) {
				vec3 eye = normalize(eye[l]);
				vec3 h = normalize(ld + eye);
				float intSpec = max(dot(h,n), 0.0);
				spec = specular * pow(intSpec, shininess);
			}
		}
		colorOut = colorOut + max(intensity * diffuse + spec * 4, ambient);
		
	}
	//float debug = 1.0f;
	//debug += l_spotDir[0].x;
	colorOut /= n_lights;

}

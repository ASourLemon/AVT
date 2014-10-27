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

in vec3 normal_a[max_lights];
in vec3 eye[max_lights];
in vec3 lightDir[max_lights];

void main() {
	int k;
	
	vec4 spec;
	vec3 n;
	vec3 l;
	vec3 e;
	float intensity;
	colorOut = vec4(0.0);
	
	for(k = 0; k < n_lights; k++){
		spec = vec4(0.0);
		n = normalize(normal_a[k]);
		l = normalize(lightDir[k]);
		e = normalize(eye[k]);
		intensity = max(dot(n,l), 0.0);
		if (intensity > 0.0) {

			vec3 h = normalize(l + e);
			float intSpec = max(dot(h,n), 0.0);
			spec = specular * pow(intSpec, shininess);
		}
		
		colorOut = colorOut + max(intensity * diffuse + spec * 4, ambient);
	}
	colorOut /= n_lights;
//	colorOut = vec4(n,1.0);
}

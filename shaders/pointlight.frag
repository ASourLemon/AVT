#version 330 core

out vec4 colorOut;

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

in vec3 normal_a;
in vec3 eye;
in vec3 lightDir;

void main() {
	
	vec4 spec;
	vec3 n;
	vec3 l;
	vec3 e;
	float intensity;
	colorOut = vec4(0.0);
	
	spec = vec4(0.0);
	n = normalize(normal_a);
	l = normalize(lightDir);
	e = normalize(eye);
	intensity = max(dot(n,l), 0.0);
	if (intensity > 0.0) {

		vec3 h = normalize(l + e);
		float intSpec = max(dot(h,n), 0.0);
		spec = specular * pow(intSpec, shininess);
	}
		
	colorOut = colorOut + max(intensity * diffuse + spec * 4, ambient);
//	colorOut = vec4(n,1.0);
}

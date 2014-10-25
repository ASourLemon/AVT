#version 330

const int max_lights = 5;

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

uniform int n_lights;
uniform vec4 l_pos[max_lights], l_spotDir[max_lights];
uniform float l_spotCutOff[max_lights];

in vec4 position;
in vec3 normal;

out vec3 normal_a[max_lights];
out	vec2 texCoord[max_lights];
out	vec3 eye[max_lights];
out	vec3 lightDir[max_lights];

void main () {
	int l;
	
	for(l = 0; l < n_lights; l++){
		vec4 pos = m_viewModel * position;
		normal_a[l] = normalize(m_normal * normal);
		lightDir[l] = vec3(l_pos[l]-pos);
		eye[l] = vec3(-pos);
	}

	gl_Position = m_pvm * position;	
}

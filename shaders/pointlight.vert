#version 330

const int max_lights = 1;

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

layout (std140) uniform Lights {
	vec4 l_pos;
};

in vec4 position;
in vec3 normal;

out vec3 normal_a;
out vec3 eye;
out vec3 lightDir;

void main () {
	vec4 pos = m_viewModel * position;

	normal_a = normalize(m_normal * normal);
	lightDir = vec3(l_pos - pos);
	eye =  vec3(-pos);
	
	gl_Position = m_pvm * position;	
}

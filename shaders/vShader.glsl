#version 330 core

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};
in vec4 in_position;
in vec4 texCoord;
in vec4 in_color;

out vec4 color;

void main()
{
	color = in_color;
	gl_Position = m_pvm * in_position;
}

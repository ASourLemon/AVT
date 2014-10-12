#version 330

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

in vec4 position;
in vec4 texCoord;

out Data {
	vec4 texCoord;
} DataOut;

void main()
{
	DataOut.texCoord = texCoord;
	gl_Position = m_pvm * position ;
} 


#version 330 core

in vec4 in_Position;
uniform mat4 Matrix;
out vec4 color;

void main()
{
color = in_Position;
	gl_Position = Matrix * in_Position;
}

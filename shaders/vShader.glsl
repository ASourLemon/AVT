
#version 330 core

in vec4 in_Position;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec4 color;

void main()
{
	color = in_Position;
	gl_Position = P * V * M * in_Position;
}

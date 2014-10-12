#version 330 core

in vec4 in_Position;			
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
out vec4 color;

void main(void)
{
	color = in_Position;
	gl_Position = P * V * M * in_Position;

}
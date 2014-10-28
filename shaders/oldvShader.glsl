#version 330 core

const int MAX_LIGHTS = 2;

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

layout (std140) uniform Lights {
	vec3 l_dir;	   // world space
	vec4 l_pos;
	bool isPoint;
};

in vec4 position;	// local space
in vec3 normal;		// local space
in vec4 texCoord;

// the data to be sent to the fragment shader
out Data {
	vec3 normal;
	vec4 eye;
	vec2 tex_coord;
	vec3 lightDir;
} DataOut;

uniform bool light_on;

void main () {
	DataOut.tex_coord = texCoord.st;
	if(light_on){
		vec4 pos = m_viewModel * position;
		DataOut.eye = vec4(-pos);
		DataOut.normal = normalize(m_normal * normal);

		DataOut.lightDir = vec3(l_pos - pos);
	}

	gl_Position = m_pvm * position;	
}

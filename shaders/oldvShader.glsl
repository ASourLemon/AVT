#version 330 core

const int MAX_LIGHTS = 5;
const int SPOT_LIGHT = 0;
const int DIR_LIGHT = 1;
const int POINT_LIGHT = 2;

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

struct Light{
	int l_type;		//
	vec3 l_dir;	   // world space
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff; 
};
uniform Light lights[MAX_LIGHTS];
uniform int n_lights;

in vec4 position;	// local space
in vec3 normal;		// local space
in vec4 texCoord;

// the data to be sent to the fragment shader
out Data {
	vec3 normal[MAX_LIGHTS];
	vec4 eye[MAX_LIGHTS];
	vec3 lightDir[MAX_LIGHTS];
} DataOut;

out vec2 tex_coord;
uniform bool light_on;

void main () {
	int k;
	tex_coord = texCoord.st;
	if(light_on){
		for(k = 0; k < n_lights; k++){
			vec4 pos = m_viewModel * position;
			DataOut.eye[k] = vec4(-pos);
			DataOut.normal[k] = normalize(m_normal * normal);
			DataOut.lightDir[k] = vec3(lights[k].l_pos - pos);
		}

	}

	gl_Position = m_pvm * position;	
}

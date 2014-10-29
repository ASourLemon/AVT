#version 330 core

const int MAX_SPOT_LIGHTS = 1;
const int MAX_DIR_LIGHTS = 1;
const int MAX_POINT_LIGHTS = 6;
const int MAX_LIGHTS = MAX_SPOT_LIGHTS + MAX_DIR_LIGHTS + MAX_POINT_LIGHTS;

layout (std140) uniform Matrices {
	mat4 m_pvm;
	mat4 m_viewModel;
	mat3 m_normal;
};

struct Spot_Light{
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff; 
};
uniform Spot_Light spot_lights[MAX_SPOT_LIGHTS];
uniform vec4 dir_lights[MAX_DIR_LIGHTS];
uniform vec4 point_lights[MAX_POINT_LIGHTS];



// the data to be sent to the fragment shader
out Data {
	vec3 normal;
	vec4 eye;
	vec3 lightDir[MAX_SPOT_LIGHTS + MAX_POINT_LIGHTS];
} DataOut;

in vec4 position;	// local space
in vec3 normal;		// local space
in vec4 texCoord;

out vec2 tex_coord;
uniform bool isDay;
uniform bool lampOn;

void main () {
	int k, i = 0;
	vec4 pos = m_viewModel * position;
	DataOut.eye = vec4(-pos);
	DataOut.normal = normalize(m_normal * normal);
	tex_coord = texCoord.st;
	
	if(!isDay){
		
		//process spot_lights
		for(k = 0; k < MAX_SPOT_LIGHTS; k++){
			vec4 pos = m_viewModel * position;
			DataOut.lightDir[i] = vec3(spot_lights[k].l_pos - pos);			
			i++;
		}
		if(lampOn){
			//process point_lights
			for(k = 0; k < MAX_POINT_LIGHTS; k++){

				DataOut.lightDir[i] = vec3(point_lights[k] - pos);
				i++;
			}	
		}
	}
	gl_Position = m_pvm * position;	
}

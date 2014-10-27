#include "../include/lightManager.h"

const char* l_posNames[] = { "l_pos[0]", "l_pos[1]", "l_pos[2]" , "l_pos[3]", "l_pos[4]", "l_pos[5]", "l_pos[6]", "l_pos[7]" };
const char* l_spotDirNames[] = { "l_spotDir[0]", "l_spotDir[1]", "l_spotDir[2]" , "l_spotDir[3]", "l_spotDir[4]", "l_spotDir[5]", "l_spotDir[6]", "l_spotDir[7]" };
const char* l_spotCutNames[] = { "l_spotCutOff[0]", "l_spotCutOff[1]", "l_spotCutOff[2]" , "l_spotCutOff[3]", "l_spotCutOff[4]", "l_spotCutOff[5]", "l_spotCutOff[6]", "l_spotCutOff[7]" };


LightManager::LightManager(){
	this->lights_on = false;
	this->n_lights = 0;
}

void LightManager::init(VSShaderLib* shader){
	this->shader = shader;
}


void ClearColor(Light* l){
	float whiteColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	memcpy(l->l_amb, whiteColor, sizeof(float) * 4);
	memcpy(l->l_dif, whiteColor, sizeof(float) * 4);
	memcpy(l->l_spec, whiteColor, sizeof(float) * 4);
}

//Add Spotlight
void LightManager::addLight(float l_spot[4]){
	Light l;
	
	l.l_type = l_spot[3];	//if(0)-directional_light elseif(1)-pointlight
	memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	
	ClearColor(&l);
	lights[n_lights++] = l;
}
void LightManager::addLight(float l_spot[4], float l_dir[4], float l_cut){
	Light l;
	
	l.l_type = SPOT_LIGHT;
	
	memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	memcpy(l.l_dir, l_dir, sizeof(float) * 4);
	l.l_spot_cut = l_cut;
	
	ClearColor(&l);
	lights[n_lights++] = l;
}

void LightManager::setLightColor(int light_num, float amb[4], float dif[4], float spec[4]){
	memcpy(lights[light_num].l_amb, amb, sizeof(float) * 4);
	memcpy(lights[light_num].l_dif, dif, sizeof(float) * 4);
	memcpy(lights[light_num].l_spec, spec, sizeof(float) * 4);
}


void LightManager::drawLight(VSMathLib* core){
	if(lights_on){
		int l;
		float res[4];
		for(l = 0; l < n_lights; ++l){
			core->multMatrixPoint(VSMathLib::VIEW, lights[l].l_pos,res);   //lightPos definido em World Coord so is converted to eye space
			//send spotPos
			glProgramUniform4fv(shader->getProgramIndex(),
					glGetUniformLocation(shader->getProgramIndex(), l_posNames[l]),
					1,
					res);
			
			//send spotDir
			glProgramUniform4fv(shader->getProgramIndex(),
					glGetUniformLocation(shader->getProgramIndex(), l_spotDirNames[l]),
					1,
					lights[l].l_dir);
					
			//send l_spot_cut
			glProgramUniform1fv(shader->getProgramIndex(), 
					glGetUniformLocation(shader->getProgramIndex(), l_spotCutNames[l]), 
					1, 
					&lights[l].l_spot_cut);
			
		}
	}
}


void LightManager::lightsOff(){
	lights_on = false;
}
void LightManager::lightsOn(){
	lights_on = true;
}

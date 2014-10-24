#include "../include/lightManager.h"


LightManager::LightManager(){
	this->lights_on = false;
	this->n_lights = 0;
}

void LightManager::init(){
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
	lights[n_lights++] = &l;
}
void LightManager::addLight(float l_spot[4], float l_dir[4], float l_cut){
	Light l;
	
	l.l_type = SPOT_LIGHT;
	
	memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	memcpy(l.l_dir, l_dir, sizeof(float) * 4);
	l.l_spot_cut = l_cut;
	
	ClearColor(&l);
	lights[n_lights++] = &l;
}

void LightManager::setLightColor(int light_num, float amb[4], float dif[4], float spec[4]){
	memcpy(lights[light_num]->l_amb, amb, sizeof(float) * 4);
	memcpy(lights[light_num]->l_dif, dif, sizeof(float) * 4);
	memcpy(lights[light_num]->l_spec, spec, sizeof(float) * 4);
}


void LightManager::drawLight(){
	
}
void LightManager::lightsOff(){
	
}
void LightManager::lightsOn(){
	
}

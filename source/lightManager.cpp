#include "../include/lightManager.h"

const char* spotLIndex[] = { "spot_lights[0].", "spot_lights[1].", "spot_lights[2]." , "spot_lights[3].", "spot_lights[4].", "spot_lights[5].", "spot_lights[6].", "spot_lights[7]." };
const char* dirLIndex[] = { "dir_lights[0]", "dir_lights[1]", "dir_lights[2]" , "dir_lights[3]", "dir_lights[4]", "dir_lights[5]", "dir_lights[6]", "dir_lights[7]" };
const char* pointLIndex[] = { "point_lights[0]", "point_lights[1]", "point_lights[2]" , "point_lights[3]", "point_lights[4]", "point_lights[5]", "point_lights[6]", "point_lights[7]" };

const char* l_pos_glslname = {"l_pos"};
const char* l_spotDir_glslname = {"l_spotDir"};
const char* l_spotCutOff_glslname = {"l_spotCutOff"};

LightManager::LightManager() :  n_lights(0), n_spots(0), n_dirs(0), n_points(0), lights_on(false){
	
}

void LightManager::init(VSShaderLib* shader, domain::Frog* frog){
	this->shader = shader;
	this->frog = frog;
}


void ClearColor(Light* l){
	float whiteColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	memcpy(l->l_amb, whiteColor, sizeof(float) * 4);
	memcpy(l->l_dif, whiteColor, sizeof(float) * 4);
	memcpy(l->l_spec, whiteColor, sizeof(float) * 4);
}

void LightManager::addLight(float l_spot[4]){
	Light l;
	if(l_spot[3] == 1.0){
		l.l_type = POINT_LIGHT;	
		memcpy(l.l_pos, l_spot, sizeof(float) * 4);
	}else {
		l.l_type = DIR_LIGHT;
		memcpy(l.l_dir, l_spot, sizeof(float) * 4);
	}
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

void LightManager::addLight(float l_dir[4], float l_cut){
	Light l;
	l.l_type = MINING_HELM_SPOT;
	
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


void LightManager::processSpotLight(int n, Light* l, VSMathLib* core){
	float res[4];
	char pos_name[30];
	strcpy(pos_name, spotLIndex[n]);
	strcat(pos_name,l_pos_glslname);	
	int pos_loc = glGetUniformLocation(shader->getProgramIndex(), pos_name);
	core->multMatrixPoint(VSMathLib::VIEW, l->l_pos, res);
	glUniform4f(pos_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG name:%s, pos:%d\n", pos_name, pos_loc);
	
	char spot_name[30];
	strcpy(spot_name, spotLIndex[n]);
	strcat(spot_name,l_spotDir_glslname);	
	int spot_loc = glGetUniformLocation(shader->getProgramIndex(), spot_name);	
	core->multMatrixPoint(VSMathLib::VIEW, l->l_dir, res);
	glUniform4f(spot_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG name:%s, pos:%d\n", spot_name, spot_loc);
	
	char cut_name[30];
	strcpy(cut_name, spotLIndex[n]);
	strcat(cut_name,l_spotCutOff_glslname);	
	int cut_loc = glGetUniformLocation(shader->getProgramIndex(), cut_name);
	glUniform1f(cut_loc, l->l_spot_cut);
	//printf("#########DEBUG name:%s, pos:%d\n", cut_name, cut_loc);
}
void LightManager::processDirLight(int n, Light* l, VSMathLib* core){

	float res[4];
	core->multMatrixPoint(VSMathLib::VIEW, l->l_dir, res);
	
	char dir_name[30];
	strcpy(dir_name, dirLIndex[n]);
	int pos_loc = glGetUniformLocation(shader->getProgramIndex(), dir_name);	
	glUniform4f(pos_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG name:%s, pos:%d\n", dir_name, pos_loc);
	
}
void LightManager::processPointLight(int n, Light* l, VSMathLib* core){
	float res[4];
	core->multMatrixPoint(VSMathLib::VIEW, l->l_pos, res);
	
	int pos_loc = glGetUniformLocation(shader->getProgramIndex(), pointLIndex[n]);	
	glUniform4f(pos_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG name:%s, pos:%d\n", pointLIndex[n], pos_loc);
}
void LightManager::processMiningLight(int n, Light* l, VSMathLib* core){
	float pos[4];
	float res[4];
	pos[0] = frog->getX();
	pos[1] = frog->getY()+1;
	pos[2] = frog->getZ();
	pos[3] = 1.0f;
	
	int f_dir = frog->getDirection();
	float dir[4];
	if(f_dir == DIR_FRONT){
		dir[0] = 0.0;
		dir[2] = 1.0;
	}else if(f_dir == DIR_LEFT) {
		dir[0] = 1.0;
		dir[2] = 0.0;
	}else if(f_dir == DIR_RIGHT){
		dir[0] = -1.0;
		dir[2] = 0.0;
	}else {
		dir[0] = 0.0;
		dir[2] = -1.0;

	}
	dir[1] = -0.2;	
	dir[3] = 0.0;
	float cut = 0.9;
	char pos_name[30];
	strcpy(pos_name, spotLIndex[n]);
	strcat(pos_name,l_pos_glslname);	
	int pos_loc = glGetUniformLocation(shader->getProgramIndex(), pos_name);	
	core->multMatrixPoint(VSMathLib::VIEW, pos, res);
	glUniform4f(pos_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG Mining name:%s, pos:%d\n",pos_name, pos_loc);
	
	char spot_name[30];
	strcpy(spot_name, spotLIndex[n]);
	strcat(spot_name,l_spotDir_glslname);	
	int spot_loc = glGetUniformLocation(shader->getProgramIndex(), spot_name);
	core->multMatrixPoint(VSMathLib::VIEW, dir, res);	
	glUniform4f(spot_loc, res[0], res[1], res[2], res[3]);
	//printf("#########DEBUG Mining name:%s, pos:%d\n",spot_name, spot_loc);
	
	char cut_name[30];
	strcpy(cut_name, spotLIndex[n]);
	strcat(cut_name,l_spotCutOff_glslname);	
	int cut_loc = glGetUniformLocation(shader->getProgramIndex(), cut_name);
	glUniform1f(cut_loc, cut);
}

void LightManager::drawLight(VSMathLib* core){
	if(lights_on){
		int l, nd = 0, np = 0, ns = 0;
		Light light;
		for(l = 0; l < n_lights; ++l){
			light = lights[l];
			switch(light.l_type){
				case(SPOT_LIGHT):{
					processSpotLight(ns, &light, core);
					ns++;
					//printf("Processing spot light\n");
					break;
				}
				case(DIR_LIGHT):{
					processDirLight(nd, &light, core);
					nd++;
					//printf("Processing dir light\n");
					break;	
				}
				case(POINT_LIGHT):{
					processPointLight(np, &light, core);
					np++;
					//printf("Processing point light\n");
					break;
				}
				case(MINING_HELM_SPOT):{
					processMiningLight(ns, &light, core);
					ns++;
					//printf("Processing mining light\n");
					break;
				}
				default:{
					printf("Light type:%d is not supported:(\n", light.l_type);
				}
			}
			
		}
	}
}

void LightManager::lightsOff(){
	lights_on = false;
}
void LightManager::lightsOn(){
	lights_on = true;
}

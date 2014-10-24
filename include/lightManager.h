#ifndef INCLUDE_LIGHTMANAGER_H_
#define INCLUDE_LIGHTMANAGER_H_

#include <string.h>

#define MAX_LIGHTS 8

#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2




struct Light{
	int l_type;				//one of the above types
	
	float l_amb[4];			//light color
	float l_dif[4];
	float l_spec[4];
		
	float l_pos[4];			//used for pointlight cone vertex; 		used for spotlight; 
	float l_dir[4];			//used for pointlight cone basecenter;	used for directionallight;	
	float l_spot_cut;		//used for pointlight cone cut;


};


class LightManager {
private:
	int n_lights;
	bool lights_on;
	Light* lights[MAX_LIGHTS];


public:
	LightManager();
	void init();
	void addLight(float l_spot[4]);
	void addLight(float l_spot[4], float l_dir[4], float l_cut);
	void setLightColor(int light_num, float amb[4], float dif[4], float spec[4]);
	void drawLight();
	void lightsOff();
	void lightsOn();
};


#endif

#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include "drawable.h"

#define MAP0_W 20
#define MAP0_H 32
#define WATER_SPEED 0.3f

namespace domain {



class Map : public Drawable {
private:
	static float roadAmb[4];
	static float roadDif[4];
	static float roadSpec[4];
	static float roadShininess;

	static float grassAmb[4];
	static float grassDif[4];
	static float grassSpec[4];
	static float grassShininess;

	static float waterAmb[4];
	static float waterDif[4];
	static float waterSpec[4];
	static float waterShininess;	
	
	static float wallAmb[4];
	static float wallDif[4];
	static float wallSpec[4];
	static float wallShininess;
	
	static float cubeAmb[4];
	static float cubeDif[4];
	static float cubeSpec[4];
	static float cubeShininess;

protected:
	VSResSurfRevLib body;
	VSResSurfRevLib water;
	float deltaWater;
	bool goingLeft;
	BoxAABB *win_box;
	float win_x;
	float win_y;
	float win_z;


public:
	Map();
	~Map();
	void draw(VSMathLib* core);
	void tick();
	int getMaplimit(){return MAP0_W;}
	BoxAABB* getWinBox(){ return win_box;}
};

}

#endif

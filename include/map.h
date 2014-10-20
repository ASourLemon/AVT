#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include "drawable.h"

#define MAP0_W 20
#define MAP0_H 32
#define WALL_CHAR 'X'
#define WATER_SPEED 0.3f

namespace domain {



class Map : public Drawable {
private:
	VSResSurfRevLib body;
	VSResSurfRevLib water;
	float deltaWater;
	bool goingLeft;


public:
	Map();
	~Map();
	void draw(VSMathLib* core);
	void tick();
	int getMaplimit(){return MAP0_W;}
};

}

#endif

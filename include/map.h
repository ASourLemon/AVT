#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include "drawable.h"

#define MAP0_W 10
#define MAP0_H 16
#define WALL_CHAR 'X'

const char map_0[] =
{		"XXXXXXXXXX"
		"XXXXXXXXXX"
		"XXXXXXXXXX"
		"          "
		"          "
		"          "
		"XXXXXXXXXX"
		"          "
		"          "
		"          "
		"XXXXXXXXXX"
		"XXXXXXXXXX"
		"XXXXXXXXXX"
};

namespace domain {



class Map : public Drawable {
private:
	VSResSurfRevLib body;
	VSResSurfRevLib water;
	float deltaWater;
	bool goingLeft;


public:
	Map();
	void draw(VSMathLib* core);

};

}

#endif

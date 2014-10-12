#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include "drawable.h"

#define MAP0_W 10
#define MAP0_H 15
#define WALL_CHAR 'X'

const char map_0[] =
{		"XXXXXXXXXX"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"X        X"
		"XXXXXXXXXX"
};

namespace domain {



class Map : public Drawable {
private:
	VSResSurfRevLib body;


public:
	Map();
	void draw(VSMathLib* core);

};

}

#endif

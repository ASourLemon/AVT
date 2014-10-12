#ifndef INCLUDE_DRAWABLE_H_
#define INCLUDE_DRAWABLE_H_

#include "vsMathLib.h"
#include "vsResSurfRevLib.h"

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

namespace domain {

class Drawable {

protected:
	float _x, _y, _z;


public:

	virtual void draw(VSMathLib* core) = 0;

};
}

#endif

#ifndef INCLUDE_DRAWABLE_H_
#define INCLUDE_DRAWABLE_H_

#include "vsMathLib.h"
#include "vsResSurfRevLib.h"

namespace domain {

class Drawable {

protected:
	float _x, _y, _z;

public:

	enum Direction{
			FRONT,
			BACK,
			LEFT,
			RIGHT,
			UP,
			DOWN,
	};

	virtual void draw(VSMathLib* core) = 0;

};
}

#endif

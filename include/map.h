#ifndef INCLUDE_MAP_H_
#define INCLUDE_MAP_H_

#include "drawable.h"

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

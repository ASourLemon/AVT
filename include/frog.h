#ifndef INCLUDE_FROG_H_
#define INCLUDE_FROG_H_

#include "drawable.h"

#define FROG_RADIOS 3.0f
#define FROG_DIVISIONS 10.0f

namespace domain {

class Frog : public Drawable{

private:
	float x, y, z;
	VSResSurfRevLib body, head, eye;
	bool created;


public:
	Frog(float x, float y, float z);
	void draw(VSMathLib* core);
	void move(int d);
	void tick();
	inline float getX(){return x;}
	inline float getY(){return y;}
	inline float getZ(){return z;}
};

}

#endif

#ifndef INCLUDE_GRASS_H_
#define INCLUDE_GRASS_H_

#include "drawable.h"

namespace domain {

class Grass: public Drawable {
private:
	static float cubeAmb[4];
	static float cubeDif[4];
	static float cubeSpec[4];
	static float cubeShininess;
	float _x;
	float _z;
	bool cross;

protected:
	VSResSurfRevLib rectangle;

public:
	Grass(float x, float z, bool c);
	~Grass();
	void draw(VSMathLib* core, VSShaderLib* shader);
	void tick();
	inline bool getCross(){return cross;}
};

}

#endif
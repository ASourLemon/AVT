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
	/*Materials*/
	float bodyAmbient[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
	float bodyDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float bodySpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	float headAmbient[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
	float headDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float headSpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	float eyeAmbient[4] = { 0.5f, 0.2f, 0.2f, 1.0f };
	float eyeDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float eyeSpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };


public:
	Frog(float x, float y, float z);
	void draw(VSMathLib* core);
	void move(int d);
	inline float getX(){return x;}
	inline float getY(){return y;}
	inline float getZ(){return z;}
};

}

#endif

#ifndef INCLUDE_LAMP_H_
#define INCLUDE_LAMP_H_

#include "drawable.h"

#define LAMP_DIVISIONS 10

namespace domain {
class Lamp: public Drawable {
private:
	static float lampShadeAmb[4];
	static float lampShadeDif[4];
	static float lampShadeSpec[4];
	static float lampShadeShininess;

	static float supportAmb[4];
	static float supportDif[4];
	static float supportSpec[4];
	static float supportShininess;

protected:
	VSResSurfRevLib lampShade, support;
	float x;
	float y;
	float z;
	bool created;

public:
	Lamp(float x, float y, float z);
	~Lamp();
	void draw(VSMathLib* core);
	void tick();

};

}
#endif

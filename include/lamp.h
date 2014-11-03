#ifndef INCLUDE_LAMP_H_
#define INCLUDE_LAMP_H_

#include "drawable.h"
#include "BoxAABB.h"

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
	//Reflections color
	static float RlampShadeAmb[4];
	static float RlampShadeDif[4];
	static float RlampShadeSpec[4];
	static float RlampShadeShininess;

	static float RsupportAmb[4];
	static float RsupportDif[4];
	static float RsupportSpec[4];
	static float RsupportShininess;
	BoxAABB *AABB;

protected:
	VSResSurfRevLib lampShade, support;
	float x;
	float y;
	float z;
	bool created;
	bool reflection;

public:
	Lamp(float x, float y, float z, bool reflect);
	~Lamp();
	void draw(VSMathLib* core);
	void tick();
	BoxAABB * get_AABB(){ return AABB; }

};

}
#endif

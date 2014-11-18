#ifndef INCLUDE_TURTLE_H_
#define INCLUDE_TURTLE_H_

#include "DynamicObject.h"

#define TURTLE_DIVISIONS 10

namespace domain {
class Turtle: public DynamicObject {
private:
	static float bodyAmb[4];
	static float bodyDif[4];
	static float bodySpec[4];
	static float bodyShininess;

	static float headAmb[4];
	static float headDif[4];
	static float headSpec[4];
	static float headShininess;

	static float legAmb[4];
	static float legDif[4];
	static float legSpec[4];
	static float legShininess;

protected:
	VSResSurfRevLib head, body, leg;
	bool created;
	BoxAABB *body_box;

public:
	Turtle(Vec3 position, Vec3 initSpeed);
	~Turtle();
	void draw(VSMathLib* core, VSShaderLib* shader);
	inline BoxAABB * get_AABB(){ return body_box;}
};

}
#endif

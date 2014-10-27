#ifndef INCLUDE_TURTLE_H_
#define INCLUDE_TURTLE_H_

#include "drawable.h"

#define TURTLE_DIVISIONS 10

namespace domain {
class Turtle: public Drawable {
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
	float x;
	float y;
	float z;
	float speed;
	int direction;
	bool created;

public:
	Turtle(float x, float y, float z, int direction, float velocity);
	~Turtle();
	void draw(VSMathLib* core);
	void tick();

};

}
#endif

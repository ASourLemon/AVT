#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

#include "drawable.h"

namespace domain {
class Car: public Drawable {
private:
	std::list<VSResSurfRevLib> components;
	VSResSurfRevLib body;
	VSResSurfRevLib tire;
	float x;
	float y;
	float z;
	float speed;
	int direction;
	bool created;

public:
	Car(float x, float y, float z, int direction, float velocity);
	~Car();
	void draw(VSMathLib* core);
	void tick();

};

}
#endif

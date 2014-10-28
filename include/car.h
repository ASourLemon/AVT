#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

#include "drawable.h"
#include "BoxAABB.h"

namespace domain {
class Car: public Drawable {
private:
	static float driverAmb[4];
	static float driverDif[4];
	static float driverSpec[4];
	static float driverShininess;

	static float loadAmb[4];
	static float loadDif[4];
	static float loadSpec[4];
	static float loadShininess;

	static float tireAmb[4];
	static float tireDif[4];
	static float tireSpec[4];
	static float tireShininess;
	BoxAABB *AABB;

protected:
	std::list<VSResSurfRevLib> components;
	VSResSurfRevLib driver;
	VSResSurfRevLib tire;
	float _x;
	float _y;
	float _z;
	float speed;
	int direction;
	bool created;
	

public:
	Car(float x, float y, float z, int direction, float velocity);
	~Car();
	void draw(VSMathLib* core);
	void tick();
	BoxAABB * get_AABB(){return AABB;}

};

}
#endif

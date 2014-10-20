#ifndef INCLUDE_FROG_H_
#define INCLUDE_FROG_H_

#include "drawable.h"
#include <GL/freeglut.h>
#include <iostream>

#define FROG_RADIOS 3.0f
#define FROG_DIVISIONS 10.0f

namespace domain {

class Frog : public Drawable{

private:
	VSResSurfRevLib body, head, eye;
	bool created;
	int t1, t2, t3, t4, deltaT; //tempos para movimento
	float x, y, z, speed;
	int direction;
	int map_limit;


public:
	Frog(float x, float y, float z, float speed);
	~Frog();
	void draw(VSMathLib* core);
	void move(int d);
	void tick();
	inline float getX(){return x;}
	inline float getY(){return y;}
	inline float getZ(){return z;}
	inline void setT1(int i){t1 = i;}
	inline void setT2(int i){t2 = i;}
	inline void setT3(int i){t3 = i;}
	inline void setT4(int i){t4 = i;}
	inline void setMaplimit(int i){map_limit = i;}
	//void setT2(int i){t2 = i;}
	//void setT3(int i){t3 = i;}
	//void setT4(int i){t4 = i;}
};

}

#endif

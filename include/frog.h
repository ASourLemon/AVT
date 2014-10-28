#ifndef INCLUDE_FROG_H_
#define INCLUDE_FROG_H_

#include "drawable.h"
#include "BoxSphere.h"
#include <GL/freeglut.h>
#include <iostream>

#define FROG_RADIOS 3.0f
#define FROG_DIVISIONS 10.0f

namespace domain {

class Frog : public Drawable{
	
private:
	static float bodyAmbient[4];
	static float bodyDiffuse[4];
	static float bodySpec[4];
	static float bodyShininess;

	static float headAmbient[4];
	static float headDiffuse[4];
	static float headSpec[4];
	static float headShininess;

	static float eyeAmbient[4];
	static float eyeDiffuse[4];
	static float eyeSpec[4];
	static float eyeShininess;
	BoxSphere *Sphere;
	
protected:
	VSResSurfRevLib body, head, eye;
	bool created;
	int t1, t2, t3, t4, deltaT; //tempos para movimento
	float _x, _y, _z, speed;
	int direction;
	int map_limit;
	

public:
	Frog(float x, float y, float z, float speed);
	~Frog();
	void draw(VSMathLib* core);
	void move(int d);
	void tick();
	inline float getX(){return _x;}
	inline float getY(){return _y;}
	inline float getZ(){return _z;}
	inline void setX(float i){_x = i;}
	inline void setY(float i){_y = i;}
	inline void setZ(float i){_z = i;}
	inline void setT1(int i){t1 = i;}
	inline void setT2(int i){t2 = i;}
	inline void setT3(int i){t3 = i;}
	inline void setT4(int i){t4 = i;}
	inline void setMaplimit(int i){map_limit = i;}

	BoxSphere * get_Sphere(){return Sphere;}
};

}

#endif

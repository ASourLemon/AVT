#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include "drawable.h"

namespace domain {

class Tree: public Drawable {
private:
	static float cubeAmb[4];
	static float cubeDif[4];
	static float cubeSpec[4];
	static float cubeShininess;
	float _x;
	float _z;

protected:
	VSResSurfRevLib rectangle;

public:
	Tree(float x, float z);
	~Tree();
	void draw(VSMathLib* core, VSShaderLib* shader);
	void tick();
};

}

#endif

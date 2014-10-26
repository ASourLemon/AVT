#include "BoxAABB.h"


namespace domain {

	BoxAABB::BoxAABB(float *x, float *y, float xmin, float ymin, float xmax, float ymax)
	: x(x), y(y), _xmin(xmin), _ymin(ymin), _xmax(xmax), _ymax(ymax){
 
 
	}

	BoxAABB::~BoxAABB(){}
}
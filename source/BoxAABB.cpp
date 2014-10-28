#include "../include/BoxAABB.h"


namespace domain {

	BoxAABB::BoxAABB(float *x, float *y, float *z, float xmin, float xmax, float ymin,  float ymax, float zmin, float zmax)
	:  _x(x), _y(y), _z(z), _xmin(xmin),  _xmax(xmax), _ymin(ymin), _ymax(ymax), _zmin(zmin), _zmax(zmax){
 
	}

	BoxAABB::~BoxAABB(){}
}
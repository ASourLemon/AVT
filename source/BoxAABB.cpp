#include "../include/BoxAABB.h"


namespace domain {

	BoxAABB::BoxAABB(float *center, float xmin, float xmax, float ymin,  float ymax, float zmin, float zmax)
	:  _xmin(xmin),  _xmax(xmax), _ymin(ymin), _ymax(ymax), _zmin(zmin), _zmax(zmax){
 
		for(int i = 0; i<3; i++){
			float a = center[i];
			_center[i] = a;
		}
	}

	BoxAABB::~BoxAABB(){}
}
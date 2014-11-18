#include "../include/BoxAABB.h"


namespace domain {

	BoxAABB::BoxAABB(Vec3 *center, float x_size, float y_size, float z_size)
		: _center(center), _x_size(x_size), _y_size(y_size), _z_size(z_size){

	}

	BoxAABB::~BoxAABB(){}
}
#include "../include/BoxSphere.h"

namespace domain{

	BoxSphere::BoxSphere(float center[3], float raio) : _raio(raio){

		for(int i = 0; i<3; i++)
			_center[i] = center[i];

	}

	BoxSphere::~BoxSphere(){}
}
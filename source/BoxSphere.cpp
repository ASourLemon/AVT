#include "../include/BoxSphere.h"

namespace domain{

	BoxSphere::BoxSphere(float raio, float *x, float *y) : _raio(raio), raio2(_raio*_raio), x(x), y(y){
 

	}

	BoxSphere::~BoxSphere(){}
}
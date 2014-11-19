#include "../include/camera.h"
#include <stdlib.h>

namespace domain {
	Camera::Camera() {	}

	Camera::~Camera() {
		delete pos;
		delete up;
		delete at;
	}

	float* Camera::getPos() {
		float *res = (float *) malloc(3*sizeof(float));

		res[0] = pos[0];
		res[1] = pos[1];
		res[2] = pos[2];

		return res;
	}
	float* Camera::getAtVector() {
		float *res = (float *) malloc(3*sizeof(float));

		res[0] = at[0];
		res[1] = at[1];
		res[2] = at[2];

		return res;
	}

} /* namespace domain */

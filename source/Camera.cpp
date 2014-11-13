#include "../include/camera.h"
#include <stdlib.h>

namespace domain {
	Camera::Camera(float pos[3], float up[3], float at[3], float near, float far) {
		memcpy(this->pos, pos, 3*sizeof(float));
		memcpy(this->up, up, 3*sizeof(float));
		memcpy(this->at, at, 3*sizeof(float));
		this->nearVal = near;
		this->farVal = far;
	}

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

#include "../include/camera.h"

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

} /* namespace domain */

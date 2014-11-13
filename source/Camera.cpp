#include "../include/camera.h"

namespace domain {
	Camera::Camera(float pos[3], float up[3], float at[3], float near, float far) {
		memcpy(this->pos, pos, 3);
		memcpy(this->up, up, 3);
		memcpy(this->at, at, 3);
		this->near = near;
		this->far = far;
	}

	Camera::~Camera() {
		delete pos;
		delete up;
		delete at;
	}

} /* namespace domain */

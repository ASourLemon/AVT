#include "../include/TopPerspectiveCamera.h"
#include "../include/game.h"
#include "../include/vsMathLib.h"

namespace domain {
	TopPerspectiveCamera *TopPerspectiveCamera::_instance = 0;

	TopPerspectiveCamera::TopPerspectiveCamera() {
		pos[0] = 10.0f;
		pos[1] = 10.0f;
		pos[2] = 15.0f;
		at[0] = 10.0f;
		at[1] = 0.0f;
		at[2] = 15.0f;
		up[0] = 0.0f;
		up[1] = 0.0f;
		up[2] = 1.0f;
	}

	TopPerspectiveCamera *TopPerspectiveCamera::getInstance() {
		if (_instance == 0) {
			_instance = new TopPerspectiveCamera();
		}
		return _instance;
	}

	TopPerspectiveCamera::~TopPerspectiveCamera() {
	}

	void TopPerspectiveCamera::update() {
		// Empty on purpose - Fixed camera
	}

	void TopPerspectiveCamera::load() {
		VSMathLib::getInstance()->lookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	}
} /* namespace domain */

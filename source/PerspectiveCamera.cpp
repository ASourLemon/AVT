#include "../include/PerspectiveCamera.h"
#include "../include/game.h"
#include "../include/VSMathLib.h"

namespace domain {

	PerspectiveCamera::PerspectiveCamera(float pos[3],
		float up[3],
		float at[3],
		float nearVal,
		float farVal,
		float fovy,
		float ratio) : Camera(pos, up, at, nearVal, farVal) {
		this->ratio = ratio;
		this->fovy = fovy;
	}

	PerspectiveCamera::~PerspectiveCamera() {
	}

	void PerspectiveCamera::update() {
		pos[0] = Game::getInstance()->getFrogX();
		pos[1] = Game::getInstance()->getFrogY();
		pos[2] = Game::getInstance()->getFrogZ();
	}

	void PerspectiveCamera::load() {
		VSMathLib::getInstance()->lookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	}
} /* namespace domain */
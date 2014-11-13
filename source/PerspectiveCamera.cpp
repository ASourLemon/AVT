#include "../include/PerspectiveCamera.h"
#include "../include/game.h"
#include "../include/vsMathLib.h"

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
		pos[1] = Game::getInstance()->getFrogY()+1.0;
		pos[2] = Game::getInstance()->getFrogZ()-1.0;
		at[0] = Game::getInstance()->getFrogX();
		at[1] = Game::getInstance()->getFrogY()+0.5;
		at[2] = Game::getInstance()->getFrogZ()+5.0;
	}

	void PerspectiveCamera::load() {
		VSMathLib::getInstance()->lookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	}
} /* namespace domain */

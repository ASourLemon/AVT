#include "../include/FrogPerspectiveCamera.h"
#include "../include/game.h"
#include "../include/vsMathLib.h"

namespace domain {
	FrogPerspectiveCamera *FrogPerspectiveCamera::_instance = 0;

	FrogPerspectiveCamera::FrogPerspectiveCamera() {
		up[0] = 0.0f;
		up[1] = 1.0f;
		up[2] = 0.0f;
		update();
	}

	FrogPerspectiveCamera *FrogPerspectiveCamera::getInstance() {
		if (_instance == 0) {
			_instance = new FrogPerspectiveCamera();
		}
		return _instance;
	}

	FrogPerspectiveCamera::~FrogPerspectiveCamera() {
	}

	void FrogPerspectiveCamera::update() {
		pos[0] = Game::getInstance()->getFrogX();
		pos[1] = Game::getInstance()->getFrogY()+1.0;
		pos[2] = Game::getInstance()->getFrogZ()-1.0;
		at[0] = Game::getInstance()->getFrogX();
		at[1] = Game::getInstance()->getFrogY()+0.5;
		at[2] = Game::getInstance()->getFrogZ()+5.0;
	}

	void FrogPerspectiveCamera::load() {
		VSMathLib::getInstance()->lookAt(pos[0], pos[1], pos[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	}
} /* namespace domain */

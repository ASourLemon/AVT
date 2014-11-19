#include "../include/DynamicObject.h"

#define LEFT_X_LIMIT 23.0f
#define RIGHT_X_LIMIT -7.0f

namespace domain {
	void DynamicObject::update(float time) {
		_nTicks++;
		const int FIFTEEN_SECONDS_PASSED = 15 * 60;
		if (_nTicks == FIFTEEN_SECONDS_PASSED) {
			increaseSpeed();
			_nTicks = 0;
		}

		_position = _position + _speed*time;

		int r = rand() % 5;
		if (_position.getX() >= LEFT_X_LIMIT) {
			_position = Vec3(RIGHT_X_LIMIT + r, _position.getY(), _position.getZ());
		}
		else if (_position.getX() <= RIGHT_X_LIMIT) {
			_position = Vec3(LEFT_X_LIMIT - r, _position.getY(), _position.getZ());
		}
	}


	void DynamicObject::resetSpeed() {
		_speed = _initSpeed;
	}

	void DynamicObject::increaseSpeed() {
		const float SPEED_INCREMENT = 1.75f;

		_speed = _initSpeed * SPEED_INCREMENT;
	}

	Vec3 DynamicObject::getSpeed() {
		return Vec3(_speed);
	}

} // namespace domain

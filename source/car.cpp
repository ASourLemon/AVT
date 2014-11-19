#include "../include/car.h"

namespace domain {

float Car::driverAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
float Car::driverDif[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
float Car::driverSpec[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
float Car::driverShininess = 100;

float Car::loadAmb[4] = { 0.4f, 0.1f, 0.1f, 1.0f };
float Car::loadDif[4] = { 0.5f, 0.3f, 0.3f, 1.0f };
float Car::loadSpec[4] = { 0.6f, 0.4f, 0.4f, 1.0f };
float Car::loadShininess = 10;

float Car::tireAmb[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
float Car::tireDif[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
float Car::tireSpec[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
float Car::tireShininess = 100;


Car::Car(Vec3 position, Vec3 initSpeed) : created(false) {
	_position = position;
	_initSpeed = initSpeed;
	_speed = initSpeed;

	load.createCube(1);
	load.setMaterialBlockName("Materials");
	load.setColor(VSResourceLib::DIFFUSE, loadDif);
	load.setColor(VSResourceLib::AMBIENT, loadAmb);
	load.setColor(VSResourceLib::SPECULAR, loadSpec);
	load.setColor(VSResourceLib::SHININESS, &loadShininess);

	driver.createCube(1.0f);
	driver.setMaterialBlockName("Materials");
	driver.setColor(VSResourceLib::DIFFUSE, driverDif);
	driver.setColor(VSResourceLib::AMBIENT, driverAmb);
	driver.setColor(VSResourceLib::SPECULAR, driverSpec);
	driver.setColor(VSResourceLib::SHININESS, &driverShininess);

	tire.createCylinder(0.2f, 0.4f, 20);
	tire.setMaterialBlockName("Materials");
	tire.setColor(VSResourceLib::SPECULAR, tireSpec);
	tire.setColor(VSResourceLib::DIFFUSE, tireDif);
	tire.setColor(VSResourceLib::AMBIENT, tireAmb);
	tire.setColor(VSResourceLib::SHININESS, &tireShininess);

	AABB = new BoxAABB(&_position, CAR_SIZE_X, CAR_SIZE_Y, CAR_SIZE_Z);
}

Car::~Car() {
	delete AABB;
}

void Car::draw(VSMathLib* core, VSShaderLib* shader) {
	float _x = _position.getX();
	float _y = _position.getY();
	float _z = _position.getZ();

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_x, _y, _z);

	const bool isHeadingLeft = _speed.getX() > 0;
	if (isHeadingLeft) {
		core->rotate(180.0f, 0.0f, 1.0f, 0.0f);
	}

	core->pushMatrix(VSMathLib::MODEL);
	core->scale(4.0f, 1.0f, 1.0f);
	core->translate(-0.5f, -0.5f, -0.5f);
	load.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(- 2.0f - 0.35f, 0.0f, 0.0f);
	core->scale(0.7f, 0.7f, 0.9f);
	core->translate(-0.5f, -0.5f, -0.5f);
	driver.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(1.5f, -0.2f, -0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.7f, -0.2f, -0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.5f, -0.2f, -0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-0.7f, -0.2f, -0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(1.5f, -0.2f, 0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.7f, -0.2f, 0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.5f, -0.2f, 0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-0.7f, -0.2f, 0.51f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->popMatrix(VSMathLib::MODEL);

}

} /* namespace domain */

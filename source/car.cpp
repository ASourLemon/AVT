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


Car::Car(float x, float y, float z, int direction, float velocity) :
		_x(x), _y(y), _z(z), speed(velocity), direction(direction), created(false) {

	VSResSurfRevLib load;
	load.createCube(1);

	load.setMaterialBlockName("Materials");
	load.setColor(VSResourceLib::DIFFUSE, loadDif);
	load.setColor(VSResourceLib::AMBIENT, loadAmb);
	load.setColor(VSResourceLib::SPECULAR, loadSpec);
	load.setColor(VSResourceLib::SHININESS, &loadShininess);

	components.push_front(load);

	//float center[] = { this->x, this->y, this->z};
	AABB = new BoxAABB(&_x, &_y, &_z, 0.05f, 2.35f, 0.01f, 0.01f, 0.01f, 0.01f);
}

Car::~Car() {
	delete AABB;
}

void Car::draw(VSMathLib* core, VSShaderLib* shader) {

	std::list<VSResSurfRevLib>::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++) {
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(_x, _y, _z);
		core->scale(3.0f, 1.0f, 1.0f);
		iter->render();
		core->popMatrix(VSMathLib::MODEL);
	}

	if (!created) {
		driver.createCube(1.0f);
	}

	driver.setMaterialBlockName("Materials");
	driver.setColor(VSResourceLib::DIFFUSE, driverDif);
	driver.setColor(VSResourceLib::AMBIENT, driverAmb);
	driver.setColor(VSResourceLib::SPECULAR, driverSpec);
	driver.setColor(VSResourceLib::SHININESS, &driverShininess);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x - 0.7f, _y, _z);
	else
		core->translate(_x + 3.0f, _y, _z);
	core->scale(0.7f, 0.7f, 0.9f);
	driver.render();
	core->popMatrix(VSMathLib::MODEL);

	tire.setMaterialBlockName("Materials");
	tire.setColor(VSResourceLib::SPECULAR, tireSpec);
	tire.setColor(VSResourceLib::DIFFUSE, tireDif);
	tire.setColor(VSResourceLib::AMBIENT, tireAmb);
	tire.setColor(VSResourceLib::SHININESS, &tireShininess);
	//pneus - 1

	if (!created) {
		tire.createCylinder(0.2f, 0.4f, 20);
		created = true;
	}

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 1.6f, _y, _z + 0.15f);
	else
		core->translate(_x + 0.7f, _y, _z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);
	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 2.3f, _y, _z + 0.15f);
	else
		core->translate(_x + 1.4f, _y, _z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 1.6f, _y, _z + 0.85f);
	else
		core->translate(_x + 0.7f, _y, _z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);
	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 2.3f, _y, _z + 0.85f);
	else
		core->translate(_x + 1.4f, _y, _z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 0.1f, _y, _z + 0.15f);
	else
		core->translate(_x + 2.7f, _y, _z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(_x + 0.1f, _y, _z + 0.85f);
	else
		core->translate(_x + 2.7f, _y, _z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

}

void Car::tick() {
	this->second_in_game += 0.01;	//After 100 calls, 1 second
	if(second_in_game > 15.0){
		speed += 0.5f;
		second_in_game = 0.0;
	}
	
	int r = rand() % 5;
	float d = speed * 0.1;
	if (direction == DIR_LEFT) {
		if (this->_x >= LEFT_X_LIMIT) {
			this->_x = RIGHT_X_LIMIT - r;
		}
		this->_x += d;
	} else if (direction == DIR_RIGHT) {
		if (this->_x <= RIGHT_X_LIMIT) {
			this->_x = LEFT_X_LIMIT + r;
		}
		this->_x -= d;
	}

}

} /* namespace domain */

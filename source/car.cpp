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
		x(x), y(y), z(z), direction(direction), speed(velocity) {
	created = false;
	VSResSurfRevLib load;
	load.createCube(1);

	load.setMaterialBlockName("Materials");
	load.setColor(VSResourceLib::DIFFUSE, loadDif);
	load.setColor(VSResourceLib::AMBIENT, loadAmb);
	load.setColor(VSResourceLib::SPECULAR, loadSpec);
	load.setColor(VSResourceLib::SHININESS, &loadShininess);

	components.push_front(load);

	float center[] = { this->x, this->y, this->z};
	AABB = new BoxAABB(center, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f, 2.5f);
}

Car::~Car() {
	delete AABB;
}

void Car::draw(VSMathLib* core) {

	std::list<VSResSurfRevLib>::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++) {
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
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
		core->translate(x - 0.7f, y, z);
	else
		core->translate(x + 3.0f, y, z);
	core->scale(0.7f, 0.7f, 0.9f);
	driver.render();
	core->popMatrix(VSMathLib::MODEL);

	/*core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x - 0.7f, y, z);
	else
		core->translate(x , y, z);
	core->scale(5.0f, 1.0f, 1.0f);
	driver.render();
	core->popMatrix(VSMathLib::MODEL);*/

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
		core->translate(x + 1.6f, y, z + 0.15f);
	else
		core->translate(x + 0.7f, y, z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);
	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x + 2.3f, y, z + 0.15f);
	else
		core->translate(x + 1.4f, y, z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x + 1.6f, y, z + 0.85f);
	else
		core->translate(x + 0.7f, y, z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);
	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x + 2.3f, y, z + 0.85f);
	else
		core->translate(x + 1.4f, y, z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x + 0.1f, y, z + 0.15f);
	else
		core->translate(x + 2.7f, y, z + 0.15f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	if (direction == DIR_RIGHT)
		core->translate(x + 0.1f, y, z + 0.85f);
	else
		core->translate(x + 2.7f, y, z + 0.85f);
	core->rotate(90, 1, 0, 0);
	tire.render();
	core->popMatrix(VSMathLib::MODEL);

}

void Car::tick() {
	this->second_in_game += 0.01;	//After 100 calls, 1 second
	int r = rand() % 5;
	float d = speed * 0.1;
	if (direction == DIR_LEFT) {
		if (this->x >= LEFT_X_LIMIT) {
			this->x = RIGHT_X_LIMIT - r;
		}
		this->x += d;
	} else if (direction == DIR_RIGHT) {
		if (this->x <= RIGHT_X_LIMIT) {
			this->x = LEFT_X_LIMIT + r;
		}
		this->x -= d;
	}

}

} /* namespace domain */

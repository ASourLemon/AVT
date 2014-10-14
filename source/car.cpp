#include "../include/car.h"

namespace domain {

	Car::Car(float x, float y, float z, int direction, float velocity) : x(x), y(y), z(z), direction(direction), velocity(velocity){
		created = false;
	}

	void Car::draw(VSMathLib* core){

		if (!created) {
			body.createCube(1.0f);
		}

		body.setMaterialBlockName("Materials");
		float f[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, f);
		float f2[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f2);


		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
		core->scale(3.0f, 1.0f, 1.0f);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


		if (!created) {
			body.createCube(1.0f);
			created = true;
		}

		body.setMaterialBlockName("Materials");
		float f3[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, f3);
		float f4[4] = { 0.8f, 0.0f, 0.0f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f4);


		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x + 3.0f, y, z);
		core->scale(0.7f, 0.7f, 0.9f);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


	}

	void Car::tick(){
		if(this->x >= LEFT_X_LIMIT){
			this->x = RIGHT_X_LIMIT;
		}
		float d = velocity * 0.1;
		if(direction == DIR_LEFT){
			this->x += d;
		}


	}

} /* namespace domain */

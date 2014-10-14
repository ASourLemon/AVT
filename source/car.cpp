#include "../include/car.h"

namespace domain {

	Car::Car(float x, float y, float z) : x(x), y(y), z(z) {
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
		body.setColor(VSResourceLib::AMBIENT, f2);


		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x + 3.0f, y, z);
		core->scale(0.7f, 0.7f, 0.9f);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


	}

	void Car::tick(){
		//TODO: Implement my movement, please!
	}

} /* namespace domain */

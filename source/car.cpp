#include "../include/car.h"

namespace domain {

	Car::Car(float x, float y, float z) : x(x), y(y), z(z) {
	}

	void Car::draw(VSMathLib* core){
		
		body.createCube(1.0f);

		body.setMaterialBlockName("Materials");
		float f[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, f);
		float f2[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f2);


		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
		core->scale(3.0, 1.0, 1.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


		body.createCube(1.0f);
		body.setColor(VSResourceLib::AMBIENT, f2);


		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x+3, y, z);
		core->scale(0.7, 0.7, 0.9);
		body.render();
		core->popMatrix(VSMathLib::MODEL);
	}

} /* namespace domain */

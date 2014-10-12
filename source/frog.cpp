#include "../include/frog.h"

namespace domain{


	Frog::Frog(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
		created = false;
		body.setMaterialBlockName("Materials");
		float f[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, f);
		float f2[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f2);
	}

	void Frog::draw(VSMathLib* core){
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
		core->rotate(180, 0,1,0);
		core->scale(0.4, 0.4, 0.4);

		body.render();
		//corpo
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			body.createSphere(2.2, FROG_DIVISIONS);
		}
		core->scale(1.0, 0.8, 1.0);
		core->rotate(35.0, 1.0, 0.0, 0.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);
		//cabe�a
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			body.createSphere(1.5, 9.0);
		}
		core->translate(0.0, 1.6, -1.8);
		core->scale(0.8, 0.8, 1.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);
		//olhos
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			body.createSphere(0.6, 9.0);
		}
		core->translate(0.4, 2.8, -1.5);
		core->scale(0.7, 1.0, 0.7);
		body.render();
		core->popMatrix(VSMathLib::MODEL);
		//olhos
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			body.createSphere(0.6, 9.0);
		}
		core->translate(-0.4, 2.8, -1.5);
		core->scale(0.7, 1.0, 0.7);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		core->popMatrix(VSMathLib::MODEL);
	}

	void Frog::move(int d){
		switch(d){

		case(FRONT):{
			this->z++;
			break;
		}

		case(BACK):{
			this->z--;
			break;
		}

		case(LEFT):{
			this->x++;
			break;
		}

		case(RIGHT):{
			this->x--;
			break;
		}

		}
	}

}

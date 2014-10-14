#include "../include/frog.h"

namespace domain{


	Frog::Frog(float x, float y, float z) : x(x), y(y), z(z), v(0.005), t1(0), t2(0), t3(0), t4(0), deltaT(0) {
		created = false;
	}

	void Frog::draw(VSMathLib* core){


		/*Materials FIXME: Please, change my location*/
		float bodyAmbient[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
		float bodyDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float bodySpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

		float headAmbient[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
		float headDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float headSpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

		float eyeAmbient[4] = { 0.5f, 0.2f, 0.2f, 1.0f };
		float eyeDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float eyeSpec[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
		core->rotate(180, 0,1,0);
		core->scale(0.4, 0.4, 0.4);

		//body.render();
		//corpo
		core->pushMatrix(VSMathLib::MODEL);
		body.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, bodySpec);
		body.setColor(VSResourceLib::DIFFUSE, bodyDiffuse);
		body.setColor(VSResourceLib::AMBIENT, bodyAmbient);
		if (!created) {
			body.createSphere(2.2, FROG_DIVISIONS);
		}
		core->scale(1.0, 0.8, 1.0);
		core->rotate(35.0, 1.0, 0.0, 0.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


		head.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, headSpec);
		head.setColor(VSResourceLib::DIFFUSE, headDiffuse);
		head.setColor(VSResourceLib::AMBIENT, headAmbient);
		//cabe�a
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			head.createSphere(1.5, 9.0);
		}
		core->translate(0.0, 1.6, -1.8);
		core->scale(0.8, 0.8, 1.0);
		head.render();
		core->popMatrix(VSMathLib::MODEL);

		eye.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, eyeSpec);
		eye.setColor(VSResourceLib::DIFFUSE, eyeDiffuse);
		eye.setColor(VSResourceLib::AMBIENT, eyeAmbient);
		//olhos - 1
		core->pushMatrix(VSMathLib::MODEL);
		if (!created) {
			eye.createSphere(0.6, 9.0);
			created = true;
		}
		core->translate(0.4, 2.8, -1.5);
		core->scale(0.7, 1.0, 0.7);
		eye.render();
		core->popMatrix(VSMathLib::MODEL);
		//olhos - 2
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(-0.4, 2.8, -1.5);
		core->scale(0.7, 1.0, 0.7);
		eye.render();
		core->popMatrix(VSMathLib::MODEL);
		core->popMatrix(VSMathLib::MODEL);


	}

	void Frog::move(int d){
		switch(d){

		case(DIR_FRONT):{
			this->z++;
			break;
		}

		case(DIR_BACK):{
			this->z--;
			break;
		}

		case(DIR_LEFT):{
			this->x++;
			break;
		}

		case(DIR_RIGHT):{
			this->x--;
			break;
		}

		}
	}

	void Frog::tick(){

	}

}

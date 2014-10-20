#include "../include/car.h"

namespace domain {

	Car::Car(float x, float y, float z, int direction, float velocity) : x(x), y(y), z(z), direction(direction), speed(velocity){
		created = false;
	}

	Car::~Car(){}

	void Car::draw(VSMathLib* core){

		float tireAmbient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		float tireDiffuse[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		float tireSpec[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

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
		}

		body.setMaterialBlockName("Materials");
		float f3[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, f3);
		float f4[4] = { 0.8f, 0.0f, 0.0f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f4);

		
		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x - 0.7f, y, z);
		else
			core->translate(x + 3.0f, y, z);
		core->scale(0.7f, 0.7f, 0.9f);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		tire.setMaterialBlockName("Materials");
		tire.setColor(VSResourceLib::SPECULAR, tireSpec);
		tire.setColor(VSResourceLib::DIFFUSE, tireDiffuse);
		tire.setColor(VSResourceLib::AMBIENT, tireAmbient);
		//pneus - 1

		if (!created) {
			tire.createCylinder(0.2f, 0.4f, 20);
			created = true;
		}		
		
		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x+1.6, y, z+0.15f);
		else
			core->translate(x+0.7, y, z+0.15f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);		
		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x + 2.3, y, z + 0.15f);
		else
			core->translate(x + 1.4, y, z + 0.15f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);

		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x + 1.6, y, z + 0.85f);
		else
			core->translate(x + 0.7, y, z + 0.85f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);
		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x + 2.3, y, z + 0.85f);
		else
			core->translate(x + 1.4, y, z + 0.85f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);

		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x + 0.1, y, z + 0.15f);
		else
			core->translate(x + 2.7, y, z + 0.15f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);

		core->pushMatrix(VSMathLib::MODEL);
		if(direction == DIR_RIGHT)
			core->translate(x + 0.1, y, z + 0.85f);
		else
			core->translate(x + 2.7, y, z + 0.85f);
		core->rotate(90, 1, 0, 0);
		tire.render();
		core->popMatrix(VSMathLib::MODEL);

		
		

	}

	void Car::tick(){
		this->second_in_game += 0.01;	//After 100 calls, 1 second
		int r = rand() % 5;
		float d = speed * 0.1;
		if (direction == DIR_LEFT){
			if (this->x >= LEFT_X_LIMIT){
				this->x = RIGHT_X_LIMIT - r;
			}
			this->x += d;
		}
		else if (direction == DIR_RIGHT){
			if (this->x <= RIGHT_X_LIMIT){
				this->x = LEFT_X_LIMIT + r;
			}
			this->x -= d;
		}


	}

} /* namespace domain */

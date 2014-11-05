/*
 * riverlog.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: un
 */

#include "../include/riverlog.h"

namespace domain {

	float Riverlog::logAmbient[4] = { 0.35f, 0.16f, 0.14f, 1.0f };
	float Riverlog::logDiffuse[4] = { 0.40f, 0.21f, 0.19f, 1.0f };
	float Riverlog::logSpec[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	float Riverlog::logShininess = 100;


	Riverlog::Riverlog(float x, float y, float z, int quality, int direction, float velocity) : x(x), y(y), z(z), direction(direction), speed(velocity) {


		body.createCylinder(LOG_HEIGHT, LOG_RADIOS, quality);
		body.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, logSpec);
		body.setColor(VSResourceLib::DIFFUSE, logDiffuse);
		body.setColor(VSResourceLib::AMBIENT, logAmbient);
		body.setColor(VSResourceLib::SHININESS, &logShininess);

		AABB = new BoxAABB(&this->x, &this->y, &this->z, LOG_HEIGHT / 2, LOG_HEIGHT / 2, 5, 5, LOG_RADIOS, LOG_RADIOS);
		//float * test1 = new float_t;
		//*test1 = 0.0f;
		//float * test2 = new float_t;
		//*test2 = 15.0f;
		//AABB = new BoxAABB(test1, test1, test2, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f);

	}

	Riverlog::~Riverlog(){}

	void Riverlog::draw(VSMathLib* core, VSShaderLib* shader){
		if (x < -1 || x > 17)
			return;

		core->pushMatrix(VSMathLib::MODEL);
		core->translate(x, y, z);
		core->rotate(90, 0, 0, 1);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

	}

	void Riverlog::tick(){
		int r = rand() % 5;
		this->second_in_game += 0.01f;	//After 100 calls, 1 second
		if (second_in_game >= 5.0){
			this->speed += SPEED_INC;
			second_in_game = 0.0f;
		}

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

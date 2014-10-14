/*
 * riverlog.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: un
 */

#include "../include/riverlog.h"

namespace domain {

Riverlog::Riverlog(float x, float y, float z, int quality, int direction, float velocity) : x(x), y(y), z(z), direction(direction), velocity(velocity) {

	body.createCylinder(LOG_HEIGHT, LOG_RADIOS, quality);

	body.setMaterialBlockName("Materials");
	float f[4] = {0.4f, 0.2f, 0.0f, 1.0f};
	body.setColor(VSResourceLib::DIFFUSE, f);
	float f2[4] = {0.4f, 0.2f, 0.0f, 1.0f};
	body.setColor(VSResourceLib::AMBIENT, f2);

}

void Riverlog::draw(VSMathLib* core){

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);
	core->rotate(90, 0, 0, 1);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

}

void Riverlog::tick(){


	float d = velocity * 0.1;
	if(direction == DIR_LEFT){
		if(this->x >= LEFT_X_LIMIT){
			this->x = RIGHT_X_LIMIT;
		}
		this->x += d;
	}else if(direction == DIR_RIGHT){
		if(this->x <= RIGHT_X_LIMIT){
			this->x = LEFT_X_LIMIT;
		}
		this->x -= d;
	}

}


} /* namespace domain */

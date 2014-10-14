/*
 * riverlog.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: un
 */

#include "../include/riverlog.h"

namespace domain {

Riverlog::Riverlog(float x, float y, float z, int quality) {
	_x = x;
	_y = y;
	_z = z;
	body.createCylinder(LOG_HEIGHT, LOG_RADIOS, quality);

	body.setMaterialBlockName("Materials");
	float f[4] = {0.4f, 0.2f, 0.0f, 1.0f};
	body.setColor(VSResourceLib::DIFFUSE, f);
	float f2[4] = {0.4f, 0.2f, 0.0f, 1.0f};
	body.setColor(VSResourceLib::AMBIENT, f2);

}

void Riverlog::draw(VSMathLib* core){

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_x, _y, _z);
	core->rotate(90, 0, 0, 1);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

}

void Riverlog::tick(){

}


} /* namespace domain */

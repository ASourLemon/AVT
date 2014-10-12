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
	float f[4] = {0.8f, 0.6f, 0.4f, 1.0f};
	body.setColor(VSResourceLib::DIFFUSE, f);
	float f2[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	body.setColor(VSResourceLib::AMBIENT, f2);

}

void Riverlog::draw(VSMathLib* core){

	core->pushMatrix(VSMathLib::MODEL);
	core->rotate(90, 1,0,0);
	core->translate(_x, _y, _z);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

}

} /* namespace domain */

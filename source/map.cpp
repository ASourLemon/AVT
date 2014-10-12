/*
 * map.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: un
 */

#include "../include/map.h"

namespace domain {

Map::Map() {

	body.createCube(1.0f);

	body.setMaterialBlockName("Materials");
	float f[4] = {0.8f, 0.6f, 0.4f, 1.0f};
	body.setColor(VSResourceLib::DIFFUSE, f);
	float f2[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	body.setColor(VSResourceLib::AMBIENT, f2);

}

void Map::draw(VSMathLib* core){

	//core->pushMatrix(VSMathLib::MODEL);
	//core->rotate(90, 1,0,0);
	//core->translate(_x, _y, _z);
	body.render();
	//core->popMatrix(VSMathLib::MODEL);
}

} /* namespace domain */

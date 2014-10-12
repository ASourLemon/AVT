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

	for(int l = 0; l < MAP0_H; ++l){
		for(int c = 0; c < MAP0_W; ++c){
			if(map_0[l * MAP0_W + c] == WALL_CHAR){
				core->pushMatrix(VSMathLib::MODEL);
				core->translate(c, 0, l);
				body.render();
				core->popMatrix(VSMathLib::MODEL);
			}
		}
	}

	body.render();


}

} /* namespace domain */

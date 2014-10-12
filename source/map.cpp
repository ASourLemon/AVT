#include "../include/map.h"

namespace domain {

	Map::Map() {

		body.createCube(1.0f);
		water.createSphere(0.85, 100);

		deltaWater = 0;
		goingLeft = false;

	}

	void Map::draw(VSMathLib* core){

		//FIXME: moviment - HAHAHA just remove me :p
		if (!goingLeft && deltaWater < 1){
			deltaWater += 0.05;
		}
		else {
			deltaWater -= 0.05;
			goingLeft = true;
			if (deltaWater < 0){
				goingLeft = false;
			}
		}

		body.setMaterialBlockName("Materials");
		float d1[4] = { 0.8f, 0.6f, 0.4f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, d1);
		float f2[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f2);
		////////////////////////////////////
		/////////////////////////////////// walls
		///////////////////////////////////
		//top
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, -1.0);
		core->scale(MAP0_W, 2.0, 1.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		//right
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(MAP0_W, -1.0, 0.0);
		core->scale(1.0, 2.0, MAP0_H);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		//left
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(-1.0, -1.0, 0.0);
		core->scale(1.0, 2.0, MAP0_H);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		//down
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, MAP0_H);
		core->scale(MAP0_W, 2.0, 1.0);
		body.render();
		core->popMatrix(VSMathLib::MODEL);



		float d2[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, d2);
		float f3[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f3);
		///////////////////////////////////
		/////////////////////////////////// floor
		///////////////////////////////////
		//top border
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, 0.0);
		core->scale(MAP0_W, 1, 3);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		//mid border
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, 8.0);
		core->scale(MAP0_W, 1, 1);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		//down border
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, 13.0);
		core->scale(MAP0_W, 1, 3);
		body.render();
		core->popMatrix(VSMathLib::MODEL);


		float d3[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		body.setColor(VSResourceLib::DIFFUSE, d3);
		float f5[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		body.setColor(VSResourceLib::AMBIENT, f5);
		//road	FIXME:	CHANGE MATERIAL
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, 3.0);
		core->scale(MAP0_W, 1, 5);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

		water.setMaterialBlockName("Materials");
		float d4[4] = { 0.0f, 0.2f, 0.6f, 1.0f };
		water.setColor(VSResourceLib::DIFFUSE, d4);
		float f6[4] = { 0.0f, 0.2f, 0.6f, 1.0f };
		water.setColor(VSResourceLib::AMBIENT, f6);

		//river	FIXME:	CHANGE MATERIAL
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(0.0, -1.0, 9.0);	//base translate
		for (int l = 0.5; l < 5; l++){
			for (int c = -1; c <= MAP0_W + 1; c++){
				core->pushMatrix(VSMathLib::MODEL);
				if (l % 2 == 0){
					core->translate(c + deltaWater, -1.0, l);
				}
				else {
					core->translate(c - deltaWater, -1.0, l);
				}
				water.render();
				core->popMatrix(VSMathLib::MODEL);
			}
		}
		core->popMatrix(VSMathLib::MODEL);


	}

} /* namespace domain */

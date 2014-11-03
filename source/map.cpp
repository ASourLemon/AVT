#include "../include/map.h"

extern GLuint TextureArray[3];

namespace domain {

float Map::roadAmb[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Map::roadDif[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
float Map::roadSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Map::roadShininess = 1;

float Map::grassAmb[4] = { 0.05f/3.0f, 0.125f/3.0f, 0.05f/3.0f, 1.0f };
float Map::grassDif[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
float Map::grassSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Map::grassShininess = 1;

float Map::waterAmb[4] = { 0.08f, 0.12f, 0.08f, 1.0f };
float Map::waterDif[4] = { 0.4f, 0.6f, 0.4f, 1.0f };
float Map::waterSpec[4] = { 0.0f, 0.0f, 0.1f, 1.0f };
float Map::waterShininess = 10;

float Map::wallAmb[4] = { 0.2f, 0.1f, 0.1f, 1.0f };
float Map::wallDif[4] = { 1.2f, 0.6f, 0.8f, 1.0f };
float Map::wallSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Map::wallShininess = 1;

float Map::cubeAmb[4] = { 0.2f, 0.1f, 0.1f, 1.0f };
float Map::cubeDif[4] = { 1.2f, 0.6f, 0.8f, 1.0f };
float Map::cubeSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Map::cubeShininess = 1;

Map::Map() {

	body.createCube(1.0f);
	//water.createSphere(2.4f, 5);
	water.createCube(2.0f);

	deltaWater = 0.0f;
	goingLeft = false;
	win_x = 10.0f;
	win_y = 0.0f;
	win_z = 28.0f;
	win_box = new BoxAABB(&win_x, &win_y, &win_z, 10.0f, 10.0f, 1.0f, 1.0f,
			1.0f, 1.0f);
}

Map::~Map() {
}

void Map::draw(VSMathLib* core) {

	body.setMaterialBlockName("Materials");
	body.setColor(VSResourceLib::DIFFUSE, wallDif);
	body.setColor(VSResourceLib::AMBIENT, wallAmb);
	body.setColor(VSResourceLib::SPECULAR, wallSpec);
	body.setColor(VSResourceLib::SHININESS, &wallShininess);

	////////////////////////////////////
	/////////////////////////////////// walls
	///////////////////////////////////
	//top
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, -1.0, -1.0);
	core->scale(MAP0_W, 3.5, 1.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	//right
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(MAP0_W, -1.0, 0.0);
	core->scale(1.0, 3.5, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(MAP0_W, 1.5, 3.0);
	core->scale(1.0, 1.0, 10.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(MAP0_W, -1.0, 13.0);
	core->scale(1.0, 3.5, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(MAP0_W, -1.0, 24.0);
	core->scale(1.0, 3.5, 8.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	//left
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.0, -1.0, 0.0);
	core->scale(1.0, 3.5, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.0, 1.5, 3.0);
	core->scale(1.0, 1.0, 10.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.0, -1.0, 13.0);
	core->scale(1.0, 3.5, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-1.0, -1.0, 24.0);
	core->scale(1.0, 3.5, 8.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	//down
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, -1.0, MAP0_H);
	core->scale(MAP0_W, 3.5, 1.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	///////////////////////////////////
	/////////////////////////////////// floor
	///////////////////////////////////

	body.setColor(VSResourceLib::DIFFUSE, grassDif);
	body.setColor(VSResourceLib::AMBIENT, grassAmb);
	body.setColor(VSResourceLib::SPECULAR, grassSpec);
	body.setColor(VSResourceLib::SHININESS, &grassShininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[3]);

	//top border
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, -1.0, 0.0);
	core->scale(MAP0_W, 1.0, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	//mid border
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, -0.4, 13.0);
	core->scale(MAP0_W, 0.3, 3.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	//down border
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, -0.4, 24.0);
	core->scale(MAP0_W, 0.3, 8);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);


	/////////////////////////////////////////////////
	///ROAD/////////////////////////////////////////
	////////////////////////////////////////////////

	body.setColor(VSResourceLib::DIFFUSE, roadDif);
	body.setColor(VSResourceLib::AMBIENT, roadAmb);
	body.setColor(VSResourceLib::SPECULAR, roadSpec);
	body.setColor(VSResourceLib::SHININESS, &roadShininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[1]);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-2.0, -1.0, 3.0);
	core->scale(MAP0_W + 5, 1, 10);
	body.render();
	core->popMatrix(VSMathLib::MODEL);

	/////////////////////////////////////////////////
	///RIVER/////////////////////////////////////////
	////////////////////////////////////////////////

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

	water.setMaterialBlockName("Materials");
	water.setColor(VSResourceLib::DIFFUSE, waterDif);
	water.setColor(VSResourceLib::AMBIENT, waterAmb);
	water.setColor(VSResourceLib::SPECULAR, waterSpec);
	water.setColor(VSResourceLib::SHININESS, &waterShininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[2]);
	
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF); // Write to stencil buffer
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)
	
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-2.0, -0.5, 16.0);	//base translate
	for (int l = 0; l < 10; l += 3) {
		for (int c = -2; c <= MAP0_W + 2; c += 2) {
			core->pushMatrix(VSMathLib::MODEL);
			/*if (l % 2 == 0) {
				core->translate(c + deltaWater, -1.0f, l + 0.5f);
			} else {
				core->translate(c - deltaWater, -1.0f, l + 0.5f);
			}*/
			core->scale(MAP0_W + 5, 0.1, 8.0);
			water.render();
			core->popMatrix(VSMathLib::MODEL);
		}
	}
	core->popMatrix(VSMathLib::MODEL);
	glDepthMask(GL_TRUE);
	glDisable(GL_STENCIL_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
}

void Map::tick() {
	if (!goingLeft && deltaWater < 1) {
		deltaWater += WATER_SPEED * 0.1;
	} else {
		deltaWater -= WATER_SPEED * 0.1;
		goingLeft = true;
		if (deltaWater < 0) {
			goingLeft = false;
		}
	}

}

}

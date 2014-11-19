#include "../include/grass.h"

#include <string.h>
#include "../include/game.h"
#include "../include/camera.h"


namespace domain {

float Grass::cubeAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
float Grass::cubeDif[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
float Grass::cubeSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Grass::cubeShininess = 1;

Grass::Grass(float x, float z, bool c) :
		_x(x), _z(z), cross(c) {
	rectangle.createRectangle(1.5f, 1.0f);
}

Grass::~Grass() {
}

void Grass::draw(VSMathLib* core, VSShaderLib* shader) {

	rectangle.setMaterialBlockName("Materials");
	rectangle.setColor(VSResourceLib::DIFFUSE, cubeDif);
	rectangle.setColor(VSResourceLib::AMBIENT, cubeAmb);
	rectangle.setColor(VSResourceLib::SPECULAR, cubeSpec);
	rectangle.setColor(VSResourceLib::SHININESS, &cubeShininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[7]);

	bool c = getCross();
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_x, 1.0 / 2, _z);
	if(c){
		core->rotate(45.0f, 0.0f, 1.0f, 0.0f);
	}

	// TODO: This would be a such more nice code if we had used class Vec3
	float *objToCam = Game::getInstance()->getActiveCamera()->getPos();
	// float *look_at = Game::getInstance()->getActiveCamera()->getAtVector();
	// FIXME: Names and comment above. THIS IS NOT LOOK AT FROM CAMERA...
	// IT IS THE LOOK AT AS IF WE WERE ON THE FIRST POSITION, LOOKING TO THE BILLBOARD
	float look_at[3] = { 0, 0, -1 };
	// FIXME: Hard coded, these will later be variables, not constants
	objToCam[0] -= _x;
	objToCam[1] = 0;
	objToCam[2] -= _z;
	VSMathLib::normalize(objToCam);
	VSMathLib::normalize(look_at);
	float cos_alpha = VSMathLib::dotProduct(look_at, objToCam);
	float up_aux[3];
	VSMathLib::crossProduct(look_at, objToCam, up_aux);
	core->rotate(acos(cos_alpha) * 180.0 / 3.14, up_aux[0], up_aux[1],
			up_aux[2]);

	delete objToCam;

	glDisable(GL_CULL_FACE);
	rectangle.render();
	glEnable(GL_CULL_FACE);

	core->popMatrix(VSMathLib::MODEL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
}

void Grass::tick() {
}

}

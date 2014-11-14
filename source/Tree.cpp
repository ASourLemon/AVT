#include "../include/Tree.h"
#include <string.h>
#include "game.h"
#include "camera.h"

extern GLuint TextureArray[3];

namespace domain {

float Tree::cubeAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
float Tree::cubeDif[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
float Tree::cubeSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Tree::cubeShininess = 1;

Tree::Tree(float x, float z) :
		_x(x), _z(z) {
	rectangle.createRectangle(4.5f, 3.0f);
}

Tree::~Tree() {
}

void Tree::draw(VSMathLib* core, VSShaderLib* shader) {

	rectangle.setMaterialBlockName("Materials");
	rectangle.setColor(VSResourceLib::DIFFUSE, cubeDif);
	rectangle.setColor(VSResourceLib::AMBIENT, cubeAmb);
	rectangle.setColor(VSResourceLib::SPECULAR, cubeSpec);
	rectangle.setColor(VSResourceLib::SHININESS, &cubeShininess);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[4]);

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_x, 4.5 / 2, _z);

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

	/*
	 TODO: Implement this pseudocode ---> IMPLEMENTED ABOVE, BUT STILL NOT WORKING AS INTENDED

	 objTocam = CamPos - ObjPos;
	 objToCam.y = 0;
	 normalize(objToCam);
	 cos_alpha = dot(lookAt, objToCam);
	 upAux = crossProduct(lookAt, objToCam);
	 core->rotate(arcos(cos_alpha)*180/PI, upAux.x, upAux.y, upAux.z);
	 */
	glDisable(GL_CULL_FACE);
	rectangle.render();
	glEnable(GL_CULL_FACE);

	core->popMatrix(VSMathLib::MODEL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
}

void Tree::tick() {
}

}

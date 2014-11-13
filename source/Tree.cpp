#include "../include/Tree.h"
#include <string.h>
#include "game.h"
#include "camera.h"

extern GLuint TextureArray[3];

namespace domain {

float Tree::cubeAmb[4] = { 0.0f, 0.2f, 0.0f, 1.0f };
float Tree::cubeDif[4] = { 0.0f, 0.6f, 0.0f, 1.0f };
float Tree::cubeSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Tree::cubeShininess = 1;

Tree::Tree() {
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
	core->translate(3.0f, 4.5/2, 7.0f);

	// TODO: This would be a such more nice code if we had used class Vec3
	float *objToCam = Game::getInstance()->getActiveCamera()->getPos();
	float *look_at = Game::getInstance()->getActiveCamera()->getAtVector();
	// FIXME: Hard coded, these will later be variables, not constants
	const float TREE_X = 3.0f;
	const float TREE_Z = 7.0f;
	objToCam[0] -= TREE_X;
	objToCam[1] = 0;
	objToCam[2] -= TREE_Z;
	printf("Projection = (%f, %f, %f)\n", objToCam[0], objToCam[1], objToCam[2]);
	VSMathLib::normalize(objToCam);
	VSMathLib::normalize(look_at);
	printf("Normalized Projection = (%f, %f, %f)\n", objToCam[0], objToCam[1], objToCam[2]);
	float cos_alpha = VSMathLib::dotProduct(look_at, objToCam);
	printf("Look At = (%f, %f, %f)\n", look_at[0], look_at[1], look_at[2]);
	printf("Cos alpha: %f\n", cos_alpha);
	printf("Alpha: %f\n", acos(cos_alpha));
	float up_aux[3];
	VSMathLib::crossProduct(look_at, objToCam, up_aux);
	printf("UP AUX = (%f, %f, %f)\n", up_aux[0], up_aux[1], up_aux[2]);
	core->rotate(acos(cos_alpha)*180.0/3.14, 0, 1, 0);

	delete objToCam;
	delete look_at;

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

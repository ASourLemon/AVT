#include "../include/Tree.h"
#include <string.h>

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
	/*
	TODO: Implement this pseudocode

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

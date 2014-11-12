#include "../include/Tree.h"
#include <string.h>

extern GLuint TextureArray[3];

namespace domain {

float Tree::cubeAmb[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
float Tree::cubeDif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Tree::cubeSpec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float Tree::cubeShininess = 1;

Tree::Tree() {
	//TODO: Create polygon
	rectangle.createRectangle(7.0f, 2.0f);
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
	core->pushMatrix(VSMathLib::VIEW);
	core->translate(5.0f, 0.0f, 7.0f);

	float *current_vm, old_vm[16];
	current_vm = core->get(VSMathLib::VIEW_MODEL);
	memcpy(old_vm, current_vm, 16);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				current_vm[i * 4 + j] = 1.0f;
			} else {
				current_vm[i * 4 + j] = 0.0f;
			}
		}
	}

	//FIXME: Tricky hacks
	core->loadIdentity(VSMathLib::MODEL);
	core->loadIdentity(VSMathLib::VIEW);
	core->loadMatrix(VSMathLib::MODEL, current_vm);
	rectangle.render();

	core->popMatrix(VSMathLib::MODEL);
	core->popMatrix(VSMathLib::VIEW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

//	glClear(GL_STENCIL_BUFFER_BIT);
//	glEnable(GL_STENCIL_TEST);
//	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    glStencilMask(0xFF); // Write to stencil buffer
//	glDepthMask(GL_FALSE);
//	glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)
}

void Tree::tick() {
}

}

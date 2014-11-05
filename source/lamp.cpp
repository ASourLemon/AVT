#include "../include/lamp.h"

namespace domain {

float Lamp::supportAmb[4] = { 64.0/1024.0, 64.0/1024.0, 64.0/1024.0, 1.0f };
float Lamp::supportDif[4] = { 64.0/256.0, 64.0/256.0, 64.0/256.0, 1.0f };
float Lamp::supportSpec[4] = { 64.0/256.0, 64.0/256.0, 64.0/256.0, 1.0f };
float Lamp::supportShininess = 10;

float Lamp::lampShadeAmb[4] = { 0.25f, 0.25f, 153.0/1024.0, 1.0f };
float Lamp::lampShadeDif[4] = { 1.0f, 1.0f, 153.0/256.0, 1.0f };
float Lamp::lampShadeSpec[4] = { 1.0f, 1.0f, 153.0/256.0, 1.0f };
float Lamp::lampShadeShininess = 100;

//Reflections Color FIX ME
float Lamp::RsupportAmb[4] = { 64.0/1024.0, 64.0/1024.0, 64.0/1024.0, 1.0f };
float Lamp::RsupportDif[4] = { 64.0/256.0, 64.0/256.0, 64.0/256.0, 1.0f };
float Lamp::RsupportSpec[4] = { 64.0/256.0, 64.0/256.0, 64.0/256.0, 1.0f };
float Lamp::RsupportShininess = 10;
//FIX ME
float Lamp::RlampShadeAmb[4] = { 0.25f, 0.25f, 153.0/1024.0, 1.0f };
float Lamp::RlampShadeDif[4] =  { 1.0f, 1.0f, 153.0/256.0, 1.0f };
float Lamp::RlampShadeSpec[4] = { 1.0f, 1.0f, 153.0/256.0, 1.0f };
float Lamp::RlampShadeShininess = 100;

Lamp::Lamp(float x, float y, float z, bool reflect) :
		x(x), y(y), z(z) {
	created = false;
	reflection = reflect;

	if(reflection == false)
		AABB = new BoxAABB(&this->x, &this->y, &this->z, 0.15f, 0.15f, 0.7f, 0.7f, 0.15f, 0.15f);

	support.createCylinder(1.0f, 0.2f, 10);
	support.setMaterialBlockName("Materials");
	support.setColor(VSResourceLib::DIFFUSE, supportDif);
	support.setColor(VSResourceLib::AMBIENT, supportAmb);
	support.setColor(VSResourceLib::SPECULAR, supportSpec);
	support.setColor(VSResourceLib::SHININESS, &supportShininess);

	lampShade.createSphere(1.0f, LAMP_DIVISIONS);
	lampShade.setMaterialBlockName("Materials");
	lampShade.setColor(VSResourceLib::DIFFUSE, lampShadeDif);
	lampShade.setColor(VSResourceLib::AMBIENT, lampShadeAmb);
	lampShade.setColor(VSResourceLib::SPECULAR, lampShadeSpec);
	lampShade.setColor(VSResourceLib::SHININESS, &lampShadeShininess);

	if(reflection == true){
		support.setMaterialBlockName("Materials");
		support.setColor(VSResourceLib::DIFFUSE, RsupportDif);
		support.setColor(VSResourceLib::AMBIENT, RsupportAmb);
		support.setColor(VSResourceLib::SPECULAR, RsupportSpec);
		support.setColor(VSResourceLib::SHININESS, &RsupportShininess);

		lampShade.setMaterialBlockName("Materials");
		lampShade.setColor(VSResourceLib::DIFFUSE, RlampShadeDif);
		lampShade.setColor(VSResourceLib::AMBIENT, RlampShadeAmb);
		lampShade.setColor(VSResourceLib::SPECULAR, RlampShadeSpec);
		lampShade.setColor(VSResourceLib::SHININESS, &RlampShadeShininess);
	}

}

Lamp::~Lamp() {
}

void Lamp::draw(VSMathLib* core, VSShaderLib* shader) {
	glEnable(GL_STENCIL_TEST);
	
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);

	//support
	core->pushMatrix(VSMathLib::MODEL);
	float SUPPORT_HEIGHT = 3.0f;
	core->translate(0.0f, SUPPORT_HEIGHT / 2, 0.0f);
	core->scale(1.0f, SUPPORT_HEIGHT, 1.0f);
		if(reflection == true){
			//glDepthMask(GL_FALSE); // Don't write to depth buffer
			glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
			glStencilMask(0x00); // Don't write anything to stencil buffer
			//glDepthMask(GL_TRUE); // Write to depth buffer
			core->translate(0.0f, -1.0f, 0.0f);
		}
	support.render();
	core->popMatrix(VSMathLib::MODEL);

	//lampShade
	core->pushMatrix(VSMathLib::MODEL);
	float LAMP_SHADE_RADIUS = 0.4f;
	core->translate(0.0f, SUPPORT_HEIGHT + LAMP_SHADE_RADIUS, 0.0f);
	core->scale(LAMP_SHADE_RADIUS, LAMP_SHADE_RADIUS, LAMP_SHADE_RADIUS);
		if(reflection == true){
			//glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
			//glStencilMask(0x00); // Don't write anything to stencil buffer
			//glDepthMask(GL_TRUE); // Write to depth buffer
			core->translate(0.0f, -15.6f, 0.0f);
		}
	lampShade.render();
	core->popMatrix(VSMathLib::MODEL);

	//end
	core->popMatrix(VSMathLib::MODEL);
	glDisable(GL_STENCIL_TEST);
}

void Lamp::tick() {
}

} /* namespace domain */

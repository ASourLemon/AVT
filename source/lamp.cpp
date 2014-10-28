#include "../include/lamp.h"

namespace domain {

float Lamp::supportAmb[4] = { 0.1f, 0.4f, 0.1f, 1.0f };
float Lamp::supportDif[4] = { 0.2f, 0.4f, 0.2f, 1.0f };
float Lamp::supportSpec[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
float Lamp::supportShininess = 100;

float Lamp::lampShadeAmb[4] = { 0.2f, 0.6f, 0.2f, 1.0f };
float Lamp::lampShadeDif[4] = { 0.5f, 0.7f, 0.5f, 1.0f };
float Lamp::lampShadeSpec[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float Lamp::lampShadeShininess = 100;

Lamp::Lamp(float x, float y, float z) :
		x(x), y(y), z(z) {
	created = false;

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

}

Lamp::~Lamp() {
}

void Lamp::draw(VSMathLib* core) {

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);

	//support
	core->pushMatrix(VSMathLib::MODEL);
	float SUPPORT_HEIGHT = 3.0f;
	core->translate(0.0f, SUPPORT_HEIGHT / 2, 0.0f);
	core->scale(1.0f, SUPPORT_HEIGHT, 1.0f);
	support.render();
	core->popMatrix(VSMathLib::MODEL);

	//lampShade
	core->pushMatrix(VSMathLib::MODEL);
	float LAMP_SHADE_RADIUS = 0.4f;
	core->translate(0.0f, SUPPORT_HEIGHT + LAMP_SHADE_RADIUS, 0.0f);
	core->scale(LAMP_SHADE_RADIUS, LAMP_SHADE_RADIUS, LAMP_SHADE_RADIUS);
	lampShade.render();
	core->popMatrix(VSMathLib::MODEL);

	//end
	core->popMatrix(VSMathLib::MODEL);
}

void Lamp::tick() {
}

} /* namespace domain */

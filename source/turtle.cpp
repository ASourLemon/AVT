#include "../include/turtle.h"

namespace domain {

float Turtle::bodyAmb[4] = { 0.1f, 0.4f, 0.1f, 1.0f };
float Turtle::bodyDif[4] = { 0.2f, 0.4f, 0.2f, 1.0f };
float Turtle::bodySpec[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
float Turtle::bodyShininess = 10;

float Turtle::headAmb[4] = { 0.2f, 0.6f, 0.2f, 1.0f };
float Turtle::headDif[4] = { 0.5f, 0.7f, 0.5f, 1.0f };
float Turtle::headSpec[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float Turtle::headShininess = 10;

float Turtle::legAmb[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
float Turtle::legDif[4] = { 0.4f, 0.6f, 0.4f, 1.0f };
float Turtle::legSpec[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float Turtle::legShininess = 10;

Turtle::Turtle(Vec3 position, Vec3 initSpeed) : created(false)  {
	_position = position;
	_initSpeed = initSpeed;
	_speed = initSpeed;
	
	body.createSphere(0.8f, TURTLE_DIVISIONS);
	body.setMaterialBlockName("Materials");
	body.setColor(VSResourceLib::DIFFUSE, bodyDif);
	body.setColor(VSResourceLib::AMBIENT, bodyAmb);
	body.setColor(VSResourceLib::SPECULAR, bodySpec);
	body.setColor(VSResourceLib::SHININESS, &bodyShininess);
	
	leg.createSphere(0.9f, TURTLE_DIVISIONS);
	leg.setMaterialBlockName("Materials");
	leg.setColor(VSResourceLib::DIFFUSE, legDif);
	leg.setColor(VSResourceLib::AMBIENT, legAmb);
	leg.setColor(VSResourceLib::SPECULAR, legSpec);
	leg.setColor(VSResourceLib::SHININESS, &legShininess);
	
	head.createSphere(0.3f, TURTLE_DIVISIONS);
	head.setMaterialBlockName("Materials");
	head.setColor(VSResourceLib::DIFFUSE, headDif);
	head.setColor(VSResourceLib::AMBIENT, headAmb);
	head.setColor(VSResourceLib::SPECULAR, headSpec);
	head.setColor(VSResourceLib::SHININESS, &headShininess);

	body_box = new BoxAABB(&_position, 0.8f, 0.24f, 0.1f);
}

Turtle::~Turtle() {
	delete body_box;
}

void Turtle::draw(VSMathLib* core, VSShaderLib* shader) {
	
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_position.getX(), _position.getY(), _position.getZ());
	
	//body
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0f, 0.15f, 0.0f);
	core->scale(1.0f, 0.3f, 1.0f);
	body.render();
	core->popMatrix(VSMathLib::MODEL);
	
	//legs
	core->pushMatrix(VSMathLib::MODEL);	
	core->rotate(45.0f, 0.0f, 1.0f, 0.0f);	
	core->scale(1.2f, 0.1f, 0.2f);
	leg.render();
	core->popMatrix(VSMathLib::MODEL);
	
	core->pushMatrix(VSMathLib::MODEL);	
	core->rotate(-45.0f, 0.0f, 1.0f, 0.0f);
	core->scale(1.2f, 0.1f, 0.2f);
	leg.render();
	core->popMatrix(VSMathLib::MODEL);
	
	//head
	core->pushMatrix(VSMathLib::MODEL);	
	if(_speed.getX() < 0){
		core->translate(-0.6f, 0.0f, 0.0f);	
	}else if(_speed.getX() > 0){
		core->translate(0.6f, 0.0f, 0.0f);
	}

	core->scale(1.4f, 0.4f, 1.0f);
	head.render();
	core->popMatrix(VSMathLib::MODEL);
	
	
	
	//end
	core->popMatrix(VSMathLib::MODEL);
}

} /* namespace domain */

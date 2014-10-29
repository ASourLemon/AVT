#include "../include/turtle.h"

namespace domain {

float Turtle::bodyAmb[4] = { 0.1f, 0.4f, 0.1f, 1.0f };
float Turtle::bodyDif[4] = { 0.2f, 0.4f, 0.2f, 1.0f };
float Turtle::bodySpec[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
float Turtle::bodyShininess = 100;

float Turtle::headAmb[4] = { 0.2f, 0.6f, 0.2f, 1.0f };
float Turtle::headDif[4] = { 0.5f, 0.7f, 0.5f, 1.0f };
float Turtle::headSpec[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float Turtle::headShininess = 100;

float Turtle::legAmb[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
float Turtle::legDif[4] = { 0.4f, 0.6f, 0.4f, 1.0f };
float Turtle::legSpec[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float Turtle::legShininess = 100;

Turtle::Turtle(float x, float y, float z, int direction, float velocity) :
		x(x), y(y), z(z), direction(direction), speed(velocity) {
	created = false;
	
	body.createSphere(0.8, TURTLE_DIVISIONS);
	body.setMaterialBlockName("Materials");
	body.setColor(VSResourceLib::DIFFUSE, bodyDif);
	body.setColor(VSResourceLib::AMBIENT, bodyAmb);
	body.setColor(VSResourceLib::SPECULAR, bodySpec);
	body.setColor(VSResourceLib::SHININESS, &bodyShininess);
	
	leg.createSphere(0.9, TURTLE_DIVISIONS);
	leg.setMaterialBlockName("Materials");
	leg.setColor(VSResourceLib::DIFFUSE, legDif);
	leg.setColor(VSResourceLib::AMBIENT, legAmb);
	leg.setColor(VSResourceLib::SPECULAR, legSpec);
	leg.setColor(VSResourceLib::SHININESS, &legShininess);
	
	head.createSphere(0.3, TURTLE_DIVISIONS);
	head.setMaterialBlockName("Materials");
	head.setColor(VSResourceLib::DIFFUSE, headDif);
	head.setColor(VSResourceLib::AMBIENT, headAmb);
	head.setColor(VSResourceLib::SPECULAR, headSpec);
	head.setColor(VSResourceLib::SHININESS, &headShininess);

	body_box = new BoxAABB(&this->x, &this->y, &this->z, 0.4f, 0.4f, 0.12f, 0.12f, 0.4f, 0.4f);
}

Turtle::~Turtle() {
}

void Turtle::draw(VSMathLib* core) {
	
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(x, y, z);
	
	//body
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(0.0, 0.15, 0.0);
	core->scale(1.0, 0.3, 1.0);
	body.render();
	core->popMatrix(VSMathLib::MODEL);
	
	//legs
	core->pushMatrix(VSMathLib::MODEL);	
	core->rotate(45.0, 0, 1, 0);	
	core->scale(1.2, 0.1, 0.2);
	leg.render();
	core->popMatrix(VSMathLib::MODEL);
	
	core->pushMatrix(VSMathLib::MODEL);	
	core->rotate(-45.0, 0, 1, 0);
	core->scale(1.2, 0.1, 0.2);
	leg.render();
	core->popMatrix(VSMathLib::MODEL);
	
	//head
	core->pushMatrix(VSMathLib::MODEL);	
	if(direction == DIR_RIGHT){
		core->translate(-0.6, 0.0, 0.0);	
	}else if(direction == DIR_LEFT){
		core->translate(0.6, 0.0, 0.0);
	}

	core->scale(1.4, 0.4, 1.0);
	head.render();
	core->popMatrix(VSMathLib::MODEL);
	
	
	
	//end
	core->popMatrix(VSMathLib::MODEL);
}

void Turtle::tick() {
	this->second_in_game += 0.01;	//After 100 calls, 1 second
	int r = rand() % 5;
	float d = speed * 0.1;
	if (direction == DIR_LEFT) {
		if (this->x >= LEFT_X_LIMIT) {
			this->x = RIGHT_X_LIMIT - r;
		}
		this->x += d;
	} else if (direction == DIR_RIGHT) {
		if (this->x <= RIGHT_X_LIMIT) {
			this->x = LEFT_X_LIMIT + r;
		}
		this->x -= d;
	}

}

} /* namespace domain */

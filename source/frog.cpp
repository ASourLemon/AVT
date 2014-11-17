#include "../include/frog.h"

namespace domain{

float Frog::bodyAmbient[4] = { 0.2f, 0.4f, 0.2f, 1.0f };
float Frog::bodyDiffuse[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
float Frog::bodySpec[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
float Frog::bodyShininess = 20;

float Frog::headAmbient[4] = { 0.2f, 0.4f, 0.2f, 1.0f };
float Frog::headDiffuse[4] = { 0.2f, 0.5f, 0.2f, 1.0f };
float Frog::headSpec[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
float Frog::headShininess = 20;

float Frog::eyeAmbient[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
float Frog::eyeDiffuse[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
float Frog::eyeSpec[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
float Frog::eyeShininess = 100;


Frog::Frog(float x, float y, float z, float speed, int direction) : 
			_x(x), _y(y), _z(z), speed(speed), t(0), deltaT(0), direction(direction), created(false), beingCompressed(false), 
				compressed(1.0){
	
	//float center[3] = { this->x, this->y, this->z};
	Sphere = new BoxSphere(&_x, &_y, &_z, 2.2f*0.4f);

}

Frog::~Frog(){
	delete Sphere;
}

void Frog::draw(VSMathLib* core, VSShaderLib* shader){

	core->pushMatrix(VSMathLib::MODEL);
	core->translate(_x, _y, _z);
	
	if(direction == DIR_FRONT){
		core->rotate(180, 0, 1, 0);
	}else if(direction == DIR_RIGHT){
		core->rotate(90, 0, 1, 0);
	}else if(direction == DIR_LEFT){
		core->rotate(-90, 0 ,1, 0);
	}

	core->scale(0.2f, 0.2f * compressed, 0.2f);

	//corpo
	core->pushMatrix(VSMathLib::MODEL);
	body.setMaterialBlockName("Materials");
	body.setColor(VSResourceLib::SPECULAR, bodySpec);
	body.setColor(VSResourceLib::DIFFUSE, bodyDiffuse);
	body.setColor(VSResourceLib::AMBIENT, bodyAmbient);
	body.setColor(VSResourceLib::SHININESS, &bodyShininess);
	if (!created) {
		body.createSphere(2.2f, FROG_DIVISIONS);
	}
	core->scale(1.0f, 0.8f, 1.0f);
	core->rotate(35.0f, 1.0f, 0.0f, 0.0f);
	body.render();
	core->popMatrix(VSMathLib::MODEL);


	head.setMaterialBlockName("Materials");
	head.setColor(VSResourceLib::SPECULAR, headSpec);
	head.setColor(VSResourceLib::DIFFUSE, headDiffuse);
	head.setColor(VSResourceLib::AMBIENT, headAmbient);
	head.setColor(VSResourceLib::SHININESS, &headShininess);
	//cabeca
	core->pushMatrix(VSMathLib::MODEL);
	if (!created) {
		head.createSphere(1.5f, 9.0f);
	}
	core->translate(0.0f, 1.6f, -1.8f);
	core->scale(0.8f, 0.8f, 1.0f);
	head.render();
	core->popMatrix(VSMathLib::MODEL);

	eye.setMaterialBlockName("Materials");
	eye.setColor(VSResourceLib::SPECULAR, eyeSpec);
	eye.setColor(VSResourceLib::DIFFUSE, eyeDiffuse);
	eye.setColor(VSResourceLib::AMBIENT, eyeAmbient);
	eye.setColor(VSResourceLib::SHININESS, &eyeShininess);

	//olhos - 1
	core->pushMatrix(VSMathLib::MODEL);
	if (!created) {
		eye.createSphere(0.6f, 9.0f);
		created = true;
	}
	core->translate(0.4f, 2.8f, -1.5f);
	core->scale(0.7f, 1.0f, 0.7f);
	eye.render();
	core->popMatrix(VSMathLib::MODEL);
	//olhos - 2
	core->pushMatrix(VSMathLib::MODEL);
	core->translate(-0.4f, 2.8f, -1.5f);
	core->scale(0.7f, 1.0f, 0.7f);
	eye.render();
	core->popMatrix(VSMathLib::MODEL);
	core->popMatrix(VSMathLib::MODEL);
	
	/*core->pushMatrix(VSMathLib::MODEL);
	
	core->scale(4.3, 4.3, 4.3);
	core->translate(0.0,0.2,-0.15);
	eye.render();
	core->popMatrix(VSMathLib::MODEL);
	core->popMatrix(VSMathLib::MODEL);*/

}

void Frog::move(int d){
	switch(d){

	case(DIR_FRONT):{			
		direction = DIR_FRONT;
		if(_z < 31.0){
			deltaT=glutGet(GLUT_ELAPSED_TIME)-t;
			_z+=speed*deltaT;
		}  

		break;
	}

	case(DIR_BACK):{			
		direction = DIR_BACK;
		if(_z > 1.0){
			deltaT=glutGet(GLUT_ELAPSED_TIME)-t;
			_z-=speed*deltaT;
		}
		break;
	}

	case(DIR_LEFT):{
		direction = DIR_LEFT;
		if(_x<map_limit-1){
			deltaT=glutGet(GLUT_ELAPSED_TIME)-t;
			_x+=speed*deltaT;
		}
		break;
	}

	case(DIR_RIGHT):{
		direction = DIR_RIGHT;
		if(_x>1){
			deltaT=glutGet(GLUT_ELAPSED_TIME)-t;
			_x-=speed*deltaT;
		}
		break;
	}

	}
}

void Frog::tick(){

}

}

#include "../include/riverlog.h"

namespace domain {

	float Riverlog::logAmbient[4] = { 0.35f, 0.16f, 0.14f, 1.0f };
	float Riverlog::logDiffuse[4] = { 0.40f, 0.21f, 0.19f, 1.0f };
	float Riverlog::logSpec[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	float Riverlog::logShininess = 100;


	Riverlog::Riverlog(Vec3 position, Vec3 initSpeed) {
		_position = position;
		_initSpeed = initSpeed;
		_speed = initSpeed;

		body.createCylinder(LOG_HEIGHT, LOG_RADIOS, 50);
		body.setMaterialBlockName("Materials");
		body.setColor(VSResourceLib::SPECULAR, logSpec);
		body.setColor(VSResourceLib::DIFFUSE, logDiffuse);
		body.setColor(VSResourceLib::AMBIENT, logAmbient);
		body.setColor(VSResourceLib::SHININESS, &logShininess);

		AABB = new BoxAABB(&_position, LOG_HEIGHT, 1.0f, LOG_RADIOS*2);
	}

	Riverlog::~Riverlog(){
		delete AABB;
	}

	void Riverlog::draw(VSMathLib* core, VSShaderLib* shader){
		//if (x < -1 || x > 17)
		//	return;

		core->pushMatrix(VSMathLib::MODEL);
		core->translate(_position.getX(), _position.getY(), _position.getZ());
		core->rotate(90, 0, 0, 1);
		body.render();
		core->popMatrix(VSMathLib::MODEL);

	}

} /* namespace domain */

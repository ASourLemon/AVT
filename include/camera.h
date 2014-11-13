#ifndef CAMERA_H_
#define CAMERA_H_

#include <string.h>

namespace domain {
class Camera {
protected:
	float pos[3];
	float up[3];
	float at[3];
	float nearVal;
	float farVal;

public:
	Camera(float pos[3], float up[3], float at[3], float nearVal, float farVal);
	virtual ~Camera();
	float* getPos();
	float* getAtVector();
	virtual void update() = 0;
	virtual void load() = 0;

};

}

#endif /* CAMERA_H_ */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "camera.h"

namespace domain {
class PerspectiveCamera: public Camera {
private:
	float fovy;
	float ratio;

public:
	PerspectiveCamera(float pos[3], float up[3], float at[3], float nearVal, float farVal, float fovy, float ratio);
	~PerspectiveCamera();
	void update();
	void load();

};

}

#endif /* PERSPECTIVECAMERA_H_ */

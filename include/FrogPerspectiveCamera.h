#ifndef FROGPERSPECTIVECAMERA_H_
#define FROGPERSPECTIVECAMERA_H_

#include "camera.h"

namespace domain {
class FrogPerspectiveCamera: public Camera {
private:
	static FrogPerspectiveCamera *_instance;
	float fovy;
	float ratio;
	FrogPerspectiveCamera();

public:
	static FrogPerspectiveCamera *getInstance();
	~FrogPerspectiveCamera();
	void update();
	void load();

};

}

#endif /* FROGPERSPECTIVECAMERA_H_ */

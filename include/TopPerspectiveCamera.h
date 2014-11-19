#ifndef TOPPERSPECTIVECAMERA_H_
#define TOPPERSPECTIVECAMERA_H_

#include "camera.h"

namespace domain {
class TopPerspectiveCamera: public Camera {
private:
	static TopPerspectiveCamera *_instance;
	TopPerspectiveCamera();

public:
	static TopPerspectiveCamera *getInstance();
	~TopPerspectiveCamera();
	void update();
	void load();

};

}

#endif /* TOPPERSPECTIVECAMERA_H_ */

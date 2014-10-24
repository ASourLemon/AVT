#ifndef CAMERA_H_
#define CAMERA_H_

namespace domain {
class Camera {
private:
	float pos[3];
	float up[3];
	float at[3];
	float near;
	float far;

public:
	Camera(float pos[3], float up[3], float at[3], float near, float far);
	virtual ~Camera();
	virtual void update();
	virtual void load();

};

}

#endif /* CAMERA_H_ */

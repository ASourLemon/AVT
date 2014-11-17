#ifndef INCLUDE_DYNAMICOBJECT_H_
#define INCLUDE_DYNAMICOBJECT_H_

class DynamicObject : public GameObject {
public:
	virtual ~DynamicObject();
	void update(float time);
	void resetSpeed();
	void increaseSpeed();
	Vec3 getSpeed();
protected:
	Vec3 _initSpeed;
	Vec3 _speed;
};

#endif /* INCLUDE_DYNAMICOBJECT_H_ */

#ifndef INCLUDE_GAMEOBJECT_H_
#define INCLUDE_GAMEOBJECT_H_

class GameObject {
public:
	virtual ~GameObject();
	virtual void draw() = 0;
	virtual void update(float time) = 0;
protected:
	Vec3 _position;
};

#endif /* INCLUDE_GAMEOBJECT_H_ */

#ifndef INCLUDE_DYNAMICOBJECT_H_
#define INCLUDE_DYNAMICOBJECT_H_

#include "GameObject.h"

namespace domain {
	class DynamicObject : public GameObject {
	public:
		DynamicObject() { _nTicks = 0; }
		virtual ~DynamicObject() {}
		void update(float time);
		void resetSpeed();
		void increaseSpeed();
		Vec3 getSpeed();
	protected:
		Vec3 _initSpeed;
		Vec3 _speed;
	private:
		int _nTicks;
	};
}

#endif /* INCLUDE_DYNAMICOBJECT_H_ */

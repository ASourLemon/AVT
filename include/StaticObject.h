#ifndef INCLUDE_STATICOBJECT_H_
#define INCLUDE_STATICOBJECT_H_

#include "GameObject.h"

namespace domain {
	class StaticObject : public GameObject {
	public:
		virtual ~StaticObject() {}
		void update(float time){}
	};
}

#endif /* INCLUDE_STATICOBJECT_H_ */

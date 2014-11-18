#ifndef INCLUDE_GAMEOBJECT_H_
#define INCLUDE_GAMEOBJECT_H_

#include "Vec3.h"
#include <stdlib.h>
#include <list>
#include <math.h>
#include "vsMathLib.h"
#include "vsResSurfRevLib.h"
#include "BoxAABB.h"

namespace domain {
	class GameObject {
	public:
		virtual ~GameObject() {}
		virtual void draw(VSMathLib* core, VSShaderLib* shader) = 0;
		virtual void update(float time) = 0;
	protected:
		Vec3 _position;
	};
}

#endif /* INCLUDE_GAMEOBJECT_H_ */

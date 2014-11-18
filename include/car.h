#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

#include "DynamicObject.h"
#include "BoxAABB.h"

namespace domain {
	class Car : public DynamicObject {
	private:
		static float driverAmb[4];
		static float driverDif[4];
		static float driverSpec[4];
		static float driverShininess;

		static float loadAmb[4];
		static float loadDif[4];
		static float loadSpec[4];
		static float loadShininess;

		static float tireAmb[4];
		static float tireDif[4];
		static float tireSpec[4];
		static float tireShininess;
		BoxAABB *AABB;

	protected:
		std::list<VSResSurfRevLib> components;
		VSResSurfRevLib driver;
		VSResSurfRevLib tire;
		bool created;


	public:
		Car(float x, float y, float z, int direction, float velocity);
		~Car();
		void draw(VSMathLib* core, VSShaderLib* shader);
		BoxAABB * get_AABB(){ return AABB; }

	};

}
#endif

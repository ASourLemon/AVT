#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

#include "DynamicObject.h"
#include "BoxAABB.h"

#define CAR_SIZE_X 4.7f
#define CAR_SIZE_Y 1.2f
#define CAR_SIZE_Z 1.0f

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

		VSResSurfRevLib driver;
		VSResSurfRevLib tire;
		VSResSurfRevLib load;
		bool created;


	public:
		Car(Vec3 position, Vec3 initSpeed);
		~Car();
		void draw(VSMathLib* core, VSShaderLib* shader);
		BoxAABB * get_AABB(){ return AABB; }

	};

}
#endif

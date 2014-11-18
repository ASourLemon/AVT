#ifndef INCLUDE_RIVERLOG_H_
#define INCLUDE_RIVERLOG_H_
#include "DynamicObject.h"
#include "BoxAABB.h"

#define LOG_RADIOS 0.5f
#define LOG_HEIGHT 3.5f

namespace domain {

	class Riverlog : public DynamicObject {
	private:
		static float logAmbient[4];
		static float logDiffuse[4];
		static float logSpec[4];
		static float logShininess;
		BoxAABB *AABB;

	protected:
		VSResSurfRevLib body;

	public:
		Riverlog(Vec3 position, Vec3 initSpeed);
		~Riverlog();
		void draw(VSMathLib* core, VSShaderLib* shader);
		inline BoxAABB * get_AABB(){ return AABB; }
		inline float getX(){ return _position.getX(); }
		inline float getY(){ return _position.getY(); }
		inline float getZ(){ return _position.getZ(); }
	};

}

#endif

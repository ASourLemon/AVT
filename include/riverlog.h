#ifndef INCLUDE_RIVERLOG_H_
#define INCLUDE_RIVERLOG_H_
#include "drawable.h"
#include "BoxAABB.h"

#define LOG_RADIOS 0.5f
#define LOG_HEIGHT 3.5f

namespace domain {

	class Riverlog : public Drawable {
	private:
		static float logAmbient[4];
		static float logDiffuse[4];
		static float logSpec[4];
		static float logShininess;
		BoxAABB *AABB;

	protected:
		VSResSurfRevLib body;
		float x;
		float y;
		float z;
		float speed;
		int direction;


	public:
		Riverlog(float x, float y, float z, int quality, int direction, float velocity);
		~Riverlog();
		void draw(VSMathLib* core, VSShaderLib* shader);
		void tick();
		inline BoxAABB * get_AABB(){ return AABB; }
		inline int getDirection(){ return direction; }
		inline float getSpeed(){ return speed;}
		inline float getX(){ return x;}
		inline float getY(){ return y;}
		inline float getZ(){ return z;}
	};

}

#endif

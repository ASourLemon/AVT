#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "drawable.h"
//#include <iostream>
#include <cmath>

namespace domain{

	class Particle{

	public:
		Particle();
		~Particle();
	
		//void Draw();
		void Draw( VSMathLib* core);
		bool Update_particle(float elapsedTime, bool respawn);
		bool Respawn(bool spawn, int c);
		bool IsAlive() const { return life>0.0f; };
		bool IsDead()  const { return life<=0.0f; };

		void setColor(int c);


	private:
		VSResSurfRevLib body;
		float	life;		// life
		float	fade;		// fade
		float    x,  y,  z; // position
		float   vx, vy, vz; // speed
		float   ax, ay, az; // aceleration

		float alpha;

		bool created;
		int color;
	
		static float bodyAmbient[4];
		static float bodyDiffuse[4];
		static float bodySpec[4];
		static float bodyShininess;

		static float bodyAmbientS[4];
		static float bodyDiffuseS[4];
		static float bodySpecS[4];
		static float bodyShininessS;


	};

}
#endif

#ifndef _ParticleManager_H_
#define _ParticleManager_H_

//#include <iostream>
#include <list>
#include "drawable.h"
#include "Particle.h"

namespace domain{
	
	class ParticleManager{
	
	public:
		ParticleManager(bool burst);
		~ParticleManager();

		void Update(float elapsed);
		void Draw(VSMathLib* core);
		void Reset();

		void desactivar(std::list<ParticleManager*> *A, std::list<ParticleManager*> *I);
		void activar(float x, float y, std::list<ParticleManager*> *A, std::list<ParticleManager*> *I);

		std::list<Particle*> get_activeParticles(){return *activeParticles;}
	private:
	
		std::list<Particle*> *activeParticles;
		std::list<Particle*> *deadParticles;
	
		int	Max_Particles;
		bool respawnParticles;

		float _x, _y;

	};

}

#endif
#include "../include/ParticleManager.h"


namespace domain{

int Max_Particles = 1000;

ParticleManager::ParticleManager(bool burst){

	activeParticles = new std::list<Particle*>;
	deadParticles = new std::list<Particle*>;

	//Cria particula e coloca na lista
	for ( int i=0; i<100; i++){
        activeParticles->push_back( new Particle());
		respawnParticles = !burst;
	}
}

ParticleManager::~ParticleManager(){
	delete activeParticles;
	delete deadParticles;

}


void ParticleManager::Draw(VSMathLib* core){

	for(std::list<Particle*>::iterator x=activeParticles->begin(); x!=activeParticles->end(); x++){
		core->pushMatrix(VSMathLib::MODEL);
		core->translate(_x, _y, 0.0f);
		(*x)->Draw(core);
		core->popMatrix(VSMathLib::MODEL);

	}

}

void ParticleManager::Reset(){

	for(std::list<Particle*>::iterator x=activeParticles->begin(); x!=activeParticles->end(); x++){

		(*x)->Respawn( true);
	}



	for(std::list<Particle*>::iterator x=deadParticles->begin(); x!=deadParticles->end(); x = deadParticles->erase(x)){

		(*x)->Respawn();
		activeParticles->push_back(*x);
	}

}

void ParticleManager::Update(float elapsed){

	std::list<Particle*>::iterator it = activeParticles->begin();
    while ( it != activeParticles->end() ) {
		
        (*it)->Update_particle( elapsed, respawnParticles);
		if ( (*it)->IsAlive() )
			it++;
		else
		{
			deadParticles->push_back( *it);
			it = activeParticles->erase( it);
		}
    }
}

void ParticleManager::desactivar(std::list<ParticleManager*> *A, std::list<ParticleManager*> *I){
	I->push_back(this);
	A->remove(this);
}

void ParticleManager::activar(float x, float y, std::list<ParticleManager*> *A, std::list<ParticleManager*> *I){


	_x = x ;
	_y = y;
	
	A->push_back(this);
	I->remove(this);
	Reset();
}

}
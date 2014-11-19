#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <list>
#include "../include/drawable.h"
#include "../include/GameObject.h"
#include "../include/map.h"
#include "../include/frog.h"
#include "../include/car.h"
#include "../include/riverlog.h"
#include "../include/turtle.h"
#include "../include/lamp.h"
#include "../include/Tree.h"
#include "../include/PerspectiveCamera.h"
#include "../include/ParticleManager.h"
#include "../include/grass.h"

namespace domain {

class Game {

public:
	~Game();
	static Game *getInstance();
	void init();
	void draw(VSMathLib* core, VSShaderLib* shader);
	void add_drawable(Drawable* d);
	void move_frog(int d);
	void tick(VSMathLib* core);
	inline float getFrogX() {
		return frog->getX();
	}
	inline float getFrogY() {
		return frog->getY();
	}
	inline float getFrogZ() {
		return frog->getZ();
	}
	inline domain::Frog* getFrog() {
		return frog;
	}
	inline int getFrogLifes() {
		return frogLifes;
	}
	;
	inline int getFrogPoints() {
		return points;
	}
	;
	inline void setFrogPoints(int p) {
		points = p;
	}
	;
	inline void setFrogLifes(int lifes) {
		frogLifes = lifes;
	}
	;
	void setFrogT(int i);

	float sqDistPointAABB(float x, float y, float z, BoxAABB *aabb);
	bool testCircleAABB(BoxSphere *sphere, BoxAABB *aabb);
	void loadCamera();
	Camera *getActiveCamera() { return activeCam; }
	void UpdateParticles(VSMathLib* core, float elaped);

private:
	Game();
	void computeCollisions();
	static Game *_instance;
	std::vector<Drawable*> game_objects;
	std::vector<GameObject*> refactored_game_objects;
	std::vector<Car*> cars;
	std::vector<Riverlog*> riverlogs;
	std::vector<Turtle*> turtles;
	std::vector<Lamp*> lamps;
	Frog* frog;

	PerspectiveCamera* frogCam;
	Camera* activeCam;

	std::vector<ParticleManager*> Particletemp;
	std::list<ParticleManager*> *list_particle_system_I, *list_particle_system_A;

	bool _burst;
	float lastTime;

	Map* map;

	//Reflection Lamps
	Lamp* lamp7;
	Lamp* lamp8;
	Lamp* lamp9;
	Lamp* lamp10;

	int frogLifes;
	int points;

	bool beingCarried;
	bool falling;
	float distFalling;
};

}
#endif

#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <list>
#include "../include/drawable.h"
#include "../include/map.h"
#include "../include/frog.h"
#include "../include/car.h"
#include "../include/riverlog.h"
#include "../include/turtle.h"
#include "../include/lamp.h"

namespace domain {

class Game {
private:
	std::vector<Drawable*> game_objects;
	std::vector<Car*> cars;
	std::vector<Riverlog*> riverlogs;
	std::vector<Turtle*> turtles;
	std::vector<Lamp*> lamps;
	Frog* frog;
	Map* map;
	Car* car1;
	Car* car2;
	Car* car3;
	Car* car4;

	Riverlog* rlog1;
	//Riverlog* rlog2;
	Riverlog* rlog3;
	//Riverlog* rlog4;

	Turtle* turtle1;
	Turtle* turtle2;

	Lamp* lamp1;
	Lamp* lamp2;
	Lamp* lamp3;
	Lamp* lamp4;
	Lamp* lamp5;
	Lamp* lamp6;
	
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

public:
	Game();
	~Game();
	void init();
	void draw(VSMathLib* core);
	void add_drawable(Drawable* d);
	void move_frog(int d);
	void tick();
	inline float getFrogX() {
		return frog->getX();
	}
	inline float getFrogY() {
		return frog->getY();
	}
	inline float getFrogZ() {
		return frog->getZ();
	}
	inline domain::Frog* getFrog(){
		return frog;
	}
	inline int getFrogLifes(){ return frogLifes;};
	inline int getFrogPoints(){ return points;};
	inline void setFrogPoints(int p){ points = p;};
	inline void setFrogLifes(int lifes){ frogLifes = lifes;};
	void setFrogT(int i);

	float sqDistPointAABB(float x, float y, float z, BoxAABB *aabb);
	bool testCircleAABB(BoxSphere *sphere, BoxAABB *aabb);
};

}
#endif

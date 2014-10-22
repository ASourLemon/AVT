#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <list>
#include "../include/drawable.h"
#include "../include/map.h"
#include "../include/frog.h"
#include "../include/car.h"
#include "../include/riverlog.h"
#include "../include/light.h"

namespace domain {

class Game {
private:
	std::vector<Drawable*> game_objects;
	Frog* frog;
	Map* map;
	Car* car1;
	Car* car2;
	Car* car3;
	Car* car4;

	Riverlog* rlog1;
	Riverlog* rlog2;
	Riverlog* rlog3;
	Riverlog* rlog4;


public:
	Game();
	~Game();
	void init();
	void draw(VSMathLib* core);
	void add_drawable(Drawable* d);
	void move_frog(int d);
	void tick();
	inline float getFrogX(){return frog->getX();}
	inline float getFrogY(){return frog->getY();}
	inline float getFrogZ(){return frog->getZ();}
	void setFrogT1(int i);
	void setFrogT2(int i);
	void setFrogT3(int i);
	void setFrogT4(int i);
};



}
#endif

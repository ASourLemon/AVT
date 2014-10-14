#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <list>
#include "drawable.h"
#include "map.h"
#include "frog.h"


namespace domain {

class Game {
private:
	std::vector<Drawable*> game_objects;
	Frog* frog;


public:
	Game();
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

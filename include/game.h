#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <list>
#include "drawable.h"
#include "map.h"


namespace domain {

class Game {
private:
	std::vector<Drawable*> game_objects;


public:
	Game();
	void init();
	void draw(VSMathLib* core);
	void add_drawable(Drawable* d);
};



}
#endif

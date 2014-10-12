#include "../include/game.h"

namespace domain {

Game::Game() {

}

void Game::init(){
	game_objects.push_back(new Map());
}

void Game::draw(VSMathLib* core){

	for(unsigned int i = 0; i < game_objects.size(); i++){

		game_objects.at(i)->draw(core);

	}

}

void Game::add_drawable(Drawable* d){

	game_objects.push_back(d);

}

}

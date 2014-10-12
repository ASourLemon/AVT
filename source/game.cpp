#include "../include/game.h"
#include "../include/car.h"

namespace domain {

Game::Game() {

}

void Game::init(){
	game_objects.push_back(new Map());
	game_objects.push_back(new Car(3.0, 0.0, 7.0));
	game_objects.push_back(new Car(3.0, 0.0, 5.0));
	game_objects.push_back(new Car(3.0, 0.0, 9.0));
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

#include "../include/game.h"
#include "../include/riverlog.h"
#include "../include/car.h"
#include "../include/frog.h"

namespace domain {

	Game::Game() {

	}

	void Game::init(){

		game_objects.push_back(new Frog());

		game_objects.push_back(new Map());

		game_objects.push_back(new Car(1.0, 0.0, 6.0));
		game_objects.push_back(new Car(5.0, 0.0, 4.0));

		game_objects.push_back(new Riverlog(2.0, -1.0, 10.0, 50));
		game_objects.push_back(new Riverlog(7.0, -1.0, 12.0, 50));
	}

	void Game::draw(VSMathLib* core){

		for (unsigned int i = 0; i < game_objects.size(); i++){

			game_objects.at(i)->draw(core);

		}

	}

	void Game::add_drawable(Drawable* d){

		game_objects.push_back(d);

	}

}

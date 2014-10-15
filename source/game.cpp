#include "../include/game.h"
#include "../include/riverlog.h"
#include "../include/car.h"
#include "../include/frog.h"

namespace domain {

	Game::Game() {

	}


void Game::init(){
	frog = new Frog(5.0, 0.0, 1.0, 0.01);
	game_objects.push_back(frog);

		game_objects.push_back(new Map());

		game_objects.push_back(new Car(-4.0, 0.3, 6.0, DIR_LEFT, 0.2));
		game_objects.push_back(new Car(-6.0, 0.3, 4.0, DIR_LEFT, 0.2));

		game_objects.push_back(new Riverlog(2.0, -1.0, 10.0, 50, DIR_LEFT, 0.2));
		game_objects.push_back(new Riverlog(7.0, -1.0, 12.0, 50, DIR_RIGHT, 0.2));
	}

	void Game::draw(VSMathLib* core){

		for (unsigned int i = 0; i < game_objects.size(); i++){

			game_objects.at(i)->draw(core);

		}

	}

	void Game::add_drawable(Drawable* d){

		game_objects.push_back(d);

	}

void Game::move_frog(int d){
	frog->move(d);
}

void Game::setFrogT1(int i){
	frog->setT1(i);
}
void Game::setFrogT2(int i){
	frog->setT2(i);
}
void Game::setFrogT3(int i){
	frog->setT3(i);
}
void Game::setFrogT4(int i){
	frog->setT4(i);
}


void Game::tick(){

	for (unsigned int i = 0; i < game_objects.size(); i++){
		game_objects.at(i)->tick();
	}

}


}

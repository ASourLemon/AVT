#include "../include/game.h"


namespace domain {

	Game::Game() {

	}

	Game::~Game(){
		delete frog;
		delete map;
		delete car1;
		delete car2;
		delete car3;
		delete car4;
	}


	void Game::init(){
		frog = new Frog(10.0, 0.0, 1.0, 0.01);
		game_objects.push_back(frog);

		map = new Map();
		game_objects.push_back(map);

		car1 = new Car(-4.0, 0.3, 6.0, DIR_LEFT, 0.2);
		game_objects.push_back(car1);
		car2 = new Car(-6.0, 0.3, 4.0, DIR_LEFT, 0.2);
		game_objects.push_back(car2);
		car3 = new Car(-4.0, 0.3, 8.0, DIR_RIGHT, 0.2);
		game_objects.push_back(car3);
		car4 = new Car(-6.0, 0.3, 10.0, DIR_RIGHT, 0.2);
		game_objects.push_back(car4);

		rlog1 = new Riverlog(2.0, -0.5, 17.0, 50, DIR_LEFT, 0.2);
		game_objects.push_back(rlog1);
		rlog2 = new Riverlog(7.0, -0.5, 19.0, 50, DIR_RIGHT, 0.2);
		game_objects.push_back(rlog2);
		rlog3 = new Riverlog(2.0, -0.5, 21.0, 50, DIR_LEFT, 0.2);
		game_objects.push_back(rlog3);
		rlog4 = new Riverlog(7.0, -0.5, 23.0, 50, DIR_RIGHT, 0.2);
		game_objects.push_back(rlog4);

		frog->setMaplimit(map->getMaplimit());
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

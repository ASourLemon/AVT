#include "../include/game.h"

namespace domain {

	Game *Game::_instance = 0;
	float delta = 0.0f;

	Game::Game() : frogLifes(3), points(0), beingCarried(false), falling(false), distFalling(0.0) {

	}

	Game::~Game() {
		delete tree;
		delete frog;
		delete map;
		delete car1;
		delete car2;
		delete car3;
		delete car4;
		delete rlog1;
		//delete rlog2;
		delete rlog3;
		//delete rlog4;
		delete turtle1;
		delete turtle2;
		delete turtle3;
		delete turtle4;
		delete turtle5;
		delete turtle6;
		delete lamp1;
		delete lamp2;
		delete lamp3;
		delete lamp4;
		delete lamp5;
		delete lamp6;
		delete lamp7;
		delete lamp8;
	}

	void Game::init() {

		frog = new Frog(10.0, 0.0, 1.0, 0.01, DIR_BACK);

		map = new Map();
		car1 = new Car(-6.0, 0.3, 4.0, DIR_LEFT, 0.5);
		cars.push_back(car1);

		car2 = new Car(-6.0, 0.3, 6.0, DIR_LEFT, 1.2);
		cars.push_back(car2);

		car3 = new Car(-4.0, 0.3, 9.0, DIR_RIGHT, 1.2);
		cars.push_back(car3);
		car4 = new Car(-6.0, 0.3, 11.0, DIR_RIGHT, 0.5);
		cars.push_back(car4);

		rlog1 = new Riverlog(2.0, -0.5, 17.0, 50, DIR_LEFT, 0.2);
		riverlogs.push_back(rlog1);
		rlog3 = new Riverlog(2.0, -0.5, 21.0, 50, DIR_LEFT, 0.2);
		riverlogs.push_back(rlog3);


		turtle1 = new Turtle(5.0, -.5, 19.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle1);
		turtle2 = new Turtle(10.0, -.5, 19.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle2);
		turtle3 = new Turtle(15.0, -.5, 19.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle3);
		turtle4 = new Turtle(15.0, -.5, 23.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle4);
		turtle5 = new Turtle(10.0, -.5, 23.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle5);
		turtle6 = new Turtle(5.0, -.5, 23.0, DIR_RIGHT, 0.2);
		turtles.push_back(turtle6);

		lamp1 = new Lamp(15.0f, 0.0f, 15.0f, false);
		lamps.push_back(lamp1);
		lamp2 = new Lamp(15.0f, 0.0f, 26.0f, false);
		lamps.push_back(lamp2);
		lamp3 = new Lamp(15.0f, 0.0f, 1.0f, false);
		lamps.push_back(lamp3);
		lamp4 = new Lamp(5.0f, 0.0f, 15.0f, false);
		lamps.push_back(lamp4);
		lamp5 = new Lamp(5.0f, 0.0f, 26.0f, false);
		lamps.push_back(lamp5);
		lamp6 = new Lamp(5.0f, 0.0f, 1.0f, false);
		lamps.push_back(lamp6);

		//Reflection lamps
		lamp7 = new Lamp(15.0f, 0.0f, 15.0f, true);
		lamp8 = new Lamp(5.0f, 0.0f, 15.0f, true);
		lamp9 = new Lamp(15.0f, 0.0f, 26.0f, true);
		lamp10 = new Lamp(5.0f, 0.0f, 26.0f, true);

		frog->setMaplimit(map->getMaplimit());

		tree = new Tree();

	}

	Game *Game::getInstance() {
		if (_instance == 0) {
			_instance = new Game();
		}
		return _instance;
	}

	void Game::draw(VSMathLib* core, VSShaderLib* shader) {

		tree->draw(core, shader);

		//for (unsigned int i = 0; i < game_objects.size(); i++)
		//game_objects.at(i)->draw(core);
		frog->draw(core, shader);

		map->draw(core, shader);

		//glDisable(GL_STENCIL_TEST);
		//Normal lamps
		for (unsigned int i = 0; i < lamps.size(); i++)
			lamps.at(i)->draw(core, shader);

		//int pos_loc = glGetUniformLocation(shader->getProgramIndex(), "vertex_moving");
		//glUniform1i(pos_loc, true);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Reflection lamps
		lamp7->draw(core, shader);
		lamp8->draw(core, shader);
		lamp9->draw(core, shader);
		lamp10->draw(core, shader);
		glEnable(GL_BLEND);
		//glUniform1i(pos_loc, false);


		for (unsigned int i = 0; i < cars.size(); i++)
			cars.at(i)->draw(core, shader);
		for (unsigned int i = 0; i < riverlogs.size(); i++)
			riverlogs.at(i)->draw(core, shader);
		for (unsigned int i = 0; i < turtles.size(); i++)
			turtles.at(i)->draw(core, shader);
	}

	void Game::move_frog(int direction) {
		frog->move(direction);
	}

	void Game::setFrogT(int i) {
		frog->setT(i);
	}

	void Game::tick() {
		if (frogLifes == 0){
			return;
		}

		if (falling){
			float d = 0.12;
			distFalling += d;
			frog->setY(frog->getY() - d);
			if (distFalling > 2.0){
				//dead
				frogLifes--;
				falling = false;
				frog->setX(10.0);
				frog->setY(0.0);
				frog->setZ(1.0);
				distFalling = 0.0;
			}

		}
		if (frog->isCompressed()){
			if (frog->getCompress() > 0.0001){
				frog->setCompressedR(frog->getCompress() - 0.04);
			}
			else {
				frog->setX(10.0);
				frog->setY(0.0);
				frog->setZ(1.0);
				frogLifes--;
				frog->setCompressedR(1.0);
				frog->setCompressed(false);
			}
		}

		//for (unsigned int i = 0; i < game_objects.size(); i++)
		//game_objects.at(i)->tick();
		frog->tick();
		map->tick();

		if (testCircleAABB(frog->get_Sphere(), map->getWinBox())){
			frog->setX(10.0);
			frog->setY(0.0);
			frog->setZ(1.0);
			points++;
			printf("Well done!\n");

		}

		for (unsigned int i = 0; i < cars.size(); i++)
			cars.at(i)->tick();
		for (unsigned int i = 0; i < riverlogs.size(); i++)
			riverlogs.at(i)->tick();
		for (unsigned int i = 0; i < turtles.size(); i++)
			turtles.at(i)->tick();

		bool log = false;
		//Collision Frog vs Riverlogs
		for (unsigned int i = 0; i < riverlogs.size(); i++) {

			if (testCircleAABB(frog->get_Sphere(), riverlogs.at(i)->get_AABB())) {
				log = true;
				beingCarried = true;
				float d = (float)riverlogs.at(i)->getSpeed() * 0.1;

				if (riverlogs.at(i)->getDirection() == DIR_RIGHT){

					frog->setX(frog->getX() - d);

				}
				else if (riverlogs.at(i)->getDirection() == DIR_LEFT){

					frog->setX(frog->getX() + d);

				}
			}
		}
		if (!log){
			beingCarried = false;
		}
		log = false;

		//Collision Frog vs Turtles
		for (unsigned int i = 0; i < turtles.size(); i++) {
			if (testCircleAABB(frog->get_Sphere(), turtles.at(i)->get_AABB())) {
				log = true;
				beingCarried = true;
				float d = (float)turtles.at(i)->getSpeed() * 0.1;
				if (turtles.at(i)->getDirection() == DIR_RIGHT){

					frog->setX(frog->getX() - d);

				}
				else if (turtles.at(i)->getDirection() == DIR_LEFT){

					frog->setX(frog->getX() + d);

				}
			}
		}
		if ((frog->getZ() >= 16.5) && (frog->getZ() <= 23.5)){
			//it's on water!
			if (!beingCarried){
				printf("SPLASH\n");
				falling = true;

			}
		}
		for (unsigned int i = 0; i < cars.size(); i++) {
			if (testCircleAABB(frog->get_Sphere(), cars.at(i)->get_AABB())) {
				frog->setCompressed(true);
			}
		}
		//Collision Frog vs Lamps
		/*for (unsigned int i = 0; i < lamps.size(); i++) {
			if (testCircleAABB(frog->get_Sphere(), lamps.at(i)->get_AABB())) {

			}
			}*/

	}

	float Game::sqDistPointAABB(float x, float y, float z, BoxAABB *aabb) {
		float sqDist = 0.0;
		float v;
		float minX, minY, minZ, maxX, maxY, maxZ;

		// get the minX, maxX, minY, maxY and minZ, maxZ points of the AABB
		minX = aabb->get_xmin();
		maxX = aabb->get_xmax();
		minY = aabb->get_ymin();
		maxY = aabb->get_ymax();
		minZ = aabb->get_zmin();
		maxZ = aabb->get_zmax();

		// test the bounds against the points X axis
		v = x;

		if (v < minX)
			sqDist += (minX - v) * (minX - v);
		if (v > maxX)
			sqDist += (v - maxX) * (v - maxX);

		// test the bounds against the points Y axis
		v = y;

		if (v < minY)
			sqDist += (minY - v) * (minY - v);
		if (v > maxY)
			sqDist += (v - maxY) * (v - maxY);

		// test the bounds against the points Z axis
		v = z;

		if (v < minZ)
			sqDist += (minZ - v) * (minZ - v);
		if (v > maxZ)
			sqDist += (v - maxZ) * (v - maxZ);

		return sqDist;

	}

	bool Game::testCircleAABB(BoxSphere *sphere, BoxAABB *aabb) {

		float x = sphere->get_x();
		float y = sphere->get_y();
		float z = sphere->get_z();

		// get the squared distance between sphere center and the AABB

		float sqDist = sqDistPointAABB(x, y, z, aabb);
		float r = sphere->get_raio();

		return sqDist <= r * r;
	}

}

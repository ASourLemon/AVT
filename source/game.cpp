#include "../include/game.h"

namespace domain {

	Game *Game::_instance = 0;
	float delta = 0.0f;

	Game::Game() : frogLifes(3), points(0), beingCarried(false), falling(false), distFalling(0.0), _burst(true) {

		lastTime = glutGet( GLUT_ELAPSED_TIME);
	}

	Game::~Game() {
		delete tree1;
		delete tree2;
		delete tree3;
		delete frog;
		delete map;
		delete car1;
		delete car2;
		delete car3;
		delete car4;
		delete rlog1;
		delete rlog3;
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
		delete list_particle_system_I;
		delete list_particle_system_A;
	}

	void Game::init() {

		frog = new Frog(10.0f, 0.0f, 1.0f, 0.01f, DIR_BACK);

		float pos[3] = {1.0f, 1.0f, 2.0f};
		float up[3] = {0.0f, 1.0f, 0.0f};
		float at[3] = {1.0f, 1.0f, 5.0f};
		frogCam = new PerspectiveCamera(pos, up, at, 0.1f, 20.0f, 45.0f, 1.3f);
		activeCam = frogCam;

		map = new Map();
		car1 = new Car(-6.0f, 0.3f, 4.0f, DIR_LEFT, 0.5f);
		cars.push_back(car1);

		car2 = new Car(-6.0f, 0.3f, 6.0f, DIR_LEFT, 1.2f);
		cars.push_back(car2);

		car3 = new Car(-4.0f, 0.3f, 9.0f, DIR_RIGHT, 1.2f);
		cars.push_back(car3);
		car4 = new Car(-6.0f, 0.3f, 11.0f, DIR_RIGHT, 0.5f);
		cars.push_back(car4);

		rlog1 = new Riverlog(2.0f, -0.5f, 17.0f, 50.0f, DIR_LEFT, 0.2f);
		riverlogs.push_back(rlog1);
		rlog3 = new Riverlog(2.0f, -0.5f, 21.0f, 50.0f, DIR_LEFT, 0.2f);
		riverlogs.push_back(rlog3);


		turtle1 = new Turtle(5.0f, -.5f, 19.0f, DIR_RIGHT, 0.2f);
		turtles.push_back(turtle1);
		turtle2 = new Turtle(10.0f, -.5f, 19.0f, DIR_RIGHT, 0.2f);
		turtles.push_back(turtle2);
		turtle3 = new Turtle(15.0f, -.5, 19.0f, DIR_RIGHT, 0.2f);
		turtles.push_back(turtle3);
		turtle4 = new Turtle(15.0f, -.5f, 23.0f, DIR_RIGHT, 0.2f);
		turtles.push_back(turtle4);
		turtle5 = new Turtle(10.0f, -.5f, 23.0f, DIR_RIGHT, 0.2f);
		turtles.push_back(turtle5);
		turtle6 = new Turtle(5.0f, -.5f, 23.0f, DIR_RIGHT, 0.2f);
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

		tree1 = new Tree(3.0f, 15.0f);
		tree2 = new Tree((17.0-3.0)/2.0+3.0, 15.0f);
		tree3 = new Tree(17.0f, 15.0f);

		list_particle_system_I = new std::list<ParticleManager*>;
		list_particle_system_A = new std::list<ParticleManager*>;

		//cria 50 sistemas de particulas
		for(int x=0; x<5; x++){
			list_particle_system_I->push_back( new ParticleManager(_burst));
		}


	}

	Game *Game::getInstance() {
		if (_instance == 0) {
			_instance = new Game();
		}
		return _instance;
	}

	void Game::draw(VSMathLib* core, VSShaderLib* shader) {
		//for (unsigned int i = 0; i < game_objects.size(); i++)
		//game_objects.at(i)->draw(core);
		frog->draw(core, shader);

		map->draw(core, shader);

		//glDisable(GL_STENCIL_TEST);
		//Normal lamps
		for (unsigned int i = 0; i < lamps.size(); i++)
			lamps.at(i)->draw(core, shader);


		for (unsigned int i = 0; i < cars.size(); i++)
			cars.at(i)->draw(core, shader);
		for (unsigned int i = 0; i < riverlogs.size(); i++)
			riverlogs.at(i)->draw(core, shader);
		for (unsigned int i = 0; i < turtles.size(); i++)
			turtles.at(i)->draw(core, shader);


		//int pos_loc = glGetUniformLocation(shader->getProgramIndex(), "vertex_moving");
		//glUniform1i(pos_loc, true);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Reflection lamps
		lamp7->draw(core, shader);
		lamp8->draw(core, shader);
		lamp9->draw(core, shader);
		lamp10->draw(core, shader);
		//glUniform1i(pos_loc, false);

		tree1->draw(core, shader);
		tree2->draw(core, shader);
		tree3->draw(core, shader);

		glDisable(GL_BLEND);
	}

	void Game::move_frog(int direction) {
		frog->move(direction);
	}

	void Game::setFrogT(int i) {
		frog->setT(i);
	}

	void Game::tick(VSMathLib* core) {

		float now    = glutGet( GLUT_ELAPSED_TIME);
		float elaped = now - lastTime;
		lastTime   = now;

		if (frogLifes == 0){
			return;
		}

		if (falling){
			float d = 0.12f;
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
				float d = (float)riverlogs.at(i)->getSpeed() * 0.1f;

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
				float d = (float)turtles.at(i)->getSpeed() * 0.1f;
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
		//Collision Frog vs Cars
		for (unsigned int i = 0; i < cars.size(); i++) {
			if (testCircleAABB(frog->get_Sphere(), cars.at(i)->get_AABB())) {
				frog->setCompressed(true);
				list_particle_system_I->front()->activar(frog->getX(),frog->getY(), list_particle_system_A, list_particle_system_I);
				break;
			}
		}
		//Collision Frog vs Lamps
		/*for (unsigned int i = 0; i < lamps.size(); i++) {
			if (testCircleAABB(frog->get_Sphere(), lamps.at(i)->get_AABB())) {

			}
			}*/
		//Update dos sistemas de particulas
		core->pushMatrix(VSMathLib::MODEL);
		for(std::list<ParticleManager*>::iterator x=list_particle_system_A->begin(); x!=list_particle_system_A->end(); x++){

			if(!(*x)->get_activeParticles().empty()){
					(*x)->Update(elaped);
					(*x)->Draw(core);
			}
			else Particletemp.push_back(*x);
		}
		core->popMatrix(VSMathLib::MODEL);
		for(std::vector<ParticleManager*>::iterator i=Particletemp.begin(); i!=Particletemp.end(); i++)
			(*i)->desactivar(list_particle_system_A, list_particle_system_I);
		Particletemp.clear();
		//UpdateParticles(core, elaped);

		activeCam->update(); //FIXME: actualizar as outras tambem

	}

	float Game::sqDistPointAABB(float x, float y, float z, BoxAABB *aabb) {
		float sqDist = 0.0f;
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

	void Game::loadCamera() {
		activeCam->load();
	}

	void UpdateParticles(VSMathLib* core, float elaped){
		
	
	}


}

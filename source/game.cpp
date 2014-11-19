#include "../include/game.h"

namespace domain {

Game *Game::_instance = 0;
float delta = 0.0f;

Game::Game() :
		frogLifes(3), points(0), beingCarried(false), falling(false), distFalling(
				0.0), _burst(true) {

	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

Game::~Game() {
	for (unsigned int i = 0; i < game_objects.size(); i++) {
		delete game_objects.at(i);
	}
	for (unsigned int i = 0; i < refactored_game_objects.size(); i++) {
		delete refactored_game_objects.at(i);
	}
}

void Game::init() {

	frog = new Frog(10.0f, 0.0f, 1.0f, 0.01f, DIR_BACK);

	float pos[3] = { 1.0f, 1.0f, 2.0f };
	float up[3] = { 0.0f, 1.0f, 0.0f };
	float at[3] = { 1.0f, 1.0f, 5.0f };
	frogCam = new PerspectiveCamera(pos, up, at, 0.1f, 20.0f, 45.0f, 1.3f);
	activeCam = frogCam;

	map = new Map();
	Drawable *d = map;
	game_objects.push_back(d);

	const float UNITS_PER_SECOND = 2.0f;
	const float TICKS_PER_SECOND = 60.0f;
	const float UNITS_PER_TICK = UNITS_PER_SECOND / TICKS_PER_SECOND;
	Vec3 car_speed_right = Vec3(UNITS_PER_TICK, 0.0f, 0.0f);
	Vec3 car_speed_left = car_speed_right * (-1);
	Vec3 car_positions[] = { Vec3(-6.0f, CAR_SIZE_Y / 2, 4.0f), Vec3(-6.0f, CAR_SIZE_Y / 2, 6.0f),
		Vec3(-4.0f, CAR_SIZE_Y / 2, 9.0f), Vec3(-6.0f, CAR_SIZE_Y / 2, 11.0f) };
	Car *car;
	for (int i = 0; i < 4; i++) {
		car = new Car(car_positions[i],
				(i < 2) ? car_speed_left : car_speed_right);
		cars.push_back(car);
		refactored_game_objects.push_back(car);
//			game_objects.push_back(c);
	}

	Vec3 riverlogs_positions[] = { Vec3(2.0f, -0.5f, 17.0f), Vec3(2.0f, -0.5f,
			21.0f) };
	// FIXME: set specific speeds for logs
	Riverlog *r;
	for (int i = 0; i < 2; i++) {
		r = new Riverlog(riverlogs_positions[i],
				(i < 1) ? car_speed_left : car_speed_right);
		riverlogs.push_back(r);
		refactored_game_objects.push_back(r);
		//			game_objects.push_back(r);
	}

	Vec3 turtles_positions[] = { Vec3(5.0f, -.5f, 19.0f), Vec3(10.0f, -.5f,
			19.0f), Vec3(15.0f, -.5f, 19.0f), Vec3(5.0f, -.5f, 23.0f), Vec3(
			10.0f, -.5f, 23.0f), Vec3(15.0f, -.5f, 23.0f) };
	// FIXME: set specific speeds for logs
	Turtle *turtle;
	for (int i = 0; i < 6; i++) {
		turtle = new Turtle(turtles_positions[i],
				(i < 3) ? car_speed_left : car_speed_right);
		turtles.push_back(turtle);
		refactored_game_objects.push_back(turtle);
//			game_objects.push_back(turtle);
	}

	//FIXME: CONVERT THESE TO EXTEND STATIC OBJECT CLASS
	Lamp *l = new Lamp(15.0f, 0.0f, 15.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);
	l = new Lamp(15.0f, 0.0f, 26.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);
	l = new Lamp(15.0f, 0.0f, 1.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);
	l = new Lamp(5.0f, 0.0f, 15.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);
	l = new Lamp(5.0f, 0.0f, 26.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);
	l = new Lamp(5.0f, 0.0f, 1.0f, false);
	lamps.push_back(l);
	game_objects.push_back(l);

	//Reflection lamps
	lamp7 = new Lamp(15.0f, 0.0f, 15.0f, true);
	lamp8 = new Lamp(5.0f, 0.0f, 15.0f, true);
	lamp9 = new Lamp(15.0f, 0.0f, 26.0f, true);
	lamp10 = new Lamp(5.0f, 0.0f, 26.0f, true);

	frog->setMaplimit(map->getMaplimit());

	Tree *tree = new Tree(3.0f, 15.0f);
	game_objects.push_back(tree);
	tree = new Tree(10.0f, 15.0f);
	game_objects.push_back(tree);
	tree = new Tree(17.0f, 15.0f);
	game_objects.push_back(tree);

	Grass *grass = new Grass(10.0f, 15.0f, false);
	game_objects.push_back(grass);
	grass = new Grass(10.0f, 15.0f, true);
	game_objects.push_back(grass);
	grass = new Grass(5.0f, 15.0f, false);
	game_objects.push_back(grass);
	grass = new Grass(5.0f, 15.0f, true);
	game_objects.push_back(grass);
	grass = new Grass(15.0f, 15.0f, false);
	game_objects.push_back(grass);
	grass = new Grass(15.0f, 15.0f, true);
	game_objects.push_back(grass);

	for(float i = 28.0f; i<=31.0f; i+=0.75){
		for(float j = 6.0f; j <= 14.0f; j+=0.75){
			grass = new Grass(j, i, false);
			game_objects.push_back(grass);
			grass = new Grass(j, i, true);
			game_objects.push_back(grass);
		}
	}

	list_particle_system_I = new std::list<ParticleManager*>;
	list_particle_system_A = new std::list<ParticleManager*>;

	//cria 5 sistemas de particulas
	for (int x = 0; x < 50; x++) {
		list_particle_system_I->push_back(new ParticleManager(_burst));
	}

}

Game *Game::getInstance() {
	if (_instance == 0) {
		_instance = new Game();
	}
	return _instance;
}

void Game::draw(VSMathLib* core, VSShaderLib* shader) {
	frog->draw(core, shader);

	for (unsigned int i = 0; i < game_objects.size(); i++) {
		game_objects.at(i)->draw(core, shader);
	}
	for (unsigned int i = 0; i < refactored_game_objects.size(); i++) {
		refactored_game_objects.at(i)->draw(core, shader);
	}

	//Reflection lamps
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	lamp7->draw(core, shader);
	lamp8->draw(core, shader);
	lamp9->draw(core, shader);
	lamp10->draw(core, shader);
	glDisable(GL_BLEND);

	for (std::list<ParticleManager*>::iterator x =
			list_particle_system_A->begin(); x != list_particle_system_A->end();
			x++) {

		if (!(*x)->get_activeParticles().empty()) {
			(*x)->Draw(core);
		} else
			Particletemp.push_back(*x);
	}
}

void Game::move_frog(int direction) {
	if(!frog->isCompressed()){
		frog->move(direction);
	}

}

void Game::setFrogT(int i) {
	frog->setT(i);
}

void Game::tick(VSMathLib* core) {
	float now = glutGet(GLUT_ELAPSED_TIME);
	float elaped = now - lastTime;
	lastTime = now;

	if (frogLifes == 0) {
		return;
	}

	if (falling) {
		float d = 0.12f;
		distFalling += d;
		frog->setY(frog->getY() - d);
		if (distFalling > 2.0) {
			//dead
			frogLifes--;
			falling = false;
			frog->setX(10.0);
			frog->setY(0.0);
			frog->setZ(1.0);
			distFalling = 0.0;
		}

	}
	if (frog->isCompressed()) {
		if (frog->getCompress() > 0.0001) {
			frog->setCompressedR(frog->getCompress() - 0.04);
		} else {
			frog->setX(10.0);
			frog->setY(0.0);
			frog->setZ(1.0);
			frogLifes--;
			frog->setCompressedR(1.0);
			frog->setCompressed(false);
		}
	}else {
		frog->tick();
	}


	for (unsigned int i = 0; i < game_objects.size(); i++) {
		game_objects.at(i)->tick();
	}
	for (unsigned int i = 0; i < refactored_game_objects.size(); i++) {
		refactored_game_objects.at(i)->update(1.0);
	}

	computeCollisions();

	UpdateParticles(core, elaped);

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

void Game::UpdateParticles(VSMathLib* core, float elaped) {

	//Update dos sistemas de particulas
	core->pushMatrix(VSMathLib::MODEL);
	for (std::list<ParticleManager*>::iterator x =
			list_particle_system_A->begin(); x != list_particle_system_A->end();
			x++) {

		if (!(*x)->get_activeParticles().empty()) {
			(*x)->Update(elaped);
		} else
			Particletemp.push_back(*x);
	}
	core->popMatrix(VSMathLib::MODEL);
	for (std::vector<ParticleManager*>::iterator i = Particletemp.begin();
			i != Particletemp.end(); i++)
		(*i)->desactivar(list_particle_system_A, list_particle_system_I);
	Particletemp.clear();
	//UpdateParticles(core, elaped);
}

void Game::computeCollisions() {
	/*
	 if (testCircleAABB(frog->get_Sphere(), map->getWinBox())) {
	 frog->setX(10.0);
	 frog->setY(0.0);
	 frog->setZ(1.0);
	 points++;
	 printf("Well done!\n");

	 }
	 */
	/*bool wonPoint = frog->getZ() > 30.0f;
	if (wonPoint) {
		frog->setX(10.0);
		frog->setY(0.0);
		frog->setZ(1.0);
		points++;
	}

	beingCarried = false;
	//Collision Frog vs Riverlogs
	for (unsigned int i = 0; i < riverlogs.size() ; i++) {

		if (testCircleAABB(frog->get_Sphere(), riverlogs.at(i)->get_AABB())) {
			beingCarried = true;
			// TODO: If we change frog implementation, this will be easier to write/read
			Vec3 d = riverlogs.at(i)->getSpeed();
			Vec3 frog_pos = Vec3(frog->getX(), frog->getY(), frog->getZ());
			frog_pos = frog_pos + d;
			frog->setX(frog_pos.getX());
			frog->setY(frog_pos.getY());
			frog->setZ(frog_pos.getZ());
		}
	}

	//Collision Frog vs Turtles
	for (unsigned int i = 0; i < turtles.size() ; i++) {
		if (testCircleAABB(frog->get_Sphere(), turtles.at(i)->get_AABB())) {
			beingCarried = true;
			// TODO: If we change frog implementation, this will be easier to write/read
			Vec3 d = turtles.at(i)->getSpeed();
			Vec3 frog_pos = Vec3(frog->getX(), frog->getY(), frog->getZ());
			frog_pos = frog_pos + d;
			frog->setX(frog_pos.getX());
			frog->setY(frog_pos.getY());
			frog->setZ(frog_pos.getZ());
		}
	}

	bool isOnRiver = (frog->getZ() >= 16.5) && (frog->getZ() <= 23.5);
	if (isOnRiver && !beingCarried) {
		falling = true;
		if(frog->getY() >= -0.20f)
			list_particle_system_I->front()->activar(frog->getX(), frog->getY(),
						frog->getZ(), 1, list_particle_system_A,
						list_particle_system_I);
	}*/

	//Collision Frog vs Cars
	for (unsigned int i = 0; i < cars.size(); i++) {
		if (!frog->isCompressed()
				&& testCircleAABB(frog->get_Sphere(), cars.at(i)->get_AABB())) {
			frog->setCompressed(true);
			// FIXME: Change location of the code below
			list_particle_system_I->front()->activar(frog->getX(), frog->getY(),
					frog->getZ(), 0, list_particle_system_A,
					list_particle_system_I);
			break;
		}
	}

	//Collision Frog vs Lamps
	/*for (unsigned int i = 0; i < lamps.size(); i++) {
	 if (testCircleAABB(frog->get_Sphere(), lamps.at(i)->get_AABB())) {

	 }
	 }*/
}

}

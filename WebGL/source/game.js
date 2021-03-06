function Game(){

	this.frogLifes = 3.0;
	this.points = 0;
	this.beingCarried = false;
	this.falling = false;
	this.distFalling = 0.0;
	this._burst = true;

	//objects
	this.map = null;
	this.frog = null;
	this.gameObjects = [];
	this.trucks = [];
	this.turtles = [];
	this.cameras = [];
	this.riverlogs = [];
	this.activeCam = null;

	this.points = 0;

	this.SphereTemp = null;
	this.BoxAABBTemp = null;

	this.beingCarried = false;

	this.tresd = 0;

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){
	SetupMaterial();

	this.map = new Map();
	this.frog = new Frog([16.0, 1.0, 0.25], [10.0, 10.0, 10.0]);
	
	this.hud = new Hud();

	var turtle1 = new Turtle([37, 12.25, -0.3], [-0.3, 0, 0]);
	var turtle2 = new Turtle([-3.0, 13.75, -0.3], [0.3, 0, 0]);
	var turtle3 = new Turtle([-3.0, 13.75, -0.3], [0.3, 0, 0]);
	var turtle4 = new Turtle([37, 15.25, -0.3], [-0.3, 0, 0]);
	var turtle5 = new Turtle([-3.0, 16.75, -0.3], [0.3, 0, 0]);
	
	this.gameObjects.push(turtle1);
	this.gameObjects.push(turtle2);
	this.gameObjects.push(turtle3);
	this.gameObjects.push(turtle4);
	this.gameObjects.push(turtle5);

	this.turtles.push(turtle1);
	this.turtles.push(turtle2);
	this.turtles.push(turtle3);
	this.turtles.push(turtle4);
	this.turtles.push(turtle5);
	
	this.gameObjects.push(new Lamp([8.0, 2.0, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 2.0, 2.0]));
	this.gameObjects.push(new Lamp([8.0, 10.5, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 10.5, 2.0]));
	this.gameObjects.push(new Lamp([8.0, 19.0, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 19.0, 2.0]));

	var t1 = new Truck([-3.0, 4.25, 0.5], [0.3, 0, 0]);
	var t2 = new Truck([-3.0, 7.25, 0.5], [0.3, 0, 0]);
	var t3 = new Truck([37.0, 5.75, 0.5], [-0.3, 0, 0]);
	var t4 = new Truck([37.0, 8.75, 0.5], [-0.3, 0, 0]); 
	
	this.gameObjects.push(t1);
	this.gameObjects.push(t2);
	this.gameObjects.push(t3);
	this.gameObjects.push(t4);

	this.trucks.push(t1);
	this.trucks.push(t2);
	this.trucks.push(t3);
	this.trucks.push(t4);

	var r1 = new RiverLog([17, 12.25, -0.3], [-0.3, 0, 0]);
	var r2 = new RiverLog([17, 15.25, -0.3], [-0.3, 0, 0]);

	this.gameObjects.push(r1);
	this.gameObjects.push(r2);

	this.riverlogs.push(r1);
	this.riverlogs.push(r2);

	this.cameras[0] = new TopOrthoCamera();
	this.cameras[1] = new TopPerspectiveCamera();
	this.cameras[2] = new FrogPerspectiveCamera();

	this.activeCam = this.cameras[2]; // by default use android settings

	// Listen for changes to the device orientation using the gyroscope and fire the event 
	// handler accordingly
	window.addEventListener('deviceorientation', game.activeCam.handleOrientationEvent, true);

}

Game.prototype.draw = function (){
	this.activeCam.load();
	this.map.draw();
	this.frog.draw();
	for(var i = 0 ; i < this.gameObjects.length ; i++) {
		this.gameObjects[i].draw();
	}
	this.map.draw();
	this.hud.drawText(0,0, "Lifes:" + this.frog.frogLifes, 50);
}

Game.prototype.update = function (){


	if (this.frog.frogLifes == 0) {
		return;
	}

	if(this.falling){
		var d = 0.12;
		this.distFalling += d;
		this.frog.position[2] = this.frog.position[2] - d;
		if(this.distFalling > 2.0){
			this.frogLifes--;
			this.falling = false;
			this.frog.position = [16.0, 1.0, 0.25];
			this.distFalling = 0.0;
		}
	}

	if(this.frog.isCompressed()){
		if(this.frog.getCompressed() > 0.0001){
			this.frog.setCompressedR(this.frog.getCompressed() - 0.04);
		} else{
			this.frog.position = [16.0, 1.0, 0.25];
			this.frogLifes--;
			this.frog.setCompressedR(1.0);
			this.frog.setCompressed(false);
		}
	} else{
		this.frog.update();
	}


	for(var i = 0 ; i < this.gameObjects.length ; i++) {
		this.gameObjects[i].update(0.1); // FIXME: Magic number
	}

	this.ComputeCollisions();
	this.activeCam.update();
}

Game.prototype.setCamera = function (num){
	this.activeCam = this.cameras[num - 1];
}

Game.prototype.sqDistPointAABB = function (pos){
	var sqDist = 0.0;
	var v;
	var minX, minY, minZ, maxX, maxY, maxZ;

	minX = this.BoxAABBTemp.getXmin();
	maxX = this.BoxAABBTemp.getXmax();
	minY = this.BoxAABBTemp.getYmin();
	maxY = this.BoxAABBTemp.getYmax();
	minZ = this.BoxAABBTemp.getZmin();
	maxZ = this.BoxAABBTemp.getZmax();

	// test the bounds against the points X axis
	v = pos[0];

	if (v < minX)
		sqDist += (minX - v) * (minX - v);
	if (v > maxX)
		sqDist += (v - maxX) * (v - maxX);

	// test the bounds against the points Y axis
	v = pos[1];

	if (v < minY)
		sqDist += (minY - v) * (minY - v);
	if (v > maxY)
		sqDist += (v - maxY) * (v - maxY);

	// test the bounds against the points Z axis
	v = pos[2];

	if (v < minZ)
		sqDist += (minZ - v) * (minZ - v);
	if (v > maxZ)
		sqDist += (v - maxZ) * (v - maxZ);

	return sqDist;
}

Game.prototype.testCircleAABB = function (){
	var x = this.SphereTemp.getX();
	var y = this.SphereTemp.getY();
	var z = this.SphereTemp.getZ();

	var sqDist = this.sqDistPointAABB([x, y, z]);
	var r = this.SphereTemp.getRaio();

	return sqDist <= r * r;
}

Game.prototype.ComputeCollisions = function (){


	var wonPoint = 22.0;
	if (this.frog.position[1] > wonPoint) {
		this.frog.position = [16.0, 1.0, 0.25];
		this.points += 1;
	}

	this.beingCarried = false;
	//Collision Frog vs Riverlogs
	for(var i = 0; i < this.riverlogs.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.riverlogs[i].getAABB();
		if(this.testCircleAABB()){
			this.beingCarried = true;
			this.frog.position[0] += this.riverlogs[i].speed[0] * 0.1; //FIXME magic number
			this.falling = false;
		}
	}

	//Collision Frog vs Turtles
	for(var i = 0; i < this.turtles.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.turtles[i].getAABB();
		if(this.testCircleAABB()){
			this.beingCarried = true;
			this.frog.position[0] += this.turtles[i].speed[0] * 0.1; //FIXME magic number
			this.falling = false;

		}
	}

	var isOnRiver = (this.frog.position[1] >=11.50) && (this.frog.position[1] <=17.25);
	if(isOnRiver && !this.beingCarried){
		this.falling = true;
		//Particles
	}
	

	//Collision Frog vs Trucks
	for(var i = 0; i < this.trucks.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.trucks[i].getAABB();
		if(!this.frog.isCompressed() && this.testCircleAABB()){
			this.frog.setCompressed(true);
			//PARTICLES
			break;
		}
	}


}

//Funcao bastarda
Game.prototype.automovement = function (){

	var temp;
	var middlefloor;
	var riverlog_1;
	var turtle_1;
	var riverlog_2;
	var turtle_2;


	if(this.frog.position[1] > 13.75 && this.frog.position[1] < 14.25)
		turtle_1 = true;
	else
		turtle_1 = false;

	if(this.frog.position[1] > 10.0 && this.frog.position[1] < 11.0)
		middlefloor = true;
	else
		middlefloor = false;

	if(this.frog.position[1] > 12.0 && this.frog.position[1] < 12.65)
		riverlog_1 = true;
	else
		riverlog_1 = false;

	if(this.frog.position[1] > 14.35 && this.frog.position[1] < 15.75)
		riverlog_2 = true;
	else
		riverlog_2 = false;

	if(this.frog.position[1] > 16.15 && this.frog.position[1] < 16.85)
		turtle_2 = true;
	else
		turtle_2 = false;

	

	if(this.frog.position[0] > 14.0 && middlefloor){
		currentlyPressedKeys[65] = true
	} else if(!middlefloor){
		currentlyPressedKeys[65] = false;
	}

	//console.log(this.frog.position[0]);
	// if(!middlefloor && this.frog.position[1] < 13.75){
	// 	currentlyPressedKeys[87] = true;
	// }

	if(this.frog.position[0] > 8.0 && riverlog_1){
		currentlyPressedKeys[87] = false;
	}else if(turtle_1 && this.frog.position[0] < 26.5 && this.frog.position[0] > 7.5){
		currentlyPressedKeys[87] = false;
	}else if(riverlog_2 && this.frog.position[0] < 26.5 && this.frog.position[0] > 8.0){
		currentlyPressedKeys[87] = false;
	} else if(turtle_2 && this.frog.position[0] > 10.0){
		currentlyPressedKeys[87] = false;
	} else{
		currentlyPressedKeys[87] = true;
	}
}

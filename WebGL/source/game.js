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

	this.SphereTemp = null;
	this.BoxAABBTemp = null;

	this.beingCarried = false;

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){
	SetupMaterial();

	this.map = new Map();
	this.frog = new Frog([16.0, 1.0, 0.5], [10.0, 10.0, 10.0])

	var turtle1 = new Turtle([37, 12.25, 0], [-0.3, 0, 0]);
	var turtle2 = new Turtle([-3.0, 13.75, 0], [0.3, 0, 0]);
	var turtle3 = new Turtle([-3.0, 13.75, 0], [0.3, 0, 0]);
	var turtle4 = new Turtle([37, 15.25, 0], [-0.3, 0, 0]);
	var turtle5 = new Turtle([-3.0, 16.75, 0], [0.3, 0, 0]);
	
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

	var t1 = new Truck([-3.0, 4.25, 1.2], [0.3, 0, 0]);
	var t2 = new Truck([-3.0, 7.25, 1.2], [0.3, 0, 0]);
	var t3 = new Truck([37.0, 5.75, 1.2], [-0.3, 0, 0]);
	var t4 = new Truck([37.0, 8.75, 1.2], [-0.3, 0, 0]); 
	
	this.gameObjects.push(t1);
	this.gameObjects.push(t2);
	this.gameObjects.push(t3);
	this.gameObjects.push(t4);

	this.trucks.push(t1);
	this.trucks.push(t2);
	this.trucks.push(t3);
	this.trucks.push(t4);
/*
	var r1 = new RiverLog([17, 12.25, 0], [-0.3, 0, 0]);
	var r2 = new RiverLog([17, 15.25, 0], [-0.3, 0, 0]);

	this.gameObjects.push(r1);
	this.gameObjects.push(r2);

	this.riverlogs.push(r1);
	this.riverlogs.push(r2);*/

	this.cameras[0] = new TopOrthoCamera();
	this.cameras[1] = new TopPerspectiveCamera();
	this.cameras[2] = new FrogPerspectiveCamera();

	this.activeCam = this.cameras[0];
}

Game.prototype.draw = function (){
	this.activeCam.load();
	this.map.draw();
	this.frog.draw();
	for(var i = 0 ; i < this.gameObjects.length ; i++) {
		this.gameObjects[i].draw();
	}
}

Game.prototype.update = function (){

	if (this.frog.frogLifes == 0) {
		return;
	}

	if(this.frog.isCompressed()){
		if(this.frog.getCompressed() > 0.0001){
			this.frog.setCompressedR(this.frog.getCompressed() - 0.04);
		} else{
			this.frog.setPosition([16.0, 1.0, 0.5]);
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


	this.beingCarried = false;
	//Collision Frog vs Riverlogs
	for(var i = 0; i < this.riverlogs.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.riverlogs[i].getAABB();
		if(this.testCircleAABB()){
			this.beingCarried = true;
			var d = this.riverlogs[i].getSpeed() ;
			var px = this.frog.position[0];
			var py = this.frog.position[1];
			var pz = this.frog.position[2];
			//p = [p[0] + d[0], p[1] + d[1], p[2] + d[2]];
			this.frog.position = [px + d[0], py+ d[1], pz+ d[2]];

		}
	}

	//Collision Frog vs Turtles
	for(var i = 0; i < this.turtles.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.turtles[i].getAABB();
		if(this.testCircleAABB()){
			this.beingCarried = true;
			var d = this.turtles[i].getSpeed() ;
			var px = this.frog.position[0];
			var py = this.frog.position[1];
			var pz = this.frog.position[2];
			//p = [p[0] + d[0], p[1] + d[1], p[2] + d[2]];
			this.frog.position = [px + d[0], py+ d[1], pz+ d[2]];

		}
	}


	//Collision Frog vs Trucks
	for(var i = 0; i < this.trucks.length; i++){
		this.SphereTemp = this.frog.getSphere();
		this.BoxAABBTemp = this.trucks[i].getAABB();
		if(!this.frog.isCompressed() && this.testCircleAABB()){
			this.frog.setCompressed(true);
			console.log("COLLISION!!!");
			//PARTICLES
			break;
		}
	}


}

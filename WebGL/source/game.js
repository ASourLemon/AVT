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
	this.cameras = []
	this.activeCam = null;

	this.SphereTemp = null;
	this.BoxAABBTemp = null;

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){
	SetupMaterial();

	this.map = new Map();
	this.frog = new Frog([16.0, 1.0, 0.5], [10.0, 10.0, 10.0])
	
	this.gameObjects.push(new Turtle([37, 12.25, 0], [-1, 0, 0]));
	this.gameObjects.push(new Turtle([-3.0, 13.75, 0], [1, 0, 0]));
	this.gameObjects.push(new Turtle([-3.0, 13.75, 0], [1, 0, 0]));

	this.gameObjects.push(new Turtle([37, 15.25, 0], [-1, 0, 0]));
	this.gameObjects.push(new Turtle([-3.0, 16.75, 0], [1, 0, 0]));
	
	this.gameObjects.push(new Lamp([8.0, 2.0, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 2.0, 2.0]));
	this.gameObjects.push(new Lamp([8.0, 10.5, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 10.5, 2.0]));
	this.gameObjects.push(new Lamp([8.0, 19.0, 2.0]));
	this.gameObjects.push(new Lamp([24.0, 19.0, 2.0]));

	var t1 = new Truck([-3.0, 4.25, 1.2], [1, 0, 0]);
	var t2 = new Truck([-3.0, 7.25, 1.2], [1, 0, 0]);
	var t3 = new Truck([37.0, 5.75, 1.2], [-1, 0, 0]);
	var t4 = new Truck([37.0, 8.75, 1.2], [-1, 0, 0]); 
	
	this.gameObjects.push(t1);
	this.gameObjects.push(t2);
	this.gameObjects.push(t3);
	this.gameObjects.push(t4);

	this.trucks.push(t1);
	this.trucks.push(t2);
	this.trucks.push(t3);
	this.trucks.push(t4);

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

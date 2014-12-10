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
	this.cameras = []
	this.activeCam = null;

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
	
	this.gameObjects.push(new Truck([-3.0, 4.25, 1.2], [1, 0, 0]));
	this.gameObjects.push(new Truck([-3.0, 7.25, 1.2], [1, 0, 0]));
	this.gameObjects.push(new Truck([37.0, 5.75, 1.2], [-1, 0, 0]));
	this.gameObjects.push(new Truck([37.0, 8.75, 1.2], [-1, 0, 0]));

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
	for(var i = 0 ; i < this.gameObjects.length ; i++) {
		this.gameObjects[i].update(0.1); // FIXME: Magic number
	}
	this.activeCam.update();
}

Game.prototype.setCamera = function (num){
	this.activeCam = this.cameras[num - 1];
}
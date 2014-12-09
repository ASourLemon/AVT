function Game(){

	this.frogLifes = 3.0;
	this.points = 0;
	this.beingCarried = false;
	this.falling = false;
	this.distFalling = 0.0;
	this._burst = true;

	//objects
	this.map = null;
	this.gameObjects = [];
	this.cameras = []
	this.activeCam = null;

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){
	SetupMaterial();

	this.map = new Map();
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));

	this.cameras[0] = new TopOrthoCamera();
	this.cameras[1] = new TopPerspectiveCamera();
	//this.cameras[2] = new FrogPerspectiveCamera();

	this.activeCam = this.cameras[1];
}

Game.prototype.draw = function (){
	this.activeCam.load();
	this.map.draw();
}

Game.prototype.setCamera = function (num){
	this.activeCam = this.cameras[num - 1];
}
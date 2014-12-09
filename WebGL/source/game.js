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

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){

	SetupMaterial();

	this.map = new Map();
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	this.gameObjects.push(new Truck([0, 0, 0], [0, 0, 0]));
	for(var i = 0 ; i < this.gameObjects.length ; i++) {
		this.gameObjects[i].update();
	}

}

Game.prototype.draw = function (){

	this.map.draw();

}
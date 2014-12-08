function Game(){

	this.frogLifes = 3.0;
	this.points = 0;
	this.beingCarried = false;
	this.falling = false;
	this.distFalling = 0.0;
	this._burst = true;

	//objects
	this.map = null;

	lastTime = new Date().getTime();
}

Game.prototype.init = function (){

	this.map = new Map();

}

Game.prototype.draw = function (){

	this.map.draw();

}
var LEFT_X_LIMIT = -5.0;
var RIGHT_X_LIMIT = 36.0;

function DynamicObject(){
	this.elapsed_ticks = 0;
}

DynamicObject.prototype.update = function(time){
	this.elapsed_ticks++;

	var FIFTEEN_SECONDS_PASSED = 15 * 60;
	if (this.elapsed_ticks == FIFTEEN_SECONDS_PASSED) {
		this.increaseSpeed();
		this.elapsed_ticks = 0;
	}

	this.position[0] += this.speed[0]*time;
	this.position[1] += this.speed[1]*time;
	this.position[2] += this.speed[2]*time;

	var r = Math.random()*5;
	if (this.position[0] <= LEFT_X_LIMIT) {
		this.position[0] = RIGHT_X_LIMIT + r;
	}
	else if (this.position[0] >= RIGHT_X_LIMIT) {
		this.position[0] = LEFT_X_LIMIT - r;
	}
}

DynamicObject.prototype.increaseSpeed = function(){
	var SPEED_INCREMENT = 1.75;
	this.speed[0] += this.initSpeed[0]*SPEED_INCREMENT;
}

DynamicObject.prototype.resetSpeed = function(){
	this.speed = vec3.set(this.initSpeed, this.speed);
}

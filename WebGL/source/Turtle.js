Turtle.prototype = new DynamicObject();

function Turtle(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

Turtle.prototype.draw = function (){
	// TODO: Implement
}
Truck.prototype = new DynamicObject();

function Truck(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

Truck.prototype.draw = function (){
	// TODO: Implement
}
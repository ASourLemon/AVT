RiverLog.prototype = new DynamicObject();

function RiverLog(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

RiverLog.prototype.draw = function (){
	// TODO: Implement
}
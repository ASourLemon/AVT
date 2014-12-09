Lamp.prototype = new StaticObject();

function Lamp(position, initSpeed){
	this.position = vec3.create(position);
}

Lamp.prototype.draw = function (){
	// TODO: Implement
}
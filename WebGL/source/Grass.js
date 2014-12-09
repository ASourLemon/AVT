Grass.prototype = new StaticObject();

function Grass(position, initSpeed){
	this.position = vec3.create(position);
}

Grass.prototype.draw = function (){
	// TODO: Implement
}
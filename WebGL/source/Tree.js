Tree.prototype = new StaticObject();

function Tree(position, initSpeed){
	this.position = vec3.create(position);
}

Tree.prototype.draw = function (){
	// TODO: Implement
}
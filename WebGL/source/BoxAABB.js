function BoxAABB(center, x, y, z){
	this.center = vec3.clone(center);
	this.x_size = x;
	this.y_size = y;
	this.z_size = z;

}

BoxAABB.prototype.get_X = function(){

	return this.center[0];
}

BoxAABB.prototype.get_Y = function(){

	return this.center[1];
}

BoxAABB.prototype.get_Z = function(){

	return this.center[2];
}

BoxAABB.prototype.getXmin = function(){
	return this.get_X() - this.x_size / 2;

}

BoxAABB.prototype.getXmax = function(){

	return this.get_X() + this.x_size / 2;
}

BoxAABB.prototype.getYmin = function(){

	return this.get_Y() - this.y_size / 2;
}

BoxAABB.prototype.getYmax = function(){

	return this.get_Y() + this.y_size / 2;
}

BoxAABB.prototype.getZmin = function(){

	return this.get_Z() - this.z_size / 2;
}

BoxAABB.prototype.getZmax = function(){

	return this.get_Z() + this.z_size / 2;
}

BoxAABB.prototype.setCenter = function(pos){

	this.center = pos;
}
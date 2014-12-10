function BoxSphere(center, raio){
	this.center = vec3.clone(center);
	this.raio = raio;

}

BoxSphere.prototype.getRaio = function(){
	return this.raio;
}

BoxSphere.prototype.getX = function(){
	return this.center[0];
}

BoxSphere.prototype.getY = function(){
	return this.center[1];
}

BoxSphere.prototype.getZ = function(){
	return this.center[2];
}

BoxSphere.prototype.setCenter = function(pos){

	this.center = pos;
}
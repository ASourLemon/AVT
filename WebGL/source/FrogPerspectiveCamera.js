function FrogPerspectiveCamera(){
	this.fov = 125.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	// FIXME: Change values below
	this.near = 0.1;
	this.far = 30.1;

	this.pos = [1.0 , 1.0, 0.5];
	this.up = [0.0, 0.0, 1.0];
	this.at = [0.0, 2.0, 0.0];
}

FrogPerspectiveCamera.prototype.load = function() {
	mat4.perspective(this.fov, this.aspectRatio, this.near, this.far, pMatrix);
	mat4.lookAt(this.pos, this.at, this.up, mvMatrix);
}

FrogPerspectiveCamera.prototype.update = function() {
	// TODO: Implement
	this.pos = [game.frog.position[0], game.frog.position[1]-1.0, game.frog.position[2]+1.0];
	this.at = [game.frog.position[0], game.frog.position[1], game.frog.position[2]];
}
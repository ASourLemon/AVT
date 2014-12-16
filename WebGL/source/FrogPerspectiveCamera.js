function FrogPerspectiveCamera(){
	this.fov = 70.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	this.near = 0.1;
	this.far = 40.1;

	this.pos = [1.0 , 1.0, 0.5];
	this.up = [0.0, 0.0, 1.0];
	this.at = [0.0, 2.0, 0.0];
}

FrogPerspectiveCamera.prototype.load = function() {
	mat4.perspective(pMatrix, this.fov, this.aspectRatio, this.near, this.far);
	mat4.lookAt(mvMatrix, this.pos, this.at, this.up);
	// kinda hacky :s
	mat4.identity(viewMatrix);
	mat4.lookAt(viewMatrix, this.pos, this.at, this.up);
}

FrogPerspectiveCamera.prototype.update = function() {
	this.pos = [game.frog.position[0], game.frog.position[1]-3.5, game.frog.position[2]+3.0];
	this.at = [game.frog.position[0], game.frog.position[1]+3.0, game.frog.position[2]];
}

FrogPerspectiveCamera.prototype.update3d = function(s) {
	this.pos = [game.frog.position[0]+s, game.frog.position[1]-3.5, game.frog.position[2]+3.0];
	this.at = [game.frog.position[0], game.frog.position[1]+3.0, game.frog.position[2]];
}
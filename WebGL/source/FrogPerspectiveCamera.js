var alpha, beta, gama;

function FrogPerspectiveCamera(){
	this.fov = 70.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	this.near = 0.1;
	this.far = 40.1;

	this.pos = [1.0, 1.0, 0.5];
	this.up = [0.0, 0.0, 1.0];
	this.at = [0.0, 2.0, 0.0];
}

FrogPerspectiveCamera.prototype.load = function() {
	var mat_alpha = mat4.create();
	var at_vec3 = vec3.create();
	var at_vec4;

	mat4.rotate(mat_alpha, mat_alpha, alpha ? alpha*Math.PI/180 : 0, [0.0, 0.0, 1.0]);
	vec3.sub(at_vec3, this.at, this.pos);
	at_vec4 = vec4.fromValues(at_vec3[0], at_vec3[1], at_vec3[2], 0.0);
	vec4.transformMat4(at_vec4, at_vec4, mat_alpha);
	at_vec3 = vec3.fromValues(at_vec4[0], at_vec4[1], at_vec4[2]);
	vec3.add(at_vec3, at_vec3, this.pos);


	mat4.perspective(pMatrix, this.fov, this.aspectRatio, this.near, this.far);
	mat4.lookAt(mvMatrix, this.pos, at_vec3, this.up);
	// kinda hacky :s
	mat4.identity(viewMatrix);
	mat4.lookAt(viewMatrix, this.pos, at_vec3, this.up);

}

FrogPerspectiveCamera.prototype.update = function() {
	this.pos = [game.frog.position[0], game.frog.position[1]-3.5, game.frog.position[2]+3.0];
	this.at = [game.frog.position[0], game.frog.position[1]+3.0, game.frog.position[2]];

}

// Create an event handler function for processing the device orientation event
FrogPerspectiveCamera.prototype.handleOrientationEvent = function(e) {
	//alert("Hello! I am an alert box!!" + alpha);

    // Get the orientation of the device in 3 axes, known as alpha, beta, and gamma, 
    // represented in degrees from the initial orientation of the device on load
    alpha = e.alpha;
    beta = e.beta;
    gamma = e.gamma;

    
};
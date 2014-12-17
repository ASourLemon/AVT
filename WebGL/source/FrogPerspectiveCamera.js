var alpha, beta, gamma;
var prev_alpha, prev_beta, prev_gamma;

function FrogPerspectiveCamera(){
	this.fov = 70.0;
	this.aspectRatio = gl.viewportWidth / gl.viewportHeight;
	this.near = 0.1;
	this.far = 40.1;

	this.pos = [1.0, 1.0, 0.5];
	this.up = [0.0, 3.0, 6.5];
	this.at = [0.0, 2.0, 0.0];
}

FrogPerspectiveCamera.prototype.load = function() {
    ////////////// Rotate over yy axis ///////////////
	var mat_gamma = mat4.create();
	var up_vec3 = vec3.clone(this.up);
	var up_vec4;

	mat4.rotate(mat_gamma, mat_gamma, gamma ? gamma*Math.PI/180 : 0, [0.0, 1.0, 0.0]);
	mat4.rotate(mat_gamma, mat_gamma, beta ? beta*Math.PI/180 : 0, [1.0, 0.0, 0.0]);
	up_vec4 = vec4.fromValues(up_vec3[0], up_vec3[1], up_vec3[2], 0.0);
	vec4.transformMat4(up_vec4, up_vec4, mat_gamma);
	up_vec3 = vec3.fromValues(up_vec4[0], up_vec4[1], up_vec4[2]);
	///////////////////////////////////////////////////


	////////////// Rotate over zz axis //////////////
	var mat_alpha = mat4.create();
	var at_vec3 = vec3.create();
	var at_vec4;

	mat4.rotate(mat_alpha, mat_alpha, beta ? beta*Math.PI/180 : 0, [1.0, 0.0, 0.0]);
	mat4.rotate(mat_alpha, mat_alpha, alpha ? alpha*Math.PI/180 : 0, [0.0, 0.0, 1.0]);
	vec3.sub(at_vec3, this.at, this.pos);
	at_vec4 = vec4.fromValues(at_vec3[0], at_vec3[1], at_vec3[2], 0.0);
	vec4.transformMat4(at_vec4, at_vec4, mat_alpha);
	at_vec3 = vec3.fromValues(at_vec4[0], at_vec4[1], at_vec4[2]);
	vec3.add(at_vec3, at_vec3, this.pos);
    //////////////////////////////////////////////////


	mat4.perspective(pMatrix, this.fov, this.aspectRatio, this.near, this.far);
	mat4.lookAt(mvMatrix, this.pos, at_vec3, up_vec3);
	// kinda hacky :s
	mat4.identity(viewMatrix);
	mat4.lookAt(viewMatrix, this.pos, at_vec3, up_vec3);

}

FrogPerspectiveCamera.prototype.update = function() {
	this.pos = [game.frog.position[0], game.frog.position[1]-3.5, game.frog.position[2]+3.0];
	this.at = [game.frog.position[0], game.frog.position[1]+3.0, game.frog.position[2]];

}

// Create an event handler function for processing the device orientation event
var isInit = false;
FrogPerspectiveCamera.prototype.handleOrientationEvent = function(e) {
	var TOLERANCE = 10;
    alpha = e.alpha;
    beta = e.beta;
    gamma = e.gamma;

    if(isInit) {
    	if(prev_alpha - alpha <= -TOLERANCE || prev_alpha - alpha >= TOLERANCE)
    		prev_alpha = alpha;
    	if(prev_beta - beta <= -TOLERANCE || prev_beta - beta >= TOLERANCE)
    		prev_beta = beta;
    	if(prev_gamma - gamma <= -TOLERANCE || prev_gamma - gamma >= TOLERANCE)
    		prev_gamma = gamma;
    } else {
    	isInit = true;
		prev_alpha = alpha;
		prev_beta = beta;
		prev_gamma = gamma;
    }

	alpha = prev_alpha;
	beta = prev_beta;
	gamma = prev_gamma;

    //////// FOR DEBUG ///////
    //var text = gamma.toString();
    //document.body.innerHTML = text;
};
var alpha, beta, gamma;

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
	////////////// Rotate over zz axis //////////////
	var mat_alpha = mat4.create();
	var at_vec3 = vec3.create();
	var at_vec4;

	mat4.rotate(mat_alpha, mat_alpha, alpha ? alpha*Math.PI/180 : 0, [0.0, 0.0, 1.0]);
	vec3.sub(at_vec3, this.at, this.pos);
	at_vec4 = vec4.fromValues(at_vec3[0], at_vec3[1], at_vec3[2], 0.0);
	vec4.transformMat4(at_vec4, at_vec4, mat_alpha);
	at_vec3 = vec3.fromValues(at_vec4[0], at_vec4[1], at_vec4[2]);
	vec3.add(at_vec3, at_vec3, this.pos);
    //////////////////////////////////////////////////


    ////////////// Rotate over yy axis ///////////////
	var mat_gamma = mat4.create();
	var up_vec3 = vec3.clone(this.up);
	var up_vec4;

	mat4.rotate(mat_gamma, mat_gamma, gamma ? gamma*Math.PI/180 : 0, [0.0, 1.0, 0.0]);
	up_vec4 = vec4.fromValues(up_vec3[0], up_vec3[1], up_vec3[2], 0.0);
	vec4.transformMat4(up_vec4, up_vec4, mat_gamma);
	up_vec3 = vec3.fromValues(up_vec4[0], up_vec4[1], up_vec4[2]);
	///////////////////////////////////////////////////


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
var hoe_index = 0;
var alpha_vec = [];
var beta_vec = [];
var gamma_vec = [];
FrogPerspectiveCamera.prototype.handleOrientationEvent = function(e) {
	if(hoe_index == 0) {
		alpha = 0;
		beta = 0;
		gamma = 0;
		for(var i = 0 ; i < 20 ; i++) {
			alpha += alpha_vec[i];
			beta += beta_vec[i];
			gamma += gamma_vec[i];
		}
		alpha /= 20;
		beta /= 20;
		gamma /= 20;
	}

    alpha_vec[hoe_index] = e.alpha;
    beta_vec[hoe_index] = e.beta;
    gamma_vec[hoe_index] = e.gamma;

    hoe_index++;
    hoe_index = hoe_index % 20;
    //////// FOR DEBUG ///////
    //var text = gamma.toString();
    //document.body.innerHTML = text;
};
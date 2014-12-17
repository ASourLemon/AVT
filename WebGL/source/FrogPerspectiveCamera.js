var alpha, beta, gamma;
var prev_alpha, prev_beta, prev_gamma;

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
	var trans_pos;
	var trans_up;
	var trans_at;

	if(alpha != null) {
	    var rMat = mat3.clone(getRotationMatrix(alpha, beta < 0 ? 90 : (90-beta), gamma));
	    trans_pos = vec3.clone(this.pos);
	    trans_up = vec3.clone(this.up);
	    trans_at = vec3.clone(this.at);
	    vec3.sub(trans_pos, trans_pos, game.frog.position);
	    vec3.sub(trans_at, trans_at, game.frog.position);
	    vec3.transformMat3(trans_pos, trans_pos, rMat);
	    vec3.transformMat3(trans_up, trans_up, rMat);
	    vec3.transformMat3(trans_at, trans_at, rMat);
	    vec3.add(trans_pos, trans_pos, game.frog.position);
	    vec3.add(trans_at, trans_at, game.frog.position);
	} else {
		trans_pos = this.pos;
		trans_up = this.up;
		trans_at = this.at;
	}

	mat4.perspective(pMatrix, this.fov, this.aspectRatio, this.near, this.far);
	mat4.lookAt(mvMatrix, trans_pos, trans_at, trans_up);
	// kinda hacky :s
	mat4.identity(viewMatrix);
	mat4.lookAt(viewMatrix, trans_pos, trans_at, trans_up);

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
    // var text = "alpha: " + alpha.toString() + "\n" + "beta: " + beta.toString() + "gama: " + gamma.toString();
    // document.body.innerHTML = text;
};

var degtorad = Math.PI / 180; // Degree-to-Radian conversion

function getRotationMatrix( alpha, beta, gamma ) {

  var _x = beta  ? beta  * degtorad : 0; // beta value
  var _y = gamma ? gamma * degtorad : 0; // gamma value
  var _z = alpha ? alpha * degtorad : 0; // alpha value

  var cX = Math.cos( _x );
  var cY = Math.cos( _y );
  var cZ = Math.cos( _z );
  var sX = Math.sin( _x );
  var sY = Math.sin( _y );
  var sZ = Math.sin( _z );

  //
  // ZXY rotation matrix construction.
  //

  var m11 = cZ * cY - sZ * sX * sY;
  var m12 = - cX * sZ;
  var m13 = cY * sZ * sX + cZ * sY;

  var m21 = cY * sZ + cZ * sX * sY;
  var m22 = cZ * cX;
  var m23 = sZ * sY - cZ * cY * sX;

  var m31 = - cX * sY;
  var m32 = sX;
  var m33 = cX * cY;

  return [
    m11,    m12,    m13,
    m21,    m22,    m23,
    m31,    m32,    m33
  ];

};
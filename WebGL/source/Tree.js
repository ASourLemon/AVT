Tree.prototype = new StaticObject();

function Tree(position){
	this.position = vec3.clone(position);
}

Tree.prototype.draw = function (){
	gl.bindTexture(gl.TEXTURE_2D, texArray[6]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	setDiffuse(0.3, 0.6, 0.3, 1.0);
	setAmbient(0.2, 0.3, 0.2, 1.0);
	setSpecular(0.0, 0.0, 0.0, 1.0);
	setShininess(1);

	///////////// Calculating rotation parameters for billboard /////////////////
	var objToCam = vec3.clone(game.activeCam.pos);
	objToCam[0] -= this.position[0];
	objToCam[1] -= this.position[1];
	objToCam[2] = 0.0;
	// IT IS THE LOOK AT AS IF WE WERE ON THE FIRST POSITION, LOOKING IN THE BILLBOARD DIRECTION
 	var look_at = vec3.clone([0.0, -1.0, 0.0]);
 	vec3.normalize(objToCam, objToCam);
 	vec3.normalize(look_at, look_at);
	var cos_alpha = vec3.dot(look_at, objToCam);
	var up_aux = vec3.create();
	vec3.cross(up_aux, look_at, objToCam);
	/////////////////////////////////////////////////////////////////////////////

	mvPushMatrix();
	gl.enable(gl.BLEND);
	mat4.translate(mvMatrix, mvMatrix, [0.85+this.position[0], 0.85+this.position[1], 1.5]);
	mat4.rotate(mvMatrix, mvMatrix, Math.acos(cos_alpha), up_aux);
	mat4.rotate(mvMatrix, mvMatrix, Math.PI, [0.0, 1.0, 0.0]);
	mat4.rotate(mvMatrix, mvMatrix, Math.PI/2, [1.0, 0.0, 0.0]);
	mat4.scale(mvMatrix, mvMatrix, [1.7, 3.5, 1]);
	drawBillboard();
	gl.disable(gl.BLEND);
	mvPopMatrix();

	gl.bindTexture(gl.TEXTURE_2D, null);
}
Frog.prototype = new DynamicObject();

function Frog(position, initSpeed){
	this.position = vec3.clone(position);
	this.initSpeed = vec3.clone(initSpeed);
	this.speed = vec3.clone(initSpeed);

	this.beingCompressed = false;
	this.compressed = 1.0;

	this.frogLifes = 3;

	this.BoxSphere = new BoxSphere(this.position, 0.65);

}

Frog.prototype.draw = function (){
	this.BoxSphere.setCenter(this.position);
	// TODO: Implement
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, this.position);
	mat4.scale(mvMatrix, mvMatrix, [0.65, 0.65, 0.65 * this.compressed]);

	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	//BODY
	this.setBodyColor();
	mvPushMatrix();
	mat4.scale(mvMatrix, mvMatrix, [1.0, 1.0, 0.8]);
	drawSphere();
	mvPopMatrix();

	//HEAD
	this.setHeadColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.25, 0.4]);
	mat4.scale(mvMatrix, mvMatrix, [0.75, 0.75, 0.8]);
	drawSphere();
	mvPopMatrix();

	//EYE 1
	this.setEyeColor();
	gl.bindTexture(gl.TEXTURE_2D, texArray[4]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.20, 0.45, 0.6]);
	mat4.scale(mvMatrix, mvMatrix, [0.25, 0.25, 0.30]);
	drawSphere();
	mvPopMatrix();

	//EYE 2
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [-0.20, 0.45, 0.6]);
	mat4.scale(mvMatrix, mvMatrix, [0.25, 0.25, 0.30]);
	drawSphere();
	mvPopMatrix();

	mvPopMatrix();
}

Frog.prototype.update = function(){

}

Frog.prototype.setBodyColor = function(){

	setDiffuse( 0.2, 0.5, 0.2, 1.0 );
	setAmbient( 0.2, 0.4, 0.2, 1.0 );
	setSpecular(0.3, 0.3, 0.3, 1.0 );
	setShininess(20);
}

Frog.prototype.setHeadColor = function(){

	setDiffuse( 0.2, 0.5, 0.2, 1.0 );
	setAmbient(0.2, 0.4, 0.2, 1.0 );
	setSpecular( 0.3, 0.3, 0.3, 1.0 );
	setShininess(20);
}

Frog.prototype.setEyeColor = function(){

	setDiffuse(0.8, 0.8, 0.8, 1.0);
	setAmbient(0.6, 0.6, 0.6, 1.0);
	setSpecular(0.4, 0.4, 0.4, 1.0);
	setShininess(100);
}

Frog.prototype.getPosition = function(){

	return this.position;
}

Frog.prototype.setPosition = function(pos){

	this.position = pos;
}

Frog.prototype.isCompressed = function(){

	return this.beingCompressed;
}

Frog.prototype.setCompressed = function(compressed){

	this.beingCompressed = compressed;
}

Frog.prototype.setCompressedR = function(compressed){

	this.compressed = compressed;
}

Frog.prototype.getCompressed = function(){

	return this.compressed;
}

Frog.prototype.getSphere = function(){

	return this.BoxSphere;
}

RiverLog.prototype = new DynamicObject();

function RiverLog(position, initSpeed){
	this.position = vec3.clone(position);
	this.initSpeed = vec3.clone(initSpeed);
	this.speed = vec3.clone(initSpeed);

	this.BoxAABB = new BoxAABB(this.position, 2.75, 0.4, 0.25);
}

RiverLog.prototype.draw = function (){
	// TODO: Implement
	this.BoxAABB.setCenter(this.position);
	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);


	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [this.position[0], this.position[1], this.position[2]]);
	
	//body
	this.setLogColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, 0.0]);
	mat4.scale(mvMatrix, mvMatrix, [2.0, 0.5, 0.25]);
	drawCube();
	mvPopMatrix();

	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}


RiverLog.prototype.setLogColor = function(){

	setDiffuse(1.0, 0.5, 0.2, 1.0 );
	setAmbient(0.9, 0.2, 0.2, 1.0);
	setSpecular(0.6, 0.6, 0.6, 1.0);
	setShininess(100);
}

RiverLog.prototype.getAABB = function(){

	return this.BoxAABB;
}

RiverLog.prototype.getSpeed = function(){

	return this.speed;
}

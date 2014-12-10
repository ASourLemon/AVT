Turtle.prototype = new DynamicObject();

function Turtle(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

Turtle.prototype.draw = function (){
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	mvPushMatrix();
	mat4.translate(mvMatrix, [this.position[0], this.position[1], this.position[2]]);
	
	//body
	this.setBodyColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, [0.0, 0.0, 0.15]);
	mat4.scale(mvMatrix, [1.1*0.8, 1.1*0.8, 0.4*0.8]);
	drawSphere();
	mvPopMatrix();
	
	//legs
	this.setLegsColor();
	mvPushMatrix();	
	mat4.rotate(mvMatrix, 45.0, [0.0, 0.0, 1.0]);	
	mat4.scale(mvMatrix, [1.3*0.9, 0.3*0.9, 0.2*0.9]);
	drawSphere();
	mvPopMatrix();
	
	mvPushMatrix();	
	mat4.rotate(mvMatrix, -45.0, [0.0, 0.0, 1.0]);
	mat4.scale(mvMatrix, [1.3*0.9, 0.3*0.9, 0.2*0.9]);
	drawSphere();
	mvPopMatrix();
	
	//head
	this.setHeadColor();
	mvPushMatrix();	
	if(this.speed[0] < 0){
		mat4.translate(mvMatrix, [-0.4, 0.0, 0.0]);	
	}else if(this.speed[0] > 0){
		mat4.translate(mvMatrix, [0.4, 0.0, 0.0]);
	}
	mat4.scale(mvMatrix, [1.1*0.3, 1.5*0.3, 0.5*0.3]);
	drawSphere();
	mvPopMatrix();
	
	//end
	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}

Turtle.prototype.setBodyColor = function(){

	setDiffuse(0.4, 0.8, 0.2, 1.0);
	setAmbient(0.2, 0.4, 0.1, 1.0);
	setSpecular(0.6, 0.6, 0.6, 1.0);
	setShininess(10);
}

Turtle.prototype.setLegsColor = function(){

	setDiffuse(0.4, 0.6, 0.4, 1.0);
	setAmbient(0.2, 0.5, 0.2, 1.0);
	setSpecular(0.7, 0.7, 0.7, 1.0);
	setShininess(10);
}

Turtle.prototype.setHeadColor = function(){

	setDiffuse(0.5, 0.7, 0.5, 1.0);
	setAmbient(0.2, 0.6, 0.2, 1.0);
	setSpecular( 0.8, 0.8, 0.8, 1.0);
	setShininess(10);
}
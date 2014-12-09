Turtle.prototype = new DynamicObject();

function Turtle(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

Turtle.prototype.draw = function (){
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, texArray[0]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	mvPushMatrix();
	mat4.translate(mvMatrix, [this.position[0], this.position[1], this.position[2]]);
	
	//body
	mvPushMatrix();
	mat4.translate(mvMatrix, [0.0, 0.0, 0.15]);
	mat4.scale(mvMatrix, [1.0*0.8, 1.0*0.8, 0.3*0.8]);
	drawSphere();
	mvPopMatrix();
	
	//legs
	mvPushMatrix();	
	mat4.rotate(mvMatrix, 45.0, [0.0, 0.0, 1.0]);	
	mat4.scale(mvMatrix, [1.2*0.9, 0.2*0.9, 0.1*0.9]);
	drawSphere();
	mvPopMatrix();
	
	mvPushMatrix();	
	mat4.rotate(mvMatrix, -45.0, [0.0, 0.0, 1.0]);
	mat4.scale(mvMatrix, [1.2*0.9, 0.2*0.9, 0.1*0.9]);
	drawSphere();
	mvPopMatrix();
	
	//head
	mvPushMatrix();	
	if(this.speed[0] < 0){
		mat4.translate(mvMatrix, [-0.6, 0.0, 0.0]);	
	}else if(this.speed[0] > 0){
		mat4.translate(mvMatrix, [0.6, 0.0, 0.0]);
	}
	mat4.scale(mvMatrix, [1.0*0.3, 1.4*0.3, 0.4*0.3]);
	drawSphere();
	mvPopMatrix();
	
	//end
	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}
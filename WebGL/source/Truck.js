Truck.prototype = new DynamicObject();

function Truck(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);
}

Truck.prototype.draw = function (){
	// TODO: Implement
	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	mvPushMatrix();
	mat4.translate(mvMatrix, [this.position[0], this.position[1], this.position[2]]);

	//LOAD
	this.setLoadColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, [-0.75, 0.0, 0.0]);
	mat4.scale(mvMatrix, [2.5, 0.5, 0.5]);
	drawCube();
	mvPopMatrix();

	//Driver
	this.setDriverColor();
	mvPushMatrix();
	if(this.speed[0] < 0){
		mat4.translate(mvMatrix, [-4.0, 0.0, -0.15]);	
	}else if(this.speed[0] > 0){
		mat4.translate(mvMatrix, [2.5, 0.0, -0.15]);
	}
	//mat4.translate(mvMatrix, [2.0, 0.0, -0.15]);
	mat4.scale(mvMatrix, [0.75, 0.5, 0.35]);
	drawCube();
	mvPopMatrix();

	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}

Truck.prototype.setLoadColor = function(){

	setDiffuse(0.5, 0.3, 0.3, 1.0);
	setAmbient(0.4, 0.1, 0.1, 1.0);
	setSpecular(0.6, 0.4, 0.4, 1.0);
	setShininess(10);
}

Truck.prototype.setDriverColor = function(){

	setDiffuse(0.4, 0.4, 0.4, 1.0);
	setAmbient(0.2, 0.2, 0.2, 1.0);
	setSpecular( 0.5, 0.5, 0.5, 1.0);
	setShininess(100);
}

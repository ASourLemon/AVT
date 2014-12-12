Lamp.prototype = new StaticObject();

function Lamp(position){
	this.position = vec3.clone(position);
}

Lamp.prototype.draw = function (){
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [this.position[0], this.position[1], this.position[2]]);

	
	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);

	//Lamp
	this.setLampColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, 0.70]);
	mat4.scale(mvMatrix, mvMatrix, [0.65, 0.65, 0.65]);
	drawSphere();
	mvPopMatrix();

	//Reflection
	gl.enable(gl.STENCIL_TEST)
	gl.depthMask(false);
	gl.stencilFunc(gl.EQUAL,1,0xff); 
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, -5.2]);
	mat4.scale(mvMatrix, mvMatrix, [0.65, 0.65, 0.65]);
	drawSphere();
	mvPopMatrix();

	gl.depthMask(true);
	gl.disable(gl.STENCIL_TEST);

	//Body
	this.setBodyColor();
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, -1.0]);
	mat4.scale(mvMatrix, mvMatrix, [0.25, 0.25, 1.5]);
	drawCube();
	mvPopMatrix();
	//Reflection
	gl.enable(gl.STENCIL_TEST);
	gl.depthMask(false);
	gl.stencilFunc(gl.EQUAL,1,0xff); 
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, -3.5]);
	mat4.scale(mvMatrix, mvMatrix, [0.25, 0.25, 1.5]);
	drawCube();
	mvPopMatrix();

	gl.depthMask(true);
	gl.disable(gl.STENCIL_TEST);
	
	
	

	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}

Lamp.prototype.setBodyColor = function(){

	setDiffuse( 0.25, 0.25, 0.25, 1.0);
	setAmbient( 0.0625, 0.0625, 0.0625, 1.0);
	setSpecular(0.25, 0.25, 0.25, 1.0);
	setShininess(10);
}

Lamp.prototype.setLampColor = function(){

	setDiffuse( 1.0, 1.0, 0.6, 1.0 );
	setAmbient(0.25, 0.25, 0.15, 1.0);
	setSpecular( 1.0, 1.0, 0.6, 1.0 );
	setShininess(100);
}

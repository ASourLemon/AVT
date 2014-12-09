Frog.prototype = new DynamicObject();

function Frog(position, initSpeed){
	this.position = vec3.create(position);
	this.initSpeed = vec3.create(initSpeed);
	this.speed = vec3.create(initSpeed);

	this.beingCompressed = false;
	this.compressed = 1.0;
}

Frog.prototype.draw = function (){
	// TODO: Implement
	mvPushMatrix();
	mat4.translate(mvMatrix, this.position);

	mat4.scale(mvMatrix, [0.2, 0.2, 0.2 * this.compressed]);

	mvPushMatrix();
	mat4.scale(mvMatrix, [1.0, 1.0, 0.8]);
	drawSphere();
	mvPopMatrix();


	mvPopMatrix();
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

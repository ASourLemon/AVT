function LightManager(){

	this.isDay = true;

}

LightManager.prototype.init = function(){
	gl.uniform1i(shaderProgram.useLightingUniform, this.isDay);

	if(this.isDay){
		gl.uniform3f(shaderProgram.ambientColorUniform, 1.0, 0.0, 0.0);

		var lightingDirection = vec3.create(1.0, 1.0, -1.0);

	    // var adjustedLD = vec3.create();
	    // vec3.normalize(lightingDirection, adjustedLD);
	    // vec3.scale(adjustedLD, -1);
	    gl.uniform3fv(shaderProgram.lightingDirectionUniform, lightingDirection);

	    gl.uniform3f(shaderProgram.directionalColorUniform, 0.1, 0.1, 0.1);
	}
}

var Light = {};



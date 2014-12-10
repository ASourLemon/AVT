function LightManager(){

	this.isDay = false;
	this.lampOn = false;

}

LightManager.prototype.init = function(){
	gl.uniform1i(shaderProgram.useLightingUniform, this.isDay); //
	gl.uniform1i(shaderProgram.isDay, this.isDay);
	gl.uniform1i(shaderProgram.lampOn, this.lampOn);

	if(this.isDay){
		gl.uniform3f(shaderProgram.ambientColorUniform, 1.0, 0.0, 0.0);

		var lightingDirection = vec3.clone([1.0, 1.0, 1.0]);
		// vec3.transformMat4(lightingDirection, lightingDirection, viewMatrix);
		vec3.normalize(lightingDirection, lightingDirection);


	    gl.uniform3fv(shaderProgram.lightingDirectionUniform, lightingDirection);

	    gl.uniform3f(shaderProgram.directionalColorUniform, 0.1, 0.1, 0.1);
	} else {
		var spotLightPos = vec4.clone([game.frog.position[0], game.frog.position[1], game.frog.position[2]+3.0, 1.0]);
		vec4.transformMat4(spotLightPos, spotLightPos, viewMatrix);
		var spotLightLookAt = vec4.clone([0.0, 40.0, 2.0, 0.0]);
		vec4.transformMat4(spotLightLookAt, spotLightLookAt, viewMatrix);
		vec4.normalize(spotLightLookAt, spotLightLookAt);
		var spotCutOff = 0.8;
		gl.uniform4fv(shaderProgram.spotLightPos, spotLightPos);
		gl.uniform4fv(shaderProgram.spotLightLookAt, spotLightLookAt);
		gl.uniform1f(shaderProgram.spotCutOff, spotCutOff);
		
	}
}

var Light = {};



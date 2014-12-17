function LightManager(){

	this.isDay = true;
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
		
		if(this.lampOn) {
			var pointLightPos = [];
			pointLightPos[0] = vec4.clone([8.0, 2.0, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[0], pointLightPos[0], viewMatrix);
			pointLightPos[1] = vec4.clone([24.0, 2.0, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[1], pointLightPos[1], viewMatrix);
			pointLightPos[2] = vec4.clone([8.0, 10.5, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[2], pointLightPos[2], viewMatrix);
			pointLightPos[3] = vec4.clone([24.0, 10.5, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[3], pointLightPos[3], viewMatrix);
			pointLightPos[4] = vec4.clone([8.0, 19.0, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[4], pointLightPos[4], viewMatrix);
			pointLightPos[5] = vec4.clone([24.0, 19.0, 2.0, 1.0]);
			vec4.transformMat4(pointLightPos[5], pointLightPos[5], viewMatrix);

			gl.uniform4fv(shaderProgram.pointLightPos, pointLightPos[0][0],
													   pointLightPos[0][1],
													   pointLightPos[0][2],
													   pointLightPos[0][3],
													   pointLightPos[1][0],
													   pointLightPos[1][1],
													   pointLightPos[1][2],
													   pointLightPos[1][3],
													   pointLightPos[2][0],
													   pointLightPos[2][1],
													   pointLightPos[2][2],
													   pointLightPos[2][3],
													   pointLightPos[3][0],
													   pointLightPos[3][1],
													   pointLightPos[3][2],
													   pointLightPos[3][3],
													   pointLightPos[4][0],
													   pointLightPos[4][1],
													   pointLightPos[4][2],
													   pointLightPos[4][3],
													   pointLightPos[5][0],
													   pointLightPos[5][1],
													   pointLightPos[5][2],
													   pointLightPos[5][3]);
		}

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



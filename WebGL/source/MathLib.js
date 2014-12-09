var mvMatrix = mat4.create();
var pMatrix = mat4.create();
var mvMatrixStack = [];

function mvPushMatrix() {
	var copy = mat4.create();
	mat4.set(mvMatrix, copy);
	mvMatrixStack.push(copy);
}

function mvPopMatrix() {
	if (mvMatrixStack.length == 0) {
		throw "Invalid popMatrix!";
	}
	mvMatrix = mvMatrixStack.pop();
}

function setMatrixUniforms() {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);

	//  var normalMatrix = mat3.create();
	// mat4.toInverseMat3(mvMatrix, normalMatrix);
	// mat3.transpose(normalMatrix);
	// gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, normalMatrix);
}

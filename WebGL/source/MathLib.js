var mvMatrix = mat4.create();
var pMatrix = mat4.create();
var viewMatrix = mat4.create();
var mvMatrixStack = [];

function mvPushMatrix() {
	var copy = mat4.clone(mvMatrix, copy);
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

	var normalMatrix = mat3.create();
	mat3.fromMat4(normalMatrix, mvMatrix);
	//mat3.invert(normalMatrix, normalMatrix);
	//mat3.transpose(normalMatrix, normalMatrix);

	var det;
	var invDet;

	det = normalMatrix[0] * (normalMatrix[4] * normalMatrix[8] - normalMatrix[5] * normalMatrix[7]) +
		  normalMatrix[1] * (normalMatrix[5] * normalMatrix[6] - normalMatrix[8] * normalMatrix[3]) +
		  normalMatrix[2] * (normalMatrix[3] * normalMatrix[7] - normalMatrix[4] * normalMatrix[6]);

	invDet = 1.0/det;

	var mNormal3x3 = mat3.create();
	mNormal3x3[0] = (normalMatrix[4] * normalMatrix[8] - normalMatrix[5] * normalMatrix[7]) * invDet;
	mNormal3x3[1] = (normalMatrix[5] * normalMatrix[6] - normalMatrix[8] * normalMatrix[3]) * invDet;
	mNormal3x3[2] = (normalMatrix[3] * normalMatrix[7] - normalMatrix[4] * normalMatrix[6]) * invDet;
	mNormal3x3[3] = (normalMatrix[2] * normalMatrix[7] - normalMatrix[1] * normalMatrix[8]) * invDet;
	mNormal3x3[4] = (normalMatrix[0] * normalMatrix[8] - normalMatrix[2] * normalMatrix[6]) * invDet;
	mNormal3x3[5] = (normalMatrix[1] * normalMatrix[6] - normalMatrix[7] * normalMatrix[0]) * invDet;
	mNormal3x3[6] = (normalMatrix[1] * normalMatrix[5] - normalMatrix[4] * normalMatrix[2]) * invDet;
	mNormal3x3[7] = (normalMatrix[2] * normalMatrix[3] - normalMatrix[0] * normalMatrix[5]) * invDet;
	mNormal3x3[8] = (normalMatrix[0] * normalMatrix[4] - normalMatrix[3] * normalMatrix[1]) * invDet;

	gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, mNormal3x3);
}

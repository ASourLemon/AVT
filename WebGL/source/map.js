function Map(){

	this.deltaWater = 0.0;
	this.goingLeft = false;
	this.win_x = 10.0;
	this.win_y = 0.0;
	this.win_z = 28.0;
	
	this.map0_W = 20.0;
	this.map0_H = 32.0;
	this.water_speed = 0.3;
}

Map.prototype.draw = function(){
	mvPushMatrix();
	//mat4.rotate(mvMatrix, mvMatrix, 2.0, [1.0, 0.0, 0.0]);

	//
	//WATER
	//
	gl.clear(gl.STENCIL_BUFFER_BIT);
	gl.enable(gl.STENCIL_TEST);
	gl.stencilFunc(gl.ALWAYS, 1,0x01);
	gl.stencilOp(gl.KEEP, gl.KEEP, gl.REPLACE);
	gl.colorMask(true,true, true, true);
	gl.depthMask(false);
	gl.clear(gl.STENCIL_BUFFER_BIT); 

	gl.disable(gl.DEPTH_TEST);
	gl.enable(gl.BLEND);
	gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

	gl.bindTexture(gl.TEXTURE_2D, texArray[1]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	this.setWaterColor();
	
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [16.0, 3.5/*bot*/ + 6.0/*road*/ + 2.0/*mid*/ + 3.0, -0.4]);
	mat4.scale(mvMatrix, mvMatrix, [32, 6, 1]);
	drawSquare();
	mvPopMatrix();
	gl.depthMask(true);
	gl.disable(gl.STENCIL_TEST);
	gl.disable(gl.BLEND);
	gl.enable(gl.DEPTH_TEST);
	//
	//FLOOR
	//
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, texArray[0]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	this.setGrassColor();

	//BOTTOM
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [16.0, 1.75, 0.0]);
	mat4.scale(mvMatrix, mvMatrix, [32, 3.5, 1]);
	drawSquare();
	mvPopMatrix();

	//MIDDLE
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [16.0, 3.5/*bot*/ + 6.0/*road*/ + 1.0, -0.25]);
	mat4.scale(mvMatrix, mvMatrix, [16, 1.0, 0.25]);
	drawCube();
	mvPopMatrix();

	//TOP
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [16.0, 3.5/*bot*/ + 6.0/*road*/ + 2.0/*mid*/ + 6.0/*water*/ + 1.75, -0.25]);
	mat4.scale(mvMatrix, mvMatrix, [16, 1.5, 0.25]);
	drawCube();
	mvPopMatrix();

	//
	//ROAD
	//
	gl.bindTexture(gl.TEXTURE_2D, texArray[2]);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	this.setRoadColor();
	
	mvPushMatrix();
	mat4.translate(mvMatrix, mvMatrix, [16.0, 3.5/*bot*/ + 3.0, 0.0]);
	mat4.scale(mvMatrix, mvMatrix, [32, 6, 1]);
	drawSquare();
	mvPopMatrix();

	

	mvPopMatrix();
	gl.bindTexture(gl.TEXTURE_2D, null);
}

Map.prototype.getMaplimit = function(){
	return this.map0_W;
}

Map.prototype.setGrassColor = function(){

	setDiffuse(0.2, 0.5, 0.2, 1.0);
	setAmbient(0.05/3.0, 0.125/3.0, 0.05/3.0, 1.0);
	setSpecular(0.0, 0.0, 0.0, 1.0);
	setShininess(1.0);
}

Map.prototype.setWaterColor = function(){

	setDiffuse(0.4, 0.6, 0.4, .7 );
	setAmbient(0.08, 0.12, 0.08, .7);
	setSpecular(0.0, 0.0, 0.1, .7 );
	setShininess(10);
}

Map.prototype.setWallColor = function(){

	setDiffuse(0.6, 0.6, 0.6, 1.0);
	setAmbient(0.3, 0.3, 0.3, 1.0);
	setSpecular(0.0, 0.0, 0.0, 1.0);
	setShininess(1);
}

Map.prototype.setRoadColor = function(){

	setDiffuse(0.3, 0.3, 0.3, 1.0);
	setAmbient(0.0, 0.0, 0.0, 1.0);
	setSpecular(0.0, 0.0, 0.0, 1.0);
	setShininess(1);
}
















// var triangleVertexPositionBuffer;
// var triangleVertexColorBuffer;
// var squareVertexPositionBuffer;
// var squareVertexColorBuffer;

// function create2DObjects(){
// 	triangleVertexPositionBuffer = gl.createBuffer();
// 	gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
// 	var vertices = [
// 		0.0, 1.0, 0.0,
// 		-1.0, -1.0, 0.0,
// 		1.0, -1.0, 0.0
// 	];
// 	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
// 	triangleVertexPositionBuffer.itemSize = 3;
// 	triangleVertexPositionBuffer.numItems = 3;

// 	triangleVertexColorBuffer = gl.createBuffer();
//     gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
//     var colors = [
//         1.0, 0.0, 0.0, 1.0,
//         0.0, 1.0, 0.0, 1.0,
//         0.0, 0.0, 1.0, 1.0
//     ];
//     gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
//     triangleVertexColorBuffer.itemSize = 4;
//     triangleVertexColorBuffer.numItems = 3;
	
// 	squareVertexPositionBuffer = gl.createBuffer();
// 	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
// 	vertices = [
// 		1.0, 1.0, 0.0,
// 		-1.0, 1.0, 0.0,
// 		1.0, -1.0, 0.0,
// 		-1.0, -1.0, 0.0
// 	];
// 	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
// 	squareVertexPositionBuffer.itemSize = 3;
// 	squareVertexPositionBuffer.numItems = 4;
						
// 	squareVertexColorBuffer = gl.createBuffer();
//     gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
//     colors = []
//     for (var i=0; i < 4; i++) {
//       colors = colors.concat([0.5, 0.5, 1.0, 1.0]);
//     }
//     gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
//     squareVertexColorBuffer.itemSize = 4;
//     squareVertexColorBuffer.numItems = 4;
	
// }




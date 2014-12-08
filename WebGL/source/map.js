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

Map.prototype = new GameObject();

Map.prototype.draw = function(){

	createCube();
	// mvPushMatrix();
	// mat4.translate(mvMatrix, [0.0, 0.0, -3.0]);
	// mat4.rotate(mvMatrix, 90.0, [1, 0, 0]);
	// createSquare(32.0, 16.0);
	// mvPushMatrix();

}

Map.prototype.update = function(){


	
}

Map.prototype.getMaplimit = function(){
	return this.map0_W;
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




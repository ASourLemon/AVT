var uMaterials = {};
// 	diffuse = [0.5, 0.5, 0.5, 1.0];
// 	ambient =  [0.5, 0.5, 0.5, 1.0];
// 	specular =  [0.5, 0.5, 0.5, 1.0];
// 	emissive =  [0.5, 0.5, 0.5, 1.0];
// 	shininess = 1;
// 	texCount = 0;

// 	setDiffuse: function (r, g, b, a){
// 		this.diffuse = [r, g, b, a];
// 	}
// 	setAmbient: function (r, g, b, a){
// 		this.ambient = [r, g, b, a];
// 	}
// 	setSpecular: function (r, g, b, a){
// 		this.specular = [r, g, b, a];
// 	}
// 	setEmissive: function (r, g, b, a){
// 		this.emissive = [r, g, b, a];
// 	}
// 	setShininess: function (v){
// 		this.shininess = v;
// 	}
// 	setTexCount: function (v){
// 		this.texCount = v;
// 	}

// };


function SetupMaterial(){

	
	
	//gl.uniform4fv(shaderProgram.Materials, uMaterials)
	uMaterials.diffuse = gl.getUniformLocation(shaderProgram,"material.diffuse");
	uMaterials.ambient = gl.getUniformLocation(shaderProgram,"material.ambient");
	uMaterials.specular = gl.getUniformLocation(shaderProgram,"material.specular");
	uMaterials.emissive = gl.getUniformLocation(shaderProgram,"material.emissive");
	uMaterials.shininess = gl.getUniformLocation(shaderProgram,"material.shininess");
	uMaterials.texCount = gl.getUniformLocation(shaderProgram,"material.texCount");

	setDiffuse(1.0, 1.0, 1.0, 1.0);
	setAmbient(1.0, 1.0, 1.0, 1.0);
	setSpecular(1.0, 1.0, 1.0, 1.0);
	setEmissive(0.0, 0.0, 0.0, 1.0);
	setShininess(1.0);
	setTexCount(0);

	
}

function setDiffuse (r, g, b, a){
	gl.uniform4f(uMaterials.diffuse, r, g, b, a);
}

function setAmbient (r, g, b, a){
	gl.uniform4f(uMaterials.ambient, r, g, b, a);
}

function setSpecular (r, g, b, a){
	gl.uniform4f(uMaterials.specular, r, g, b, a);
}

function setEmissive (r, g, b, a){
	gl.uniform4f(uMaterials.emissive, r, g, b, a);
}
function setShininess (v){
	gl.uniform1f(uMaterials.shininess, v);
}
function setTexCount (v){
	gl.uniform1i(uMaterials.texCount, v);
}


var squareVertexPositionBuffer;
var squareNormalsBuffer;
var squareVertexTexCoordBuffer;
var squareVertexIndexBuffer;

function drawSquare(){

	if(!drawSquare.initialized) {
		console.log("Square was created!"); // it is actually beeing created...
		drawSquare.initialized = true;
	
		squareVertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
		vertices = [
			-0.5, -0.5, 0.0, 1.0,
			-0.5, 0.5, 0.0, 1.0,
			0.5, 0.5, 0.0, 1.0,
			0.5, -0.5, 0.0, 1.0
			
		];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
		squareVertexPositionBuffer.itemSize = 4;
		squareVertexPositionBuffer.numItems = 4;

		squareTexCoordBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, squareTexCoordBuffer);
		
		textureCoords = [
			0.0, 0.0,
			0.0, 1.0,
			1.0, 1.0,
			1.0, 0.0
		];

		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
		squareTexCoordBuffer.itemSize = 2;
		squareTexCoordBuffer.numItems = 2;

		squareNormalsBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, squareNormalsBuffer);
		normals = [
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0
		];

		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
		squareNormalsBuffer.itemSize = 3;
		squareNormalsBuffer.numItems = 4;

		squareVertexIndexBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, squareVertexIndexBuffer);
		var squareVertexIndices = [
			0, 1, 2, 0, 2, 3, // Front face
		];
		gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(squareVertexIndices), gl.STATIC_DRAW);
		squareVertexIndexBuffer.itemSize = 1;
		squareVertexIndexBuffer.numItems = 6;

	} // initialization ended
	
	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, squareVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);
	gl.bindBuffer(gl.ARRAY_BUFFER, squareTexCoordBuffer);
	gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, squareTexCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
	gl.bindBuffer(gl.ARRAY_BUFFER, squareNormalsBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, squareNormalsBuffer.itemSize, gl.FLOAT, false, 0, 0);

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, squareVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, squareVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);

}

var cubeVertexPositionBuffer;
var cubeVertexNormalBuffer;
var cubeVertexIndexBuffer;
var cubeVertexTextureCoordBuffer;

function drawCube(){
    if(!drawCube.initialized) {
		console.log("Cube was created!"); // it is actually beeing created...
		drawCube.initialized = true;


	    cubeVertexPositionBuffer = gl.createBuffer();
	    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	    vertices = [
			// Front face
			-1.0, -1.0, 1.0,
			1.0, -1.0, 1.0,
			1.0, 1.0, 1.0,
			-1.0, 1.0, 1.0,
			// Back face
			-1.0, -1.0, -1.0,
			-1.0, 1.0, -1.0,
			1.0, 1.0, -1.0,
			1.0, -1.0, -1.0,
			// Top face
			-1.0, 1.0, -1.0,
			-1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
			1.0, 1.0, -1.0,
			// Bottom face
			-1.0, -1.0, -1.0,
			1.0, -1.0, -1.0,
			1.0, -1.0, 1.0,
			-1.0, -1.0, 1.0,
			// Right face
			1.0, -1.0, -1.0,
			1.0, 1.0, -1.0,
			1.0, 1.0, 1.0,
			1.0, -1.0, 1.0,
			// Left face
			-1.0, -1.0, -1.0,
			-1.0, -1.0, 1.0,
			-1.0, 1.0, 1.0,
			-1.0, 1.0, -1.0,
		];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
		cubeVertexPositionBuffer.itemSize = 3;
		cubeVertexPositionBuffer.numItems = 24;

		cubeVertexNormalBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
        var vertexNormals = [
            // Front face
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
             0.0,  0.0,  1.0,
            // Back face
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
             0.0,  0.0, -1.0,
            // Top face
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
             0.0,  1.0,  0.0,
            // Bottom face
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
             0.0, -1.0,  0.0,
            // Right face
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
             1.0,  0.0,  0.0,
            // Left face
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0,
            -1.0,  0.0,  0.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexNormals), gl.STATIC_DRAW);
        cubeVertexNormalBuffer.itemSize = 3;
        cubeVertexNormalBuffer.numItems = 24;
		
		cubeVertexTextureCoordBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
		var textureCoords = [
			// Front face
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
			// Back face
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
			0.0, 0.0,
			// Top face
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			// Bottom face
			1.0, 1.0,
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,
			// Right face
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
			0.0, 0.0,
			// Left face
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
		];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
		cubeVertexTextureCoordBuffer.itemSize = 2;
		cubeVertexTextureCoordBuffer.numItems = 24;
		
		cubeVertexIndexBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
		var cubeVertexIndices = [
			0, 1, 2, 0, 2, 3, // Front face
			4, 5, 6, 4, 6, 7, // Back face
			8, 9, 10, 8, 10, 11, // Top face
			12, 13, 14, 12, 14, 15, // Bottom face
			16, 17, 18, 16, 18, 19, // Right face
			20, 21, 22, 20, 22, 23 // Left face
		];
		gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
		cubeVertexIndexBuffer.itemSize = 1;
		cubeVertexIndexBuffer.numItems = 36;

	} // initialization ended

	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, cubeVertexNormalBuffer.itemSize, gl.FLOAT, false, 0, 0);
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
}

var sphereVertexNormalBuffer;
var sphereVertexTextureCoordBuffer;
var sphereVertexPositionBuffer;
var sphereVertexIndexBuffer;

function drawSphere(){

	if(!drawSphere.initialized) {
		console.log("Sphere was created!"); // it is actually beeing created...
		drawSphere.initialized = true;


        var latitudeBands = 30;
        var longitudeBands = 30;
        var radius = 0.5;

		var vertexPositionData = [];
	    var normalData = [];
	    var textureCoordData = [];
	    for (var latNumber = 0; latNumber <= latitudeBands; latNumber++) {
	      var theta = latNumber * Math.PI / latitudeBands;
	      var sinTheta = Math.sin(theta);
	      var cosTheta = Math.cos(theta);

	      for (var longNumber = 0; longNumber <= longitudeBands; longNumber++) {
	        var phi = longNumber * 2 * Math.PI / longitudeBands;
	        var sinPhi = Math.sin(phi);
	        var cosPhi = Math.cos(phi);

	        var x = cosPhi * sinTheta;
	        var y = cosTheta;
	        var z = sinPhi * sinTheta;
	        var u = 1 - (longNumber / longitudeBands);
	        var v = 1 - (latNumber / latitudeBands);

	        normalData.push(x);
	        normalData.push(y);
	        normalData.push(z);
	        textureCoordData.push(u);
	        textureCoordData.push(v);
	        vertexPositionData.push(radius * x);
	        vertexPositionData.push(radius * y);
	        vertexPositionData.push(radius * z);
	      }
	    }

		var indexData = [];
	    for (var latNumber = 0; latNumber < latitudeBands; latNumber++) {
	      for (var longNumber = 0; longNumber < longitudeBands; longNumber++) {
	        var first = (latNumber * (longitudeBands + 1)) + longNumber;
	        var second = first + longitudeBands + 1;
	        indexData.push(first);
	        indexData.push(second);
	        indexData.push(first + 1);

	        indexData.push(second);
	        indexData.push(second + 1);
	        indexData.push(first + 1);
	      }
	    }


	    // Normals
	    sphereVertexNormalBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexNormalBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normalData), gl.STATIC_DRAW);
        sphereVertexNormalBuffer.itemSize = 3;
        sphereVertexNormalBuffer.numItems = normalData.length / 3;

		// Tex Coords
        sphereVertexTextureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexTextureCoordBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordData), gl.STATIC_DRAW);
        sphereVertexTextureCoordBuffer.itemSize = 2;
        sphereVertexTextureCoordBuffer.numItems = textureCoordData.length / 2;

		// Positions
        sphereVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexPositionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexPositionData), gl.STATIC_DRAW);
        sphereVertexPositionBuffer.itemSize = 3;
        sphereVertexPositionBuffer.numItems = vertexPositionData.length / 3;

		// Indices
        sphereVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, sphereVertexIndexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexData), gl.STATIC_DRAW);
        sphereVertexIndexBuffer.itemSize = 1;
        sphereVertexIndexBuffer.numItems = indexData.length;
    } // initialization ended

    
	gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexTextureCoordBuffer);
	gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, sphereVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, sphereVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);
	gl.bindBuffer(gl.ARRAY_BUFFER, sphereVertexNormalBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, sphereVertexNormalBuffer.itemSize, gl.FLOAT, false, 0, 0);

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, sphereVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, sphereVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);

}

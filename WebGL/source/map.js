//document.write('<script language="javascript" src="glMatrix-0.9.5.min.js"></script>');

/*var triangleVertexPositionBuffer;
			var squareVertexPositionBuffer;

			function initBuffers() {
				triangleVertexPositionBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
				
				var vertices = [
				0.0, 1.0, 0.0,
				-1.0, -1.0, 0.0,
				1.0, -1.0, 0.0
				];
				
				
				
				squareVertexPositionBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
				
				vertices = [
				0.0, 1.0, 0.0,
				-1.0, -1.0, 0.0,
				1.0, -1.0, 0.0
				];
				
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
				squareVertexPositionBuffer.itemSize = 3;
				squareVertexPositionBuffer.numItems = 3;
			}*/


			var triangleVertexPositionBuffer;
			var triangleVertexColorBuffer;
			var squareVertexPositionBuffer;
			var squareVertexColorBuffer;

			function create2DObjects(){
				triangleVertexPositionBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
				var vertices = [
					0.0, 1.0, 0.0,
					-1.0, -1.0, 0.0,
					1.0, -1.0, 0.0
				];
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
				triangleVertexPositionBuffer.itemSize = 3;
				triangleVertexPositionBuffer.numItems = 3;

				triangleVertexColorBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
			    var colors = [
			        1.0, 0.0, 0.0, 1.0,
			        0.0, 1.0, 0.0, 1.0,
			        0.0, 0.0, 1.0, 1.0
			    ];
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
			    triangleVertexColorBuffer.itemSize = 4;
			    triangleVertexColorBuffer.numItems = 3;
				
				squareVertexPositionBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
				vertices = [
					1.0, 1.0, 0.0,
					-1.0, 1.0, 0.0,
					1.0, -1.0, 0.0,
					-1.0, -1.0, 0.0
				];
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
				squareVertexPositionBuffer.itemSize = 3;
				squareVertexPositionBuffer.numItems = 4;
									
				squareVertexColorBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
			    colors = []
			    for (var i=0; i < 4; i++) {
			      colors = colors.concat([0.5, 0.5, 1.0, 1.0]);
			    }
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
			    squareVertexColorBuffer.itemSize = 4;
			    squareVertexColorBuffer.numItems = 4;
				
			}

			var pyramidVertexPositionBuffer;
			var pyramidVertexColorBuffer;
			var cubeVertexPositionBuffer;
			var cubeVertexColorBuffer;
			var cubeVertexIndexBuffer;

			function create3DObjects(){
				//Pyramid
			    pyramidVertexPositionBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, pyramidVertexPositionBuffer);
			    var vertices = [
			        // Front face
			         0.0,  1.0,  0.0,
			        -1.0, -1.0,  1.0,
			         1.0, -1.0,  1.0,
			        // Right face
			         0.0,  1.0,  0.0,
			         1.0, -1.0,  1.0,
			         1.0, -1.0, -1.0,
			        // Back face
			         0.0,  1.0,  0.0,
			         1.0, -1.0, -1.0,
			        -1.0, -1.0, -1.0,
			        // Left face
			         0.0,  1.0,  0.0,
			        -1.0, -1.0, -1.0,
			        -1.0, -1.0,  1.0
			    ];
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
			    pyramidVertexPositionBuffer.itemSize = 3;
			    pyramidVertexPositionBuffer.numItems = 12;

			    pyramidVertexColorBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, pyramidVertexColorBuffer);
			    var colors = [
			        // Front face
			        1.0, 0.0, 0.0, 1.0,
			        0.0, 1.0, 0.0, 1.0,
			        0.0, 0.0, 1.0, 1.0,
			        // Right face
			        1.0, 0.0, 0.0, 1.0,
			        0.0, 0.0, 1.0, 1.0,
			        0.0, 1.0, 0.0, 1.0,
			        // Back face
			        1.0, 0.0, 0.0, 1.0,
			        0.0, 1.0, 0.0, 1.0,
			        0.0, 0.0, 1.0, 1.0,
			        // Left face
			        1.0, 0.0, 0.0, 1.0,
			        0.0, 0.0, 1.0, 1.0,
			        0.0, 1.0, 0.0, 1.0
			    ];
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
			    pyramidVertexColorBuffer.itemSize = 4;
			    pyramidVertexColorBuffer.numItems = 12;

			    //Cube
			    cubeVertexPositionBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
			    vertices = [
			      // Front face
			      -1.0, -1.0,  1.0,
			       1.0, -1.0,  1.0,
			       1.0,  1.0,  1.0,
			      -1.0,  1.0,  1.0,

			      // Back face
			      -1.0, -1.0, -1.0,
			      -1.0,  1.0, -1.0,
			       1.0,  1.0, -1.0,
			       1.0, -1.0, -1.0,

			      // Top face
			      -1.0,  1.0, -1.0,
			      -1.0,  1.0,  1.0,
			       1.0,  1.0,  1.0,
			       1.0,  1.0, -1.0,

			      // Bottom face
			      -1.0, -1.0, -1.0,
			       1.0, -1.0, -1.0,
			       1.0, -1.0,  1.0,
			      -1.0, -1.0,  1.0,

			      // Right face
			       1.0, -1.0, -1.0,
			       1.0,  1.0, -1.0,
			       1.0,  1.0,  1.0,
			       1.0, -1.0,  1.0,

			      // Left face
			      -1.0, -1.0, -1.0,
			      -1.0, -1.0,  1.0,
			      -1.0,  1.0,  1.0,
			      -1.0,  1.0, -1.0,
			    ];
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
			    cubeVertexPositionBuffer.itemSize = 3;
			    cubeVertexPositionBuffer.numItems = 24;

				cubeVertexColorBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexColorBuffer);
			    colors = [
			      [1.0, 0.0, 0.0, 1.0],     // Front face
			      [1.0, 1.0, 0.0, 1.0],     // Back face
			      [0.0, 1.0, 0.0, 1.0],     // Top face
			      [1.0, 0.5, 0.5, 1.0],     // Bottom face
			      [1.0, 0.0, 1.0, 1.0],     // Right face
			      [0.0, 0.0, 1.0, 1.0],     // Left face
			    ];
			    var unpackedColors = [];
			    for (var i in colors) {
			      var color = colors[i];
			      for (var j=0; j < 4; j++) {
			        unpackedColors = unpackedColors.concat(color);
			      }
			    }
			    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(unpackedColors), gl.STATIC_DRAW);
			    cubeVertexColorBuffer.itemSize = 4;
			    cubeVertexColorBuffer.numItems = 24;

			    cubeVertexIndexBuffer = gl.createBuffer();
			    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
			    var cubeVertexIndices = [
			      0, 1, 2,      0, 2, 3,    // Front face
			      4, 5, 6,      4, 6, 7,    // Back face
			      8, 9, 10,     8, 10, 11,  // Top face
			      12, 13, 14,   12, 14, 15, // Bottom face
			      16, 17, 18,   16, 18, 19, // Right face
			      20, 21, 22,   20, 22, 23  // Left face
			    ]
			    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
			    cubeVertexIndexBuffer.itemSize = 1;
			    cubeVertexIndexBuffer.numItems = 36;


			}


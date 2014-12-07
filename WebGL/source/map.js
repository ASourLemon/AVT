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

			function createRectangle(){
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
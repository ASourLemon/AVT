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

var rectangleVertexPositionBuffer;
var rectangleVertexNormalsBuffer;
			function initBuffers() {

				createRectangle(2.0, 2.0);
			}

			function createRectangle(height, width){
				
				// var height = h;
				// var width = w;
				var vertices = [
					
					width/2, height/2, 0.0, 
					-width/2, height/2, 0.0,
					width/2, -height/2, 0.0,
					-width/2, -height/2, 0.0
					
				];

				var normals = [
					-1.0, 0.0, -1.0,
					-1.0, 0.0, -1.0,
					1.0, 0.0, -1.0,
					1.0, 0.0, -1.0
				];

				var texCoords = [
					0.0, 0.0,
					0.0, 1.0,
					1.0, 1.0,
					1.0, 0.0
				];

				var faceIndex = [
					0,1,2,0,2,3
				];

				
				
				rectangleVertexPositionBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, rectangleVertexPositionBuffer)
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
				rectangleVertexPositionBuffer.itemSize = 3;
				rectangleVertexPositionBuffer.numItems = 4;

				
				
				rectangleVertexNormalsBuffer = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, rectangleVertexNormalsBuffer)
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
				rectangleVertexNormalsBuffer.itemSize = 3;
				rectangleVertexNormalsBuffer.numItems = 4;
				
			}
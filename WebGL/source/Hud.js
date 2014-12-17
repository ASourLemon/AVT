function Hud(){
  
}

Hud.prototype.drawText = function(x, y, text, fontSize) {
  
  
	mvPushMatrix();
	pPushMatrix();
	
  	mat4.identity(mvMatrix);
	mat4.identity(pMatrix);
	
	mat4.ortho(pMatrix, 0.0, gl.viewportWidth, 0.0, gl.viewportHeight, -1.0, 1.0);
	
	mat4.translate(mvMatrix, mvMatrix, [x+fontSize/2, y+fontSize/2, 0.0]);
	
	gl.disable(gl.DEPTH_TEST);
 	gl.bindTexture(gl.TEXTURE_2D, texArray[6]);
	var oneOverSixteen = (1.0 / 16.0);
	var ratio = gl.viewportWidth / gl.viewportHeight;


	textureCoords = [
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0
	];

	for(var i = 0; i < text.length; ++i){ 

	  ch = text[i];
	  ch = ch.charCodeAt(0);
	  console.log(ch);
	  xPos = (ch % 16) * oneOverSixteen;
	  yPos = (ch / 16) * oneOverSixteen;
	  
	  yPos = (oneOverSixteen * 16) - yPos - oneOverSixteen;
	  
	  textureCoords[2] = xPos;
	  textureCoords[3] = 1.0 - yPos - oneOverSixteen;

	  textureCoords[4] = xPos + oneOverSixteen;
	  textureCoords[5] = 1.0 - yPos - oneOverSixteen;

	  textureCoords[6] = xPos + oneOverSixteen;
	  textureCoords[7] = 1.0 - yPos - 0.001;

	  textureCoords[0] = xPos;
	  textureCoords[1] = 1.0 - yPos - 0.001;


	  mvPushMatrix();
	  if(ratio>1.0){
	    mat4.scale(mvMatrix, mvMatrix, [fontSize*ratio*0.75, fontSize, 1.0]);
	  }else {
	    mat4.scale(mvMatrix, mvMatrix, [fontSize*0.75, fontSize*ratio, 1.0]);
	  }

	  drawChar(textureCoords);
	  mvPopMatrix();

	  mat4.translate(mvMatrix, mvMatrix, [fontSize * 1.2, 0.0, 0.0]);

	}
	
	
	  


	
	
	gl.enable(gl.DEPTH_TEST);
	
	gl.bindTexture(gl.TEXTURE_2D, texArray[3]);
	pPopMatrix();
	mvPopMatrix();
}

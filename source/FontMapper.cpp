#include "../include/FontMapper.h"

FontMapper::FontMapper() : _fontSize(26.0) {
}
FontMapper::~FontMapper(){
}

bool FontMapper::Init()
{
	float vertices [] = {
		0.0f, 0.0f,
		_fontSize, 0.0f,
		_fontSize, _fontSize,
		0.0f, _fontSize
	};
	
	glGenVertexArrays(1, &_vaoID);
	glBindVertexArray(_vaoID);
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	float texCoords[] = {
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};

	glGenBuffers(1, &_texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &texCoords[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);
	
	return true;
}

void FontMapper::DrawString(VSShaderLib* shader, float x, float y, const char* string, bool selected){
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(glGetUniformLocation(shader->getProgramIndex(), "selected"), selected);
	
	VSMathLib* core = VSMathLib::getInstance();
	
	core->pushMatrix(VSMathLib::PROJECTION);	
	core->loadIdentity(VSMathLib::PROJECTION);
	
	core->pushMatrix(VSMathLib::VIEW);
	core->loadIdentity(VSMathLib::VIEW);
	
	core->pushMatrix(VSMathLib::MODEL);
	core->loadIdentity(VSMathLib::MODEL);
	
	core->translate(x, y, 0);
	//left, right, bot, top, near, far
	core->ortho(.0f, float(WinX), .0f, float(WinY), -1.0f, 1.0f);

	const float oneOverSixteen = 1.0f / 16.0f;
	int i = 0;
	char c = string[i];
	
	float texCoords [] = {
	    0.0f, 0.0f,
	    0.0f, 0.0f,
	    0.0f, 0.0f,
	    0.0f, 0.0f
	};
	
	while(c != ((int) '\0')){
		int ch = int(string[i]);
		float xPos = float(ch % 16) * oneOverSixteen;
		float yPos = float(ch / 16) * oneOverSixteen;	
		texCoords[0] = xPos;
		texCoords[1] = 1.0f - yPos - oneOverSixteen;

		texCoords[2] = xPos + oneOverSixteen;
		texCoords[3] = 1.0f - yPos - oneOverSixteen;

		texCoords[4] = xPos + oneOverSixteen;
		texCoords[5] = 1.0f - yPos - 0.001f;

		texCoords[6] = xPos;
		texCoords[7] = 1.0f - yPos - 0.001f;
		
		glBindBuffer(GL_ARRAY_BUFFER, _texCoordBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, &texCoords[0]);		
		glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
		
		//draw
		core->matricesToGL();
		glBindVertexArray(_vaoID);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
		
		c = string[++i];
		core->translate(_fontSize, 0, 0);
	}
	
	glEnable(GL_DEPTH_TEST);
	core->popMatrix(VSMathLib::MODEL);	
	core->popMatrix(VSMathLib::VIEW);
	core->popMatrix(VSMathLib::PROJECTION);	

}

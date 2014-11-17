#ifndef INCLUDE_TMF_H_
#define INCLUDE_TMF_H_

#include <string.h>
#include <stdio.h>
#include "drawable.h"
#include "vsMathLib.h"
#include "vsShaderLib.h"
#include "vsResSurfRevLib.h"

extern int WinY;
extern int WinX;

using namespace std;

class FontMapper
{
public:
	FontMapper(void);
	FontMapper(const string& fontTexture, float fontSize=16.0f);
	~FontMapper(void);

	bool Init();
	void DrawString(VSShaderLib* shader, float x, float y, const char* string, bool selected=false);

private:
	GLuint _textureID, _vaoID;

	GLuint _texCoordBuffer;
	GLuint _vertexBuffer;
	float _fontSize;
};


#endif

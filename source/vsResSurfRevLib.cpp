/** ----------------------------------------------------------
 * \class VSResSurfRevLib
 *
 * Lighthouse3D
 *
 * VSResSurfRevLib - Very Simple Surfaces of Revolution Model Library
 *
 * \version 0.1.0
 *		Initial Release
 *
 * This lib provides an interface to create models
 * based on surfaces of revolution 
 *
 * This lib requires the following classes from VSL:
 * (http://www.lighthouse3d.com/very-simple-libs)
 *
 * VSResourceLib
 * VSMathLib 
 * VSLogLib
 * VSShaderLib
 *
 * and the following third party libs:
 *
 * GLEW (http://glew.sourceforge.net/),
 *
 * Full documentation at 
 * http://www.lighthouse3d.com/very-simple-libs
 *
 ---------------------------------------------------------------*/

#include "../include/vsResSurfRevLib.h"

#include "../include/vsMathLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

VSResSurfRevLib::VSResSurfRevLib() {
}

VSResSurfRevLib::~VSResSurfRevLib() {
}

void VSResSurfRevLib::clone(VSResourceLib *res) {

	if (res == NULL)
		return;

	VSResSurfRevLib *r = (VSResSurfRevLib *) res;

	this->mMyMesh = r->mMyMesh;
}

bool VSResSurfRevLib::load(std::string filename) {

	return false;
}

void VSResSurfRevLib::createSphere(float radius, int divisions) {

	float *p = circularProfile(-3.14159f / 2.0f, 3.14159f / 2.0f, radius,
			divisions);
	computeVAO(divisions + 1, p + 2, p, divisions * 2, 0.0f);
}

void VSResSurfRevLib::createTorus(float innerRadius, float outerRadius,
		int rings, int sides) {

	float tubeRadius = (outerRadius - innerRadius) * 0.5f;
	float *p = circularProfile(-3.14159f, 3.14159f, tubeRadius, sides,
			innerRadius + tubeRadius);
	computeVAO(sides + 1, p + 2, p, rings, 0.0f);
}

void VSResSurfRevLib::createCylinder(float height, float radius, int sides) {

	float p[] = { -radius, -height * 0.5f, 0.0f, -height * 0.5f, radius, -height
			* 0.5f, radius, height * 0.5f, 0.0f, height * 0.5f, -radius, height
			* 0.5f };

	computeVAO(4, p + 2, p, sides, 0.0f);
}

void VSResSurfRevLib::createRectangle(float height, float width) {
	float vertices[] = {
		-width, 0.0f, -height, 1.0f,
		-width, 0.0f, height, 1.0f,
		width, 0.0f, height, 1.0f,
		width, 0.0f, -height, 1.0f
	};

	float normals[] = {
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	float texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	unsigned int faceIndex[] = {
		2,1,0,3,2,0
	};

	glGenVertexArrays(1, &mMyMesh.vao);
	glBindVertexArray(mMyMesh.vao);

	GLuint buffers[4];
	glGenBuffers(4, buffers);

	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0,
			0);

	//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
	glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0,
			0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex,
			GL_STATIC_DRAW);

	// unbind the VAO
	glBindVertexArray(0);

	mMyMesh.numIndexes = 6;
	mMyMesh.type = GL_TRIANGLES;
}

void VSResSurfRevLib::createCone(float height, float baseRadius, int sides) {

	float v[2];
	v[0] = -baseRadius;
	v[1] = height;

	std::vector<float> p;

	p.push_back(-baseRadius);
	p.push_back(0.0f);
	p.push_back(0.0f);
	p.push_back(0.0f);
	p.push_back(baseRadius);
	p.push_back(0.0f);
	int max = (int) (1 + height / (baseRadius * 2 * 3.14159 / sides));
	for (int i = 0; i < max; ++i) {

		p.push_back(baseRadius - i * baseRadius / max);
		p.push_back(i * height / max);
	}
	p.push_back(0.0f);
	p.push_back(height);
	p.push_back(-baseRadius);
	p.push_back(height * 2.0f);
	//float p[(sides+3)*2] = {
	//		-baseRadius,	0.0, 
	//		0.0f,			0.0, 
	//		baseRadius,		0.0f,
	//		baseRadius + v[0] * 0.1,		v[1] * 0.1,
	//		baseRadius + v[0] * 0.2,		v[1] * 0.2,
	//		baseRadius + v[0] * 0.3,		v[1] * 0.3,
	//		baseRadius + v[0] * 0.4,		v[1] * 0.4,
	//		baseRadius + v[0] * 0.5,		v[1] * 0.5,
	//		baseRadius + v[0] * 0.6,		v[1] * 0.6,
	//		baseRadius + v[0] * 0.7,		v[1] * 0.7,
	//		baseRadius + v[0] * 0.8,		v[1] * 0.8,
	//		baseRadius + v[0] * 0.9,		v[1] * 0.9,
	//		0.0f,			height,  
	//		-baseRadius,	height*2.0f,
	//	};

	computeVAO((p.size() - 4) / 2, &(p[2]), &(p[0]), sides, 0.0f);
}

void VSResSurfRevLib::createPawn() {

	float p2[] = { 0.0f, 0.0f, 0.98f, 0.0f, 0.98f, 0.01f, 0.99f, 0.02f, 1.0f,
			0.02f, 1.0f, 0.3f, 0.99f, 0.31f, 0.98f, 0.32f, 0.93f, 0.32f,

			0.95f, 0.38f, 0.965f, 0.44f, 0.97f, 0.48f, 0.965f, 0.52f, 0.95f,
			0.56f, 0.89f, 0.62f, 0.83f, 0.66f, 0.75f, 0.70f, 0.66f, 0.735f,
			0.65f, 0.74f,

			0.611f, 0.83f, 0.5f, 0.83f,

			0.35f, 2.0f,

			0.58f, 2.075f, 0.610f, 2.10f, 0.6225f, 2.1125f, 0.625f, 2.125f,
			0.6225f, 2.1375f, 0.610f, 2.15f, 0.58f, 2.175f,

			0.32f, 2.27f, 0.46f, 2.38f, 0.56f, 2.514f, 0.628f, 2.67f, 0.65f,
			2.84f,

			0.628f, 3.01f, 0.56f, 3.164f, 0.46f, 3.3f, 0.32f, 3.40f, 0.168f,
			3.467f, 0.0f, 3.486f };
	create(p2, 40, 30, 1, 0.6f);
}

void VSResSurfRevLib::create(float *p, int numP, int sides, int closed,
		float smoothCos) {

	int i;
	// two extra points are added for normal computation

	float *points = (float *) malloc(sizeof(float) * (numP + 2) * 2);

	for (i = 2; i < (numP + 1) * 2; i++) {
		points[i] = p[i - 2];
	}

	// distinguishes between closed curves and open curves
	// for normal computation
	int numPoints = numP + 2;

	if (closed) {

		points[0] = p[(numP - 2) * 2];
		points[1] = p[(numP - 2) * 2 + 1];

		points[(numPoints - 1) * 2] = p[2];
		points[(numPoints - 1) * 2 + 1] = p[3];
	} else {

		points[0] = points[2] + (points[2] - points[4]);
		points[1] = points[3] + (points[3] - points[5]);

		points[(numPoints - 1) * 2] = points[(numPoints - 2) * 2]
				+ (points[(numPoints - 2) * 2] - points[(numPoints - 3) * 2]);
		points[(numPoints - 1) * 2 + 1] = points[(numPoints - 2) * 2 + 1]
				+ (points[(numPoints - 2) * 2 + 1]
						- points[(numPoints - 3) * 2 + 1]);
	}

	computeVAO(numP, p, points, sides, smoothCos);
}

void VSResSurfRevLib::createCube(float side) {

	glGenVertexArrays(1, &mMyMesh.vao);
	glBindVertexArray(mMyMesh.vao);

	GLuint buffers[4];
	glGenBuffers(4, buffers);

//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0,
			0);

//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
	glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0,
			0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex,
			GL_STATIC_DRAW);

// unbind the VAO
	glBindVertexArray(0);

	mMyMesh.numIndexes = faceCount * 3;

	mMyMesh.type = GL_TRIANGLES;
}

void VSResSurfRevLib::computeVAO(int numP, float *p, float *points, int sides,
		float smoothCos) {
	// Compute and store vertices

	int numSides = sides;
	int numPoints = numP + 2;

	float *vertex = (float *) malloc(
			sizeof(float) * numP * 2 * 4 * (numSides + 1));
	float *normal = (float *) malloc(
			sizeof(float) * numP * 2 * 4 * (numSides + 1));
	float *textco = (float *) malloc(
			sizeof(float) * numP * 2 * 4 * (numSides + 1));

	float inc = 2 * 3.14159f / (numSides);
	float nx, ny;
	float delta;
	int smooth;
	std::vector<int> smoothness;
	int k = 0;
	for (int i = 0; i < numP; i++) {
		revSmoothNormal2(points + (i * 2), &nx, &ny, smoothCos, 0);
		for (int j = 0; j <= numSides; j++) {

			if ((i == 0 && p[0] == 0.0f)
					|| (i == numP - 1 && p[(i + 1) * 2] == 0.0))
				delta = inc * 0.5f;
			else
				delta = 0.0f;

			normal[((k) * (numSides + 1) + j) * 4] = nx * cos(j * inc + delta);
			normal[((k) * (numSides + 1) + j) * 4 + 1] = ny;
			normal[((k) * (numSides + 1) + j) * 4 + 2] = nx
					* sin(-j * inc + delta);
			normal[((k) * (numSides + 1) + j) * 4 + 3] = 0.0f;

			vertex[((k) * (numSides + 1) + j) * 4] = p[i * 2] * cos(j * inc);
			vertex[((k) * (numSides + 1) + j) * 4 + 1] = p[(i * 2) + 1];
			vertex[((k) * (numSides + 1) + j) * 4 + 2] = p[i * 2]
					* sin(-j * inc);
			vertex[((k) * (numSides + 1) + j) * 4 + 3] = 1.0f;

			textco[((k) * (numSides + 1) + j) * 4] = ((j + 0.0f) / numSides);
			textco[((k) * (numSides + 1) + j) * 4 + 1] = (i + 0.0f)
					/ (numP - 1);
			textco[((k) * (numSides + 1) + j) * 4 + 2] = 0;
			textco[((k) * (numSides + 1) + j) * 4 + 3] = 1.0f;
		}
		k++;
		if (i < numP - 1) {
			smooth = revSmoothNormal2(points + ((i + 1) * 2), &nx, &ny,
					smoothCos, 1);

			if (!smooth) {
				smoothness.push_back(1);
				for (int j = 0; j <= numSides; j++) {

					normal[((k) * (numSides + 1) + j) * 4] = nx * cos(j * inc);
					normal[((k) * (numSides + 1) + j) * 4 + 1] = ny;
					normal[((k) * (numSides + 1) + j) * 4 + 2] = nx
							* sin(-j * inc);
					normal[((k) * (numSides + 1) + j) * 4 + 3] = 0.0f;

					vertex[((k) * (numSides + 1) + j) * 4] = p[(i + 1) * 2]
							* cos(j * inc);
					vertex[((k) * (numSides + 1) + j) * 4 + 1] = p[((i + 1) * 2)
							+ 1];
					vertex[((k) * (numSides + 1) + j) * 4 + 2] = p[(i + 1) * 2]
							* sin(-j * inc);
					vertex[((k) * (numSides + 1) + j) * 4 + 3] = 1.0f;

					textco[((k) * (numSides + 1) + j) * 4] = ((j + 0.0f)
							/ numSides);
					textco[((k) * (numSides + 1) + j) * 4 + 1] = (i + 1 + 0.0f)
							/ (numP - 1);
					textco[((k) * (numSides + 1) + j) * 4 + 2] = 0;
					textco[((k) * (numSides + 1) + j) * 4 + 3] = 1.0f;
				}
				k++;
			} else
				smoothness.push_back(0);
		}
	}

	unsigned int *faceIndex = (unsigned int *) malloc(
			sizeof(unsigned int) * (numP - 1) * (numSides + 1) * 6);
	unsigned int count = 0;
	k = 0;
	for (int i = 0; i < numP - 1; ++i) {
		for (int j = 0; j < numSides; ++j) {

			/*if (i != 0 || p[0] != 0.0)*/{
				faceIndex[count++] = k * (numSides + 1) + j;
				faceIndex[count++] = (k + 1) * (numSides + 1) + j + 1;
				faceIndex[count++] = (k + 1) * (numSides + 1) + j;
			}
			/*if (i != numP-2 || p[(numP-1)*2] != 0.0)*/{
				faceIndex[count++] = k * (numSides + 1) + j;
				faceIndex[count++] = k * (numSides + 1) + j + 1;
				faceIndex[count++] = (k + 1) * (numSides + 1) + j + 1;
			}

		}
		k++;
		k += smoothness[i];
	}

	int numVertices = numP * 2 * (numSides + 1);
	mMyMesh.numIndexes = count;

	glGenVertexArrays(1, &mMyMesh.vao);
	glBindVertexArray(mMyMesh.vao);

	GLuint buffers[4];
	glGenBuffers(4, buffers);
	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 4, vertex,
			GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0,
			0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 4, textco,
			GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 4, GL_FLOAT, 0, 0,
			0);

	//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 4, normal,
			GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
	glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(unsigned int) * mMyMesh.numIndexes, faceIndex,
			GL_STATIC_DRAW);

	// unbind the VAO
	glBindVertexArray(0);

	mMyMesh.type = GL_TRIANGLES;
	mMyMesh.mat.ambient[0] = 0.2f;
	mMyMesh.mat.ambient[1] = 0.2f;
	mMyMesh.mat.ambient[2] = 0.2f;
	mMyMesh.mat.ambient[3] = 1.0f;

	mMyMesh.mat.diffuse[0] = 0.8f;
	mMyMesh.mat.diffuse[1] = 0.8f;
	mMyMesh.mat.diffuse[2] = 0.8f;
	mMyMesh.mat.diffuse[3] = 1.0f;

	mMyMesh.mat.specular[0] = 0.8f;
	mMyMesh.mat.specular[1] = 0.8f;
	mMyMesh.mat.specular[2] = 0.8f;
	mMyMesh.mat.specular[3] = 1.0f;

	mMyMesh.mat.shininess = 100.0f;
}

void VSResSurfRevLib::render() {

	// send matrices to shaders
	mVSML->matricesToGL();

	// set material
	setMaterial(mMyMesh.mat);

	// bind texture
	for (unsigned int j = 0; j < VSResourceLib::MAX_TEXTURES; ++j) {
		if (mMyMesh.texUnits[j] != 0) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(mMyMesh.texTypes[j], mMyMesh.texUnits[j]);
		}
	}
	// bind VAO
	glBindVertexArray(mMyMesh.vao);
	glDrawElements(mMyMesh.type, mMyMesh.numIndexes, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (unsigned int j = 0; j < VSResourceLib::MAX_TEXTURES; ++j) {
		if (mMyMesh.texUnits[j] != 0) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(mMyMesh.texTypes[j], 0);
		}
	}

}

void VSResSurfRevLib::setColor(VSResourceLib::MaterialSemantics m,
		float *values) {

	if (m == TEX_COUNT)
		return;

	switch (m) {
	case SHININESS:
		mMyMesh.mat.shininess = *values;
		break;
	case DIFFUSE:
		memcpy(mMyMesh.mat.diffuse, values, sizeof(float) * 4);
		break;
	case AMBIENT:
		memcpy(mMyMesh.mat.ambient, values, sizeof(float) * 4);
		break;
	case SPECULAR:
		memcpy(mMyMesh.mat.specular, values, sizeof(float) * 4);
		break;
	case EMISSIVE:
		memcpy(mMyMesh.mat.emissive, values, sizeof(float) * 4);
		break;
	}
}

#ifdef _VSL_TEXTURE_WITH_DEVIL

void
VSResSurfRevLib::setTexture(unsigned int unit, unsigned int textureID, GLenum textureType) {

	mMyMesh.texUnits[unit] = textureID;
	mMyMesh.texTypes[unit] = textureType;
	mMyMesh.mat.texCount = 1;
}

void
VSResSurfRevLib::addTexture(unsigned int unit, std::string filename) {

	int textID = loadRGBATexture(filename, true);
	mMyMesh.texUnits[unit] = textID;
	mMyMesh.texTypes[unit] = GL_TEXTURE_2D;
	mMyMesh.mat.texCount = 1;
}

void
VSResSurfRevLib::addCubeMapTexture(unsigned int unit, std::string posX, std::string negX,
		std::string posY, std::string negY,
		std::string posZ, std::string negZ) {

	int textID = loadCubeMapTexture(posX, negX, posY, negY, posZ, negZ);
	mMyMesh.texUnits[unit] = textID;
	mMyMesh.texTypes[unit] = GL_TEXTURE_CUBE_MAP;
	mMyMesh.mat.texCount = 1;
}

#endif

int VSResSurfRevLib::revSmoothNormal2(float *p, float *nx, float *ny,
		float smoothCos, int beginEnd) {

	float v1x, v1y, v2x, v2y, x, y, norm;
	float auxX, auxY, angle;

	auxX = p[0] - p[2];
	auxY = p[1] - p[3];
	v1x = -auxY;
	v1y = auxX;
	norm = sqrt((v1x * v1x) + (v1y * v1y));
	v1x /= norm;
	v1y /= norm;

	auxX = p[2] - p[4];
	auxY = p[3] - p[5];
	v2x = -auxY;
	v2y = auxX;
	norm = sqrt((v2x * v2x) + (v2y * v2y));
	v2x /= norm;
	v2y /= norm;

	angle = v1x * v2x + v1y * v2y;

	if (angle > smoothCos) {
		x = v1x + v2x;
		y = v1y + v2y;
	} else if (beginEnd == 0) {
		x = v2x;
		y = v2y;
	} else {
		x = v1x;
		y = v1y;

	}

	norm = sqrt(x * x + y * y);

	assert(norm!=0);
	x /= norm;
	y /= norm;

	*nx = x;
	*ny = y;
	if (angle > smoothCos)
		return 1;
	else
		return 0;
}

float VSResSurfRevLib::computeTotalSegmentLength(float *p, int numP) {

	float l, aux;
	int i;

	l = 0;
	for (i = 0; i < numP - 1; i++) {

		aux = (p[(i + 1) * 2] - p[i * 2]) * (p[(i + 1) * 2] - p[i * 2])
				+ (p[(i + 1) * 2 + 1] - p[i * 2 + 1])
						* (p[(i + 1) * 2 + 1] - p[i * 2 + 1]);
		l += sqrt(aux);
	}
	return l;

}

float VSResSurfRevLib::computeSegmentLength(float *p) {

	float l, aux;

	aux = (p[2] - p[0]) * (p[2] - p[0]) + (p[3] - p[1]) * (p[3] - p[1]);
	l = sqrt(aux);

	return l;

}

float *
VSResSurfRevLib::circularProfile(float minAngle, float maxAngle, float radius,
		int divisions, float transX, float transY) {

	float *p = (float *) malloc(sizeof(float) * 2 * (divisions + 3));
	float step = (maxAngle - minAngle) / divisions;

	for (int i = 0, k = -1; i < divisions + 3; ++i, ++k) {

		p[i * 2] = radius * cos(minAngle + k * step) + transX;
		p[i * 2 + 1] = radius * sin(minAngle + k * step) + transY;
//		printf("%f %f\n", p[i*2], p[i * 2 + 1]);
	}

	return p;
}

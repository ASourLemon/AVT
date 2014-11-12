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

 
#ifndef __VSResSurfRevLib__
#define __VSResSurfRevLib__

#include <string>
#include <assert.h>

#include <GL/glew.h>

#include "vsResourceLib.h"

extern float vertices[6*4*4];
extern float normals[6*4*3];
extern float texCoords[6*4*2];
extern unsigned int faceIndex[36];
extern int verticeCount;
extern int faceCount;

class VSResSurfRevLib : public VSResourceLib{

public:

	VSResSurfRevLib();
	~VSResSurfRevLib();

	void create (float *p, int numP, int sides, int closed, float smoothCos);
	void createCube(float side);
	void createSphere(float radius, int divisions);
	void createTorus(float innerRadius, float outerRadius, int rings, int sides);
	void createCylinder(float height, float radius, int sides);
	void createRectangle(float height, float width);
	void createCone(float height, float baseRadius, int sides);
	void createPawn();

	virtual void clone(VSResourceLib *res);
	/** implementation of the superclass abstract method
	  * \param filename the model's filename
	*/
	virtual bool load(std::string filename);
	/// implementation of the superclass abstract method
	virtual void render();
	/// set a color component for all meshes
	void setColor(VSResourceLib::MaterialSemantics m, float *values);
	/// set a color component for a particular mesh
	void setColor(unsigned int mesh, VSResourceLib::MaterialSemantics m, float *values);

#ifdef _VSL_TEXTURE_WITH_DEVIL
	/// load and set a texture for the object
	virtual void addTexture(unsigned int unit, std::string filename);
	/// load and set a cubemap texture for a object
	virtual void addCubeMapTexture(unsigned int unit, 
									std::string posX, std::string negX, 
									std::string posY, std::string negY, 
									std::string posZ, std::string negZ);
	/// set an existing texture ID for a texture unit
	virtual void setTexture(unsigned int unit, unsigned int textureID,
							GLenum textureType = GL_TEXTURE_2D);
#endif
protected:

	// A model can be made of many meshes. Each is stored
	// in the following structure
	struct MyMesh{
		GLuint vao;
		GLuint texUnits[MAX_TEXTURES];
		GLuint texTypes[MAX_TEXTURES];
		GLuint uniformBlockIndex;
		float transform[16];
		int numIndexes;
		unsigned int type;
		struct Material mat;
	};

	/// the mesh collection
	struct MyMesh mMyMesh;
	
private:
	void computeVAO(int numP, float *p, float *points, int sides, float smoothCos);
	float *circularProfile(float minAngle, float maxAngle, float radius, int divisions, float transX= 0.0f, float transY = 0.0f);
	int revSmoothNormal2(float *p, float *nx, float *ny, float smoothCos, int beginEnd);
//	float *vertex,*normal,*textco,*points;
//	int numPoints,numSides,cap;
	float computeSegmentLength(float *p);
	float computeTotalSegmentLength(float *p, int numP);

};
#endif

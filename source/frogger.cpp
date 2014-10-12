///////////////////////////////////////////////////////////////////////
//
// 
// (c) 2014 by Jo�o Madeiras Pereira
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../include/game.h"
#include "../include/cube.h"
#include "../include/vsMathLib.h"
#include "../include/vsShaderLib.h"
#include "../include/vsResSurfRevLib.h"

#define CAPTION "Exercise 1"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

#define VERTEX_COORD_ATTRIB_ORIGINAL 0
#define NORMAL_ATTRIB_ORIGINAL 1
#define TEXTURE_COORD_ATTRIB_ORIGINAL 2

GLuint VaoId, VboId[4];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId, ProjectionID, ModelID, ViewID;

// Mouse Tracking Variables
int startX, startY, tracking = 0;
// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 10.0f;
// Camera Position
float camX = 0.0, camY = 15.0, camZ = 15.0;

VSMathLib* core;
VSResSurfRevLib mySurfRev;

VSShaderLib shader, shaderF;
domain::Game game;

bool oldVersion = false;


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// ERRORS
///////////////////////////////////////////////////////////////////////


bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if(isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SHADERS
///////////////////////////////////////////////////////////////////////


static char* readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "r");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	//memset(buf, size, sizeof(char));
	int n_read = fread(buf, 1, size, fp);

	buf[n_read] = '\0';
	fclose(fp);

	return buf;
}

void createShaderProgram()
{
	ProgramId = glCreateProgram();
	struct Shader {
		const char*  filename;
		GLenum       type;
		GLchar*      source;
	}  shaders[2] = {
		{ "shaders/oldvShader.glsl", GL_VERTEX_SHADER, NULL },
		{ "shaders/oldfShader.glsl", GL_FRAGMENT_SHADER, NULL }
	};


	for (int i = 0; i < 2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source == NULL) {
			std::cerr << "Failed to read " << s.filename << std::endl;
			exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
		glCompileShader(shader);

		GLint  compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cerr << s.filename << " failed to compile:" << std::endl;
			GLint  logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		delete[] s.source;

		glAttachShader(ProgramId, shader);
	}


	glBindAttribLocation(ProgramId, VERTEX_COORD_ATTRIB_ORIGINAL, "in_position");
	

	glLinkProgram(ProgramId);

	ProjectionID = glGetUniformLocation(ProgramId, "P");
	ViewID = glGetUniformLocation(ProgramId, "V");
	ModelID = glGetUniformLocation(ProgramId, "M");
	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// VAOs & VBOs
///////////////////////////////////////////////////////////////////////


void createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(4, VboId);

//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_COORD_ATTRIB_ORIGINAL);
	glVertexAttribPointer(VERTEX_COORD_ATTRIB_ORIGINAL, 4, GL_FLOAT, 0, 0, 0);

//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_ATTRIB_ORIGINAL);
	glVertexAttribPointer(NORMAL_ATTRIB_ORIGINAL, 3, GL_FLOAT, 0, 0, 0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_ORIGINAL);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_ORIGINAL, 2, GL_FLOAT, 0, 0, 0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);

// unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(VERTICES);
	//glDisableVertexAttribArray(COLORS);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glDisableVertexAttribArray(VERTEX_COORD_ATTRIB_ORIGINAL);
	glDisableVertexAttribArray(NORMAL_ATTRIB_ORIGINAL);
	glDisableVertexAttribArray(TEXTURE_COORD_ATTRIB_ORIGINAL);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(4, VboId);
	glDeleteVertexArrays(1, &VaoId);
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SCENE
///////////////////////////////////////////////////////////////////////


typedef float Matrix[16];

const Matrix M = {
	1.0f,  0.0f,  0.0f,  3.0f,
	0.0f,  1.0f,  0.0f,  3.0f,
	0.0f,  0.0f,  1.0f,  3.0f,
	0.0f,  0.0f,  0.0f,  1.0f
}; // Row Major (GLSL is Column Major)

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	core->loadIdentity(VSMathLib::VIEW);
	core->loadIdentity(VSMathLib::MODEL);

	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	core->lookAt(camX,camY,camZ , 0.0,0.0,0.0, 0,1,0);
	core->loadIdentity(VSMathLib::MODEL);

	float* proj_mat = core->get(core->PROJECTION);
	float* view_mat = core->get(core->VIEW);
	float* model_mat = core->get(core->MODEL);

	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, proj_mat);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, view_mat);
	glUniformMatrix4fv(ModelID, 1, GL_TRUE, model_mat);

	glDrawElements(GL_TRIANGLES, faceCount*3, GL_UNSIGNED_INT, (GLvoid*)0);

	core->loadMatrix(core->MODEL, (float*) &M);
	glUniformMatrix4fv(ModelID, 1, GL_TRUE, model_mat);
	glDrawElements(GL_TRIANGLES, faceCount*3, GL_UNSIGNED_INT, (GLvoid*)0);


	glUseProgram(0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

void newrenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	core->loadIdentity(VSMathLib::VIEW);
	core->loadIdentity(VSMathLib::MODEL);
	// set camera
	core->lookAt(camX, camY, camZ, 0,0,0, 0,1,0);

	/*
	// transform light to camera space and send it to GLSL
	float res[4];
	core->multMatrixPoint(VSMathLib::VIEW, lightDir, res);
	core->normalize(res);
	shader.setBlockUniform("Lights", "l_dir", res);

	core->multMatrixPoint(VSMathLib::VIEW, lightPos, res);
	shader.setBlockUniform("Lights", "l_pos", res);

	core->multMatrixPoint(VSMathLib::VIEW, spotDir, res);
	shader.setBlockUniform("Lights", "l_spotDir", res);*/

	// use our shader
	glUseProgram(shader.getProgramIndex());

	game.draw(core);

	//swap buffers
	glutSwapBuffers();
}


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// CALLBACKS
///////////////////////////////////////////////////////////////////////


void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(oldVersion){
		renderScene();
	}else{
		newrenderScene();
	}

}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	ratio = (1.0f * w) / h;
	core->loadIdentity(VSMathLib::PROJECTION);
	core->perspective(90.0f, ratio, 0.5f, 100.0f);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}

	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}

	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux *   						       sin(betaAux * 3.14f / 180.0f);

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}

void processKeys(unsigned char key, int xx, int yy)
{
	switch(key) {

		case 27:

			glutLeaveMainLoop();
			break;
		case 'c': printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
			break;
		case 'm': glEnable(GL_MULTISAMPLE); break;
		case 'n': glDisable(GL_MULTISAMPLE); break;
		case 'a':{
			camX++;
			break;
		}
		case 'd':{
			camX--;
			break;
		}
	}

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}


///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SETUP
///////////////////////////////////////////////////////////////////////


void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ;
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void setupCore(){

	core = VSMathLib::getInstance();
	core->setUniformBlockName("Matrices");
	core->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "m_pvm");
	core->setUniformName(VSMathLib::NORMAL, "m_normal");
	core->setUniformName(VSMathLib::VIEW_MODEL, "m_viewModel");

}

GLuint setupShaders() {

	// Shader for fonts
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/vShader.glsl");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/fShader.glsl");

	// set semantics for the shader variables
	shaderF.setProgramOutput(0,"outputF");
	shaderF.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shaderF.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	shaderF.prepareProgram();

	// add sampler uniforms
	shaderF.setUniform("texUnit", 0);

	printf("InfoLog for Font Shader\n%s\n\n", shaderF.getAllInfoLogs().c_str());

	// Shader for models
	shader.init();


#define _DIF			0
#define _DIF_AMB		1
#define _DIF_AMB_SPEC	2
#define _PER_PIXEL		3
#define _POINT			4
#define _SPOT			5

#define _LIGHT 5

#if (_LIGHT == _DIF)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/dirdif.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/dirdif.frag");
#elif (_LIGHT == _DIF_AMB)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/dirdifamb.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/dirdifamb.frag");
#elif (_LIGHT == _DIF_AMB_SPEC)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/dirdifambspec.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/dirdifambspec.frag");
#elif (_LIGHT == _PER_PIXEL)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pixeldirdifambspec.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pixeldirdifambspec.frag");
#elif (_LIGHT == _POINT)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");
#else
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/vShader.glsl");	/*FIXME: oh dear, fix me when light added!!*/
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/fShader.glsl");
#endif

	// set semantics for the shader variables
	shader.setProgramOutput(0,"outputF");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	shader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	shader.prepareProgram();

	shader.setUniform("texUnit", 0);
	float f3 = 0.90f;
	shader.setBlockUniform("Lights", "l_spotCutOff", &f3);


	printf("InfoLog for Model Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	return(shader.isProgramValid());
}

void setupSurfRev(){

	game.init();
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCore();

	if(oldVersion){
		createShaderProgram();
		createBufferObjects();
	}else {

		if(!setupShaders()){

		}
		setupSurfRev();
	}

	setupCallbacks();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////

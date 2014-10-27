///////////////////////////////////////////////////////////////////////
//
// 
// (c) 2014 by Jo���o Madeiras Pereira
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../include/game.h"
#include "../include/drawable.h"
#include "../include/cube.h"
#include "../include/vsMathLib.h"
#include "../include/vsShaderLib.h"
#include "../include/vsResSurfRevLib.h"
#include "../include/lightManager.h"
#include "../include/TGA.h"

#define CAPTION "Frogger 3D"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;



#define FPS 60
#define VERTEX_COORD_ATTRIB_ORIGINAL 0
#define NORMAL_ATTRIB_ORIGINAL 1
#define TEXTURE_COORD_ATTRIB_ORIGINAL 2

#define CAM_ORTHO 0
#define CAM_PRESP 1
#define CAM_FROG 2

GLuint VaoId, VboId[4];
GLuint VertexShaderId, FragmentShaderId, ProgramId, ColorId;
GLint UniformId, ProjectionID, ModelID, ViewID;
GLint tex_loc;
GLuint TextureArray[1];


// Mouse Tracking Variables
int startX, startY, tracking = 0;
// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 10.0f;
// Camera Position
float camX = 0.0, camY = 0.0, camZ = 2.0;

VSMathLib* core;
VSResSurfRevLib mySurfRev;

VSShaderLib shader, shaderF;
domain::Game game;

int CAM_TYPE = 0;
void processKeys();
bool* keyStates;
int nTimer = 0;

LightManager lightManager;

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

void checkOpenGLError(std::string error) {
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SCENE
///////////////////////////////////////////////////////////////////////

void newrenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	core->loadIdentity(VSMathLib::VIEW);
	core->loadIdentity(VSMathLib::MODEL);
	// set camera

	if(CAM_TYPE == CAM_FROG){

		float fx = game.getFrogX();
		float fy = game.getFrogY();
		float fz = game.getFrogZ();
		
		printf("fx:%f, fy%f, fz%f\n", fx, fy, fz); 

		if (tracking == 1){
			core->lookAt(fx, fy + 3.5, fz - 2.5,  fx + camX , (fy + camY * -0.5), (fz + camZ * 0.5), 0, 1, 0);

		}
		else {
			core->lookAt(fx + camX, fy + camY*-0.5 + 2.5, fz - camZ, fx, fy, fz, 0, 1, 0);
		}

	} else {

		core->lookAt(10, 10, 15.0, 10, 0, 15.0, 0, 0, 1);
	}


	float l0_dir[4] = {0.0f, 1.0f, 0.0f, 0.0f};
	float res[4];
	core->multMatrixPoint(VSMathLib::VIEW, l0_dir, res);
	shader.setBlockUniform("Lights", "l_dir", res);
	
	//lightManager.drawLight(core);
	// use our shader
	glUseProgram(shader.getProgramIndex());

	game.draw(core);

	//FIXME: just a test
	//Associar os Texture Units aos Objects Texture
	//stone.tga loaded in TU0; checker.tga loaded in TU1;  lightwood.tga loaded in TU2

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

	//Indicar aos tres samplers do GLSL quais os Texture Units a serem usados
	glUniform1i(tex_loc, 0);

	//swap buffers
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// CALLBACKS
///////////////////////////////////////////////////////////////////////

void display() {
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	newrenderScene();

}

void idle() {
	//printf("Doing nothing!\n");
	//glutPostRedisplay();
}

void reshape(int w, int h) {
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	ratio = (1.0f * w) / h;
	core->loadIdentity(VSMathLib::PROJECTION);

	if(CAM_TYPE == CAM_ORTHO){
		if(ratio > 1){
			core->ortho(-8.0f*ratio, 8.0f*ratio, -16.0f, 18.0f, 1.6f, 12.0f);

		}else {
			core->ortho(-8.0f, 8.0f, -16.0f/ratio, 18.0f/ratio, 1.6f, 12.0f);

		}

	}else{

		core->perspective(125.0f, ratio, 0.6f, 40.0f);
	}
	WinX = w;
	WinY = h;
}

void timer(int value) {
	if(nTimer == FPS){
		std::ostringstream oss;
		oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
		std::string s = oss.str();
		glutSetWindow(WindowHandle);
		glutSetWindowTitle(s.c_str());
		FrameCount = 0;
		nTimer = 0;
	}
	nTimer++;
	game.tick();
	processKeys();

	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0);
}

void processMouseButtons(int button, int state, int xx, int yy) {
	// start tracking the mouse
	if (state == GLUT_DOWN) {
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
		} else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy) {
	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX = -xx + startX;
	deltaY = yy - startY;

	// left mouse button: move camera
	//if (tracking == 1) {

	alphaAux = alpha + deltaX;
	betaAux = beta + deltaY;

	if (betaAux > 85.0f)
		betaAux = 85.0f;
	else if (betaAux < -85.0f)
		betaAux = -85.0f;
	rAux = r;
	/*}

	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}*/

	camX = rAux * sin(alphaAux * 3.14f / 180.0f)
	* cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f)
	* cos(betaAux * 3.14f / 180.0f);
	camY = rAux * sin(betaAux * 3.14f / 180.0f);

	printf("camX:%f , camY:%f, camZ:%f\n", camX, camY,camZ);
}

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
}

void processKeys(){

	if(keyStates['c']){
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);

	}if(keyStates['1']){
		CAM_TYPE = CAM_ORTHO;
		reshape(WinX, WinY);
	}

	if(keyStates['2']){
		CAM_TYPE = CAM_PRESP;
		reshape(WinX, WinY);
	}

	if(keyStates['3']){
		CAM_TYPE = CAM_FROG;
		reshape(WinX, WinY);
	}

	if(keyStates['m']){
		glEnable(GL_MULTISAMPLE);
	}

	if(keyStates['n']){
		glDisable(GL_MULTISAMPLE);
	}
	if(keyStates['l']){
		if(lightManager.isOn()){
			lightManager.lightsOff();
		}else{
			lightManager.lightsOn();
		}
	}
	if(keyStates['q']){
		game.move_frog(0);
	}else{
		game.setFrogT1(glutGet(GLUT_ELAPSED_TIME));
	}

	if(keyStates['a']){
		game.move_frog(1);
	}else{
		game.setFrogT2(glutGet(GLUT_ELAPSED_TIME));
	}

	if(keyStates['o']){
		game.move_frog(2);
	}else{
		game.setFrogT3(glutGet(GLUT_ELAPSED_TIME));
	}

	if(keyStates['p']){
		game.move_frog(3);
	}else{
		game.setFrogT4(glutGet(GLUT_ELAPSED_TIME));
	}
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SETUP
///////////////////////////////////////////////////////////////////////

void setupCallbacks() {
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);


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
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

}

void setupGLUT(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window."
				<< std::endl;
		exit(EXIT_FAILURE);
	}
}

void setupCore() {

	core = VSMathLib::getInstance();
	core->setUniformBlockName("Matrices");
	core->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "m_pvm");
	core->setUniformName(VSMathLib::NORMAL, "m_normal");
	core->setUniformName(VSMathLib::VIEW_MODEL, "m_viewModel");
	//Nao sabia onde por isto, a ideia �� isto ser feito apenas uma vez
	keyStates = new bool[256];
	for(int i=0; i<256; i++){
		keyStates[i] = false;
	}

}

GLuint setupShaders() {

	// Shader for fonts
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/color.vert");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/color.frag");

	// set semantics for the shader variables
	shaderF.setProgramOutput(0, "outputF");
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
#define _POINT			4	//lampada
#define _SPOT			5	//cone

#define _LIGHT 2

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
	shader.loadShader(VSShaderLib::VERTEX_SHADER,
			"shaders/pixeldirdifambspec.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER,
			"shaders/pixeldirdifambspec.frag");
#elif (_LIGHT == _POINT)
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");
#else
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/spotlight.vert"); /*FIXME: oh dear, fix me when light added!!*/
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/spotlight.frag");
#endif

	// set semantics for the shader variables
	shader.setProgramOutput(0, "outputF");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	shader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	//FIXME: hardcode
	tex_loc = glGetUniformLocation(shader.getProgramIndex(), "texmap");
	
	shader.prepareProgram();

	shader.setUniform("texUnit", 0);

	printf("InfoLog for Model Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	return (shader.isProgramValid());
}

void setupSurfRev() {

	game.init();
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void setupLight(){
	lightManager.init(&shader);
	float l0_cut = 0.3f;
	float l0_pos[4] = {15.0f, 2.0f, 10.0f, 1.0f};	//WORLD COORDINATES!!
	float l0_dir[4] = {0.0f, 0.0f, -1.0f, 0.0f};
	lightManager.addLight(l0_pos, l0_dir, l0_cut);
	
	float l1_cut = 0.3f;
	float l1_pos[4] = { 5.0f, 2.0f, 10.0f, 1.0f };
	float l1_dir[4] = { 0.0f, 0.0f, -1.0f, 0.0f };
	//lightManager.addLight(l1_pos, l1_dir, l1_cut);
	
	float l2_cut = 0.3f;
	float l2_pos[4] = { 6.0f, 2.0f, 30.0f, 1.0f };
	float l2_dir[4] = { 0.0f, 0.0f, -1.0f, 0.0f };
	//lightManager.addLight(l2_pos, l2_dir, l2_cut);
	
	
	int n_lights = lightManager.getNumLights();
	shader.setUniform("n_lights", &n_lights);
}

void init(int argc, char* argv[]) {
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCore();

	if (!setupShaders()) {

	}
	setupLight();
	setupSurfRev();
	setupCallbacks();

	glGenTextures(1, TextureArray);
	TGA_Texture(TextureArray, "lightwood.tga", 0);
}

int main(int argc, char* argv[]) {
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////

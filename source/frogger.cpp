///////////////////////////////////////////////////////////////////////
//
// 
// (c) 2014 by João, Miguel and Nelson
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iomanip>

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
#include "../include/FontMapper.h"
#include "../include/Flare.h"

#define CAPTION "Frogger 3D"

int WinX = 640, WinY = 480;
int WindowHandle = 0;
float FrameCount = 0;

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
GLuint TextureArray[10];
GLuint FlareTextureArray[4];

// Mouse Tracking Variables
int startX, startY, tracking = 0;
// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 5.0f;
// Camera Position
float camX = 0.0, camY = 0.0, camZ = 2.0;

using namespace domain;

VSMathLib* core;
VSResSurfRevLib mySurfRev;
FontMapper fontM;
Flare flare;

VSShaderLib shader, shaderF;
domain::Game *game = domain::Game::getInstance();

int CAM_TYPE = 0;
void processKeys();
bool* keyStates;
int nTimer = 0;

LightManager lightManager;
bool l_on;
bool lampOn;
bool drawFlare;
bool fogOn;

int mx = 0, my = 0;

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

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int lifes = game->getFrogLifes();
	
	////////////////////////////////////////////////////////////
	///////////////Draw models/////////////////////////////////
	//////////////////////////////////////////////////////////
	if(lifes > 0){
		core->loadIdentity(VSMathLib::VIEW);
		core->loadIdentity(VSMathLib::MODEL);
		
		// set camera
		if (CAM_TYPE == CAM_FROG) {
			if (tracking == 1) {
				// Move camera around
				float fx = game->getFrogX();
				float fy = game->getFrogY();
				float fz = game->getFrogZ();
				core->lookAt(fx + camX, fy + camY, fz + camZ, fx, fy, fz, 0, 1, 0);
			} else {
				game->loadCamera(3);
			}
		}
		else {
			game->loadCamera(2);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
		glUseProgram(shader.getProgramIndex());
		
		int lampbool = glGetUniformLocation(shader.getProgramIndex(), "lampOn");
		glUniform1i(lampbool, lampOn);
		
		int daybool = glGetUniformLocation(shader.getProgramIndex(), "isDay");
		glUniform1i(daybool, l_on);

		float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		shader.setUniform("time", &time);
		
		bool tex_moving = false;
		int pos_loc = glGetUniformLocation(shader.getProgramIndex(), "tex_moving");
		glUniform1i(pos_loc, tex_moving);
		
		int fog_loc = glGetUniformLocation(shader.getProgramIndex(), "fogOn");
		glUniform1i(fog_loc, fogOn);

		lightManager.drawLight(core);
		game->draw(core, &shader);
	}

	////////////////////////////////////////////////////////////
	///////////////Draw flares/////////////////////////////////
	//////////////////////////////////////////////////////////

	if(drawFlare && lampOn && !l_on){
		glUseProgram(shaderF.getProgramIndex());
		flare.draw(core, &shaderF);
	}
	
	////////////////////////////////////////////////////////////
	///////////////Draw fonts//////////////////////////////////
	//////////////////////////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[6]);
	glUseProgram(shaderF.getProgramIndex());
	if(lifes > 0){
		int points = game->getFrogPoints();
		char hud[30];
		char buf[2];
		buf[1] = '\0';
		
		strcpy(hud, "Lifes:");
		sprintf(buf, "%d\0", lifes);
		strcat(hud, buf);
		strcat(hud, "   ");
		strcat(hud, "Points:");
		sprintf(buf, "%d\0", points);
		strcat(hud, buf);
		fontM.DrawString(&shaderF, 0.0f, 0.0f, hud, false);	
		
	}else {
		
		fontM.DrawString(&shaderF, WinX/2, WinY/2, "GAME OVER!", true);	
	}

	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// CALLBACKS
///////////////////////////////////////////////////////////////////////

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int start = glutGet(GLUT_ELAPSED_TIME);
	renderScene();
	float frameTime = ((float) (glutGet(GLUT_ELAPSED_TIME) - start) / 1000);
	FrameCount = ((float) 1 / frameTime);
	//printf("FPS : %.1f, frameTime: %.5f\n", FrameCount, frameTime);
}

void reshape(int w, int h) {
	float ratio;

	// Prevents a divide by zero, when window is too short
	if (h == 0)
		h = 1;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	ratio = (1.0f * w) / h;
	core->loadIdentity(VSMathLib::PROJECTION);

	if (CAM_TYPE == CAM_ORTHO) {
		if (ratio > 1) {
			core->ortho(-8.0f * ratio, 8.0f * ratio, -16.0f, 18.0f, 1.6f,
					12.0f);

		} else {
			core->ortho(-8.0f, 8.0f, -16.0f / ratio, 18.0f / ratio, 1.6f,
					12.0f);

		}

	} else {
		core->perspective(125.0f, ratio, 0.1f, 40.0f);
	}
	WinX = w;
	WinY = h;
}

void timer(int value) {

	std::ostringstream oss;
	int lifes = game->getFrogLifes();
	int points = game->getFrogPoints();
	if (lifes) {
		oss << CAPTION << ": " << std::setprecision(4) << FrameCount << " FPS @ (" << WinX << "x"
				<< WinY << ")" << "Lifes:" << lifes << "Points:" << points;
	} else {
		drawFlare = false;
		oss << CAPTION << ": G A M E   O V E R!!";
	}

	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());

	//std::cout << FrameCount << std::endl;
	game->tick(core);

	processKeys();

	glutPostRedisplay();
	
	
	glutTimerFunc(1000 / FPS, timer, 0);
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
			//r += (yy - startY) * 0.01f;
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
	mx = xx;
	my = yy;
	//printf("mX: %d, mY: %d \n", xx, yy);

	deltaX = -xx + startX;
	deltaY = yy - startY;

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

	camX = rAux * sin(alphaAux * 3.14f / 180.0f)
			* cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f)
			* cos(betaAux * 3.14f / 180.0f);
	camY = rAux * sin(betaAux * 3.14f / 180.0f);
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
}

void processKeys() {

	if (keyStates['0']) {
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);

	}
	if (keyStates['1']) {
		CAM_TYPE = CAM_ORTHO;
		reshape(WinX, WinY);
	}

	if (keyStates['2']) {
		CAM_TYPE = CAM_PRESP;
		reshape(WinX, WinY);
	}

	if (keyStates['3']) {
		CAM_TYPE = CAM_FROG;
		reshape(WinX, WinY);
	}

	if (keyStates['m']) {
		glEnable(GL_MULTISAMPLE);
	}

	if (keyStates['l']) {
		glDisable(GL_MULTISAMPLE);
	}
	if (keyStates['n']) {
		if (l_on) {
			printf("Lights off\n");
			l_on = false;
		} else {
			printf("Lights on\n");
			l_on = true;
		}
		keyStates['n'] = false;
	}

	if (keyStates['c']) {
		if (lampOn) {
			lampOn = false;
			printf("Lamps off\n");
		} else {
			printf("Lamps on\n");
			lampOn = true;
		}
		keyStates['c'] = false;
	}

	if (keyStates['r']) {
		if (!game->getFrogLifes()) {
			game->setFrogLifes(3);
			game->setFrogPoints(0);
			drawFlare = true;
		}
		keyStates['r'] = false;
	}
	if (keyStates['s']) {
		r += 0.5f;
	}
	if (keyStates['w']) {
		r -= 0.5f;
	}
	if (keyStates['a']) {
		game->move_frog(1);
	}
	if (keyStates['q']) {
		game->move_frog(0);
	}
	if (keyStates['o']) {
		game->move_frog(2);
	}
	if (keyStates['p']) {
		game->move_frog(3);
	}
	if (keyStates['f']){
		if (fogOn) {
			fogOn = false;
			printf("Fog off\n");
		} else {
			printf("Fog on\n");
			fogOn = true;
		}
		keyStates['f'] = false;
		
	}
	game->setFrogT(glutGet(GLUT_ELAPSED_TIME));
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// SETUP
///////////////////////////////////////////////////////////////////////

void setupCallbacks() {
	glutDisplayFunc(display);
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
	// GLenum err_code = glGetError();
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
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
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
	core->setUniformName(VSMathLib::MODEL, "m_model");
	keyStates = new bool[256];
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}

}

GLuint setupShaders() {

	///////////////////////////////////////////// 
	//////////////Shader for fonts//////////////
	/////////////////////////////////////////////
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/color.vert");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/color.frag");

	// set semantics for the shader variables
	shaderF.setProgramOutput(0, "outputF");
	shaderF.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shaderF.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	shaderF.prepareProgram();

	// add sampler uniforms
	//shaderF.setUniform("texUnit", 0);
	fontM.Init();

	printf("InfoLog for Font Shader\n%s\n\n", shaderF.getAllInfoLogs().c_str());

	///////////////////////////////////////////// 
	//////////////Shader for models//////////////
	/////////////////////////////////////////////
	shader.init();
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/oldvShader.glsl");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/oldfShader.glsl");

	// set semantics for the shader variables
	shader.setProgramOutput(0, "colorOut");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	shader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	shader.prepareProgram();

	shader.setUniform("texUnit", 0);

	printf("InfoLog for Model Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	return (shader.isProgramValid());
}

void setupSurfRev() {

	game->init();
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void setupLight() {
	lightManager.init(&shader, game->getFrog());

	//Point lights
	float p0_pos[4] = { 15.0f, 3.0f, 15.0f, 1.0f };
	lightManager.addLight(p0_pos);
	float p1_pos[4] = { 5.0f, 3.0f, 15.0f, 1.0f };
	lightManager.addLight(p1_pos);

	float p2_pos[4] = { 15.0f, 3.0f, 1.0f, 1.0f };
	lightManager.addLight(p2_pos);
	float p3_pos[4] = { 5.0f, 3.0f, 1.0f, 1.0f };
	lightManager.addLight(p3_pos);

	float p4_pos[4] = { 15.0f, 3.0f, 28.0f, 1.0f };
	lightManager.addLight(p4_pos);
	float p5_pos[4] = { 5.0f, 3.0f, 28.0f, 1.0f };
	lightManager.addLight(p5_pos);

	//Dir light
	float l1_dir[4] = { 1.0f, 1.0f, -1.0f, 0.0f };
	lightManager.addLight(l1_dir);

	//Mining light
	float l2_cut = 0.2f;
	float l2_dir[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	lightManager.addLight(l2_dir, l2_cut);


	//add lights to the flare system
	flare.addLight(p0_pos);
	flare.addLight(p1_pos);
	flare.addLight(p2_pos);
	flare.addLight(p3_pos);
	flare.addLight(p4_pos);
	flare.addLight(p5_pos);
	
	int n_lights = lightManager.getNumLights();
	shader.setUniform("n_lights", &n_lights);
	lightManager.lightsOn();
}

void setupFlare(){
	flare.addFlareElement(0, 2.0f, 5.0f, 0.5f, 0.1f);
	flare.addFlareElement(1, 2.0f, 5.0f, 0.5f, 0.2f);
	flare.addFlareElement(2, 2.0f, 5.0f, 0.5f, 0.8f);
	flare.addFlareElement(3, 2.0f, 5.0f, 0.5f, 0.9f);
	drawFlare = true;
	
}

void init(int argc, char* argv[]) {
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	setupCore();

	if (!setupShaders()) {
		exit(1);
	}
	setupSurfRev();
	setupCallbacks();
	setupFlare();
	setupLight();
	l_on = false;
	glGenTextures(9, TextureArray);
	TGA_Texture(TextureArray, "textures/lightwood.tga", 0);
	TGA_Texture(TextureArray, "textures/road.tga", 1);
	TGA_Texture(TextureArray, "textures/water.tga", 2);
	TGA_Texture(TextureArray, "textures/grass.tga", 3);
	TGA_Texture(TextureArray, "textures/tree.tga", 4);
	TGA_Texture(TextureArray, "textures/eye.tga", 5);
	TGA_Texture(TextureArray, "textures/font1.tga", 6);
	TGA_Texture(TextureArray, "textures/tallgrass.tga", 7);
	TGA_Texture(TextureArray, "textures/stone.tga", 8);
	TGA_Texture(TextureArray, "textures/smoke.tga", 9);
	
	glGenTextures(4, FlareTextureArray);
	TGA_Texture(FlareTextureArray, "textures/Flare1.tga", 0);
	TGA_Texture(FlareTextureArray, "textures/Flare2.tga", 1);
	TGA_Texture(FlareTextureArray, "textures/Flare3.tga", 2);
	TGA_Texture(FlareTextureArray, "textures/Flare4.tga", 3);
	
	fogOn = true;
}

int main(int argc, char* argv[]) {
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////

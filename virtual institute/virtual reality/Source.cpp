
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>					
#include <glut.h>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include <AR/gsub.h>
#include <math.h>
#include "Header.h"
#include "RGBpixmap.h"
#include "ParticleSystem.h"
#include"objLoader.h"
#include"video.h"
#include"voice.h"
#include"space.h"
#include"main.h"
#define SPACEBAR 0x08
#pragma comment(lib,"fmod.lib")

void drawstring(int x, int y, int z, const char *s);
bool pause = true;
int cw, che;
int window2 = 0, window = 0;
FSOUND_STREAM * g_mp3_stream1, *g_mp3_stream2, *g_mp3_stream3, *g_mp3_stream4, *g_mp3_stream5, *g_mp3_stream6, *g_mp3_stream7, *g_mp3_stream8, *g_mp3_stream9,
*g_mp3_stream10,
*g_mp3_stream11,
*g_mp3_stream12,
*g_mp3_stream13,
*g_mp3_stream14,
*g_mp3_stream15,
*g_mp3_stream16;

GLdouble p[16];	
GLdouble m[16];	


static int SetupGraphicsFull(int dispWidth, int dispHeight, int dispDepth, int dispRefresh);
static int SetupGraphicsWin(const char *title, int dispWidth, int dispHeight);

void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char *string);

#define VIEW_SCALEFACTOR		0.025		
#define VIEW_DISTANCE_MIN		0.1			
#define VIEW_DISTANCE_MAX		100.0		
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysTranspired = 0.00;
GLfloat EarthDayIncrement = 0.001;



// Character data structure
typedef struct {
	int model;
	GLfloat rot;
	GLfloat x;
	GLfloat y;
	GLfloat z;
	int pattId;
	int patt_found;
	double trans[3][4];
} CHARACTER_DATA;


#define NUM_MODEL 7


// TRUE: window mode / FALSE: full screen mode
static const int gWindowed = TRUE;

//Setting // full screen mode
static const int gFullWidth = 800; // screen resolution
static const int gFullHeight = 700; // screen resolution
static const int gFullDepth = 32; // number of bits
static const int gFullRefresh = 0; // refresh rate. The default value is 0.

// The real world / virtual world of the scale factor
static const double gViewScaleFactor = 1.0;

// Range of visibility (draw an object that is in the range of up to Min ~ Max)
static const double gViewDistanceMin = 0.1;
static const double gViewDistanceMax = 10000.0;

static char * gCparamName = "Data/camera_para.dat"; // camera parameter file
static char * gVconf = "Data/WDM_camera_flipV.xml"; // video device configuration file
//static char * gModelName[2] = { "Data / sacchi.mqo", "Data / domain.mqo" }; // model file
static char * gPattName[7] = {"data/new1", "Data/new2", "Data/new3", "Data/new4","Data/new5","Data/new6","Data/new7" }; // pattern files




static ARUint8 * gARTImage = NULL; // pointer to the camera image
static int gARTThreshhold = 100; // 2-valued threshold

static double gPatt_width = 80.0; // pattern size (mm units)
static double gPatt_centre[7] = { 0.0, 0.0 }; // center position of the pattern (mm units)

static ARParam gARTCparam; // camera parameters
static ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL; // drawing system configuration information

// Character of data
static CHARACTER_DATA gCharacter[8];

void SetLight(GLenum light);
void drawEarthAndMoon();
void drawEarthAndMoon1();
void drawSun();
void drawSaturnRing();
void drawSaturnRing1();
void drawAllPlanets();
void drawOne();
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha);
void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
void drawParticle(Particle currParticle);
void drawAllParticles();
void SetLights();
void UpdateLight();
int play(char *filename);
void drawOnePlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
void drawsat();
void MakeAllImages();
GLfloat ViewerDistance = INITIAL_VIEWER_DISTANCE;
GLfloat viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
GLfloat viewerZenith = INITIAL_VIEWER_ZENITH;
GLint currWindowSize[2] = { 750, 750 / ASPECT_RATIO };
GLint currViewportSize[2] = { 750, 750 / ASPECT_RATIO };

void TimerFunction(int value);
GLuint ParticleTextureName = -1;
GLuint EarthTextureName = 3;
GLuint MoonTextureName = 4;
GLuint SunTextureName = 0;
GLuint MercuryTextureName = 1;
GLuint VenusTextureName = 2;
GLuint MarsTextureName = 5;
GLuint JupiterTextureName = 6;
GLuint SaturnTextureName = 7;
GLuint UranusTextureName = 8;
GLuint NeptuneTextureName = 9;
GLuint PlutoTextureName = 10;
GLuint RingTextureName = 11;
ParticleSystem particles;
int sound(int argc, char **argv);
bool particleFlag = true;
bool blendFlag = true;
int guss,guss1;
int next1=0;
float t;
bool skyflag = true;
bool wire= true;
float xx=15, yy=15, z=15;
static void DrawCube(void)
{
	if (guss == 99){

	}
	else if (gCharacter[0].patt_found){
	

		glPushMatrix();
		//Applying // coordinate transformation matrix
		arglCameraViewRH(gCharacter[0].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();
		glScalef(7.8, 4.8, 4.8);

		//glTranslated(3, 0, -30);
		//glRotated(90, 1, 0, 0);
		//sky();
		//glTranslated(-3, 0, 20);
		//glScalef(xx, yy, z);
		//drawElephant2();
		if (wire){
			OnDraw();
		}
else
		OnDraw1();
		glPopMatrix();

		glPopMatrix();
		if (skyflag){
			
			
		}
		

	//FSOUND_Stream_Play(0, g_mp3_stream1);
		//PlaySound(data1, NULL, SND_ASYNC | SND_NOSTOP );*/
	}
	else if (gCharacter[4].patt_found){


		glPushMatrix();
		//Applying // coordinate transformation matrix
		arglCameraViewRH(gCharacter[4].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();
		
		//sky();
		glTranslated(-3, 0, 20);
	    glScalef(xx, yy, z);
		//drawElephant2();
	

		FSOUND_Stream_Play(0, g_mp3_stream1);
		//PlaySound(data1, NULL, SND_ASYNC | SND_NOSTOP );*/
	}
	
	else if(gCharacter[1].patt_found){

		glPushMatrix();
		
		arglCameraViewRH(gCharacter[1].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);
		glEnable(GL_LIGHTING);
		//gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
		gluLookAt(LOOK_AT_POSITION[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth),
			LOOK_AT_POSITION[1] + ViewerDistance * cos(viewerZenith),
			LOOK_AT_POSITION[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
			LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
			0.0, 1.0, 0.20);
		glScalef(xx, yy, z);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
		glEnable(GL_NORMALIZE);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		FSOUND_Stream_Play(0, g_mp3_stream2);
		
	
		glRotated(90, 1, 0, 0);
		glScaled(2, 2, 2);
		UpdateLight();
		drawEarthAndMoon();
	
		
		
		drawAllPlanets();
		drawSaturnRing();
		drawSun();
		


		if (blendFlag){ 
			glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_COLOR, GL_ONE);
		}

		if (particleFlag)
		drawAllParticles();
		
		



		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		
		//drawElephant();
	
		
	
	
		//glTranslated(0, 0, -2);


		glPopMatrix();
		
		glPopMatrix();
		//OnDraw2();
	
	}
	else if (gCharacter[3].patt_found)
	{
		glPushMatrix();
	
		arglCameraViewRH(gCharacter[3].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);
		glEnable(GL_LIGHTING);
		//gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
		gluLookAt(LOOK_AT_POSITION[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth),
			LOOK_AT_POSITION[1] + ViewerDistance * cos(viewerZenith),
			LOOK_AT_POSITION[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
			LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
			0.0, 1.0, 0.020);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glEnable(GL_NORMALIZE);
		glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTranslated(0, 0, 0);
		glScalef(xx, yy, z);
		UpdateLight();
		glRotated(90, 1, 0, 0);
		drawOne();







		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		guss1 = 1;
		glPopMatrix();
		glPopMatrix();
	}
	/* if (gCharacter[4].patt_found){

		glPushMatrix();
	
		arglCameraViewRH(gCharacter[4].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();


		glScaled(xx, yy, z);
		glColor3d(1, 1, 1);
		glBegin(GL_QUADS);

		glVertex2f(-3, 3);


		glVertex2f(-3, -3);


		glVertex2f(3, -3);


		glVertex2f(3, 3);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0, 2);
		glScaled(25, 25, 25);
		glBegin(GL_TRIANGLES);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glVertex3f(-1.0f, -1.0f, 0.0f);

		glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		glPopMatrix();
		glPopMatrix();
		//printf("found");
	}
	 if (gCharacter[5].patt_found){

		glPushMatrix();
	
		arglCameraViewRH(gCharacter[5].trans, m, gViewScaleFactor);
		glLoadMatrixd(m);

		glPushMatrix();


		glScaled(xx, yy, z);
		glColor3d(1, 1, 1);
		glBegin(GL_QUADS);

		glVertex2f(-3, 3);


		glVertex2f(-3, -3);


		glVertex2f(3, -3);


		glVertex2f(3, 3);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0, 2);
		glScaled(25, 25, 25);
		glBegin(GL_TRIANGLES);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glVertex3f(-1.0f, -1.0f, 0.0f);

		glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		glPopMatrix();
		glPopMatrix();
		//printf("found");
	
	}*/else
	 if (gCharacter[5].patt_found){
		 glPushMatrix();

		 arglCameraViewRH(gCharacter[6].trans, m, gViewScaleFactor);
		 glLoadMatrixd(m);

		 glPushMatrix();
		 glScalef(13, 13, 13);
		 glColor3f(1, 1, 1);
		 glTranslated(-10, 0, 0);
		 cube();
		 FSOUND_Stream_Play(0, g_mp3_stream16);
		 glPopMatrix();

		 glPopMatrix();
	 }
		/* if (gCharacter[7].patt_found){
			 glPushMatrix();

			 arglCameraViewRH(gCharacter[7].trans, m, gViewScaleFactor);
			 glLoadMatrixd(m);

			 glPushMatrix();


			 glScaled(xx, yy, z);
			 glColor3d(1, 1, 1);
			 glBegin(GL_QUADS);

			 glVertex2f(-3, 3);


			 glVertex2f(-3, -3);


			 glVertex2f(3, -3);


			 glVertex2f(3, 3);
			 glEnd();
			 glPopMatrix();
			 if (pause){
				 glPushMatrix();
				 glTranslated(0, 0, 2);
				 glScaled(25, 25, 25);
				 glBegin(GL_TRIANGLES);

				 glColor3f(0.0f, 0.0f, 0.0f);
				 glVertex3f(0.0f, 1.0f, 0.0f);

				 glVertex3f(-1.0f, -1.0f, 0.0f);

				 glVertex3f(1.0f, -1.0f, 0.0f);
				 glEnd();
				 glPopMatrix();
			 }
			 else
			 if (!pause){
				 glPushMatrix();
				 glScaled(8, 8, 8);
				 glTranslated(0, -1
					 , 3);
				 glRotated(90, 0, 0, 1);
				 glColor3d(0, 1, 1);
				 glBegin(GL_QUADS);

				 glVertex2f(-0.6, 3);


				 glVertex2f(-0.6, -3);


				 glVertex2f(0.6, -3);


				 glVertex2f(0.6, 3);
				 glEnd();
				 glPopMatrix();
				 glPushMatrix();
				 glScaled(8, 8, 8);
				 glTranslated(0, 1
					 , 3);
				 glRotated(90, 0, 0, 1);
				 glColor3d(0, 1, 1);
				 glBegin(GL_QUADS);

				 glVertex2f(-0.6, 3);


				 glVertex2f(-0.6, -3);


				 glVertex2f(0.6, -3);


				 glVertex2f(0.6, 3);
				 glEnd();
				 glPopMatrix();

			 }

			 glPopMatrix();
		 }*/
	 





}
static int SetupCamera(const char * cparam_name, char * vconf, ARParam * cparam)
{
	ARParam wparam; 
	int xsize, ysize; 


	if (arVideoOpen(vconf) <0) {
		printf("The camera can not be found \ n");
		return FALSE;
	}


	if (arVideoInqSize(&xsize, &ysize) <0) {
		printf("\ n Failed to get the image size");
		return FALSE;
	}

	
	if (arParamLoad(cparam_name, 1, &wparam) <0) {
		printf("\ n Failed to load the camera parameter file");
		return FALSE;
	}
	arParamChangeSize(&wparam, xsize, ysize, cparam);
	arInitCparam(cparam);


	if (arVideoCapStart() != 0) {
		printf("\ n Failed to start video capture");
		return FALSE;
	}

	return TRUE;
}



static int SetupMarker(const char * patt_name, int * patt_id)
{
	if ((*patt_id = arLoadPatt(patt_name)) <0) {
		printf("\ n Failed to load the pattern file");
		return FALSE;
	}

	return TRUE;
}



static int SetupGraphicsWin(const char * title, int dispWidth, int dispHeight)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(dispWidth, dispHeight);
	glutCreateWindow(title);

	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
		return FALSE;
	}

	return TRUE;
}



static int SetupGraphicsFull(int dispWidth, int dispHeight, int dispDepth, int dispRefresh)
{
	char glutGamemode[32];


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);


	if (dispRefresh) {
		sprintf(glutGamemode, "% ix% i:% i @% i", dispWidth, dispHeight, dispDepth, dispRefresh);
	}
	else{
		sprintf(glutGamemode, "% ix% i:% i", dispWidth, dispHeight, dispDepth);
	}
	glutGameModeString(glutGamemode);
	glutEnterGameMode();


	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
		return FALSE;
	}

	return TRUE;
}



static void Quit(void)
{
	

	arVideoCapStop(); 
	arVideoClose(); 
	//arglCleanup(gArglSettings);
	DeleteAllTextures();
}
void vide(){


	
	if (!pause){ frame = frame; }
	else frame += 0.00001;
	if (frame > 100)
	{
		frame = 1;
	}

}
void vide1(){



	frame += 0.00013;
	if (frame > 3)
	{
		frame = 1;
	}

}


static void Keyboard(unsigned char key, int x, int y)
{
	int mode;
	switch (key) {
	case '+': {
				  EarthDayIncrement *= 1.5;
				  if (EarthDayIncrement > 10.0)
					  EarthDayIncrement = 10.0;
				  break;
	}
	case '-': {
				  EarthDayIncrement *= 0.5;
				  if (EarthDayIncrement < 0.001)
					  EarthDayIncrement = 0.001;
				  break;
	}
	case 'z': {xx += 0.5;
		yy += 0.5;
		z+=0.5;
		if (xx>35){
			xx = 15, yy = 15, z = 15;
		}
				  /*ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
				  if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
					  ViewerDistance = MINIMUM_VIEWER_DISTANCE;*/
				  break;
	}
	case 'Z': {
				  ViewerDistance += VIEWER_DISTANCE_INCREMENT;
				  if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
					  ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
				  break;
	}
		
	case 'p': {
				  particleFlag = !particleFlag;
				  break;
	}

	case 'b': {
				  blendFlag = !blendFlag;
				  break;
	}
	case 's': {
				  skyflag = !skyflag;
				  break;
	}
	case 'e': {
				  wire = !wire;
				  break;
	}
	case 0x1B:
	case 'Q':
	case 'q':
		Quit();
		break;
	
	
	case 'D':
	case 'd':
		arDebug = !arDebug;
		break;
	
	case '/':
		printf("Keys:\n");
		printf(" q or [esc]    Quit demo.\n");
		printf(" c             Change arglDrawMode and arglTexmapMode.\n");
		printf(" d             Activate / deactivate debug mode.\n");
		printf(" ? or /        Show this help.\n");
		printf("\nAdditionally, the ARVideo library supplied the following help text:\n");
		arVideoDispOption();
		break;

	case SPACEBAR:{
					  pause =!pause;
					  break;
	}
	case'x':
			skyflag = !skyflag;
	default:
		guss = 0;
		
		break;
	}
}
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch (pressedKey)
	{
	case GLUT_KEY_RIGHT: {
							 viewerAzimuth += VIEWER_ANGLE_INCREMENT;
							 if (viewerAzimuth > 2 * PI)
								 viewerAzimuth -= 2 * PI;
							 break;
	}
	case GLUT_KEY_LEFT:  {
							 viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
							 if (viewerAzimuth < 0.0)
								 viewerAzimuth += 2 * PI;
							 break;
	}
	case GLUT_KEY_UP:    {
							 viewerZenith -= VIEWER_ANGLE_INCREMENT;
							 if (viewerZenith < VIEWER_ANGLE_INCREMENT)
								 viewerZenith = VIEWER_ANGLE_INCREMENT;
							 break;
	}
	case GLUT_KEY_DOWN:  {
							 viewerZenith += VIEWER_ANGLE_INCREMENT;
							 if (viewerZenith > PI - VIEWER_ANGLE_INCREMENT)
								 viewerZenith = PI - VIEWER_ANGLE_INCREMENT;
							 break;
	}

	}
}

void processMouse(int button, int state, int x, int y)

{



	
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
		next1 = next1 + 1;
		printf("%d", next1);
		if (next1 > 9)
			next1 = 0;

	}

	else if (button == GLUT_MIDDLE_BUTTON&&state == GLUT_DOWN) {

	}
	
	else if (button == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN)
	{
		
	}
}
void TimerFunction(int value)
{
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysTranspired += EarthDayIncrement;
	if (EarthDaysTranspired == EARTH_ORBIT_DUR)
		EarthDaysTranspired = 0;


}

static void Idle(void)
{
	static int ms_prev; 
	int ms;
	float s_elapsed; 
	ARUint8 * image; 

	ARMarkerInfo * marker_info; 
	int marker_num;
	int i, j, k;

	

	if (gCharacter[1].patt_found){
		ms = glutGet(GLUT_ELAPSED_TIME);
		s_elapsed = (float)(ms - ms_prev) * 0.1;
		if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
		ms_prev = ms;

		// Update drawing.
		glutTimerFunc(20, TimerFunction, 1);
		

	
	


	}
	

	
	else if (gCharacter[0].patt_found)
	{
		ms = glutGet(GLUT_ELAPSED_TIME);
		s_elapsed = (float)(ms - ms_prev) * 0.001;
		if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
		ms_prev = ms;

		//drawElephant2();
	}else if (guss1 == 1){
		ms = glutGet(GLUT_ELAPSED_TIME);
	s_elapsed = (float)(ms - ms_prev) * 0.001;
	if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
	ms_prev = ms;
	
	
		if (gCharacter[3].patt_found == FALSE){

			t += 0.05;
			if (t > 12){
				t = 0;
			}
			printf("%f\n", t);
		}
		/*if (gCharacter[4].patt_found == FALSE){

			t += 0.04;
			if (t > 12){
				t = 1;
			}
			printf("%f\n", t);
		}
		if (gCharacter[5].patt_found == FALSE){

			t -= 0.04;
			if (t < 0){
				t = 1;
			}
			printf("%f\n", t);
		}*/
		glutTimerFunc(20, TimerFunction, 1);
	
	}else if (gCharacter[6].patt_found ){
		
		vide();
		
	}
	else if (gCharacter[4].patt_found){
		ms = glutGet(GLUT_ELAPSED_TIME);
		s_elapsed = (float)(ms - ms_prev) * 0.001;
		if (s_elapsed < 0.01f) return; // Don't update more often than 100 Hz.
		ms_prev = ms;
		drawElephant();
	}

	if ((image = arVideoGetImage()) != NULL) {


		gARTImage = image;

		for (i = 0; i <NUM_MODEL; i++) gCharacter[i].patt_found = FALSE;


		if (arDetectMarker(gARTImage, gARTThreshhold, &marker_info, &marker_num) <0) {
			exit(0);
		}

		for (i = 0; i <NUM_MODEL; i++) {

			k = -1;
			for (j = 0; j <marker_num; j++) {
				if (marker_info[j].id == gCharacter[i].pattId) {
					if (k == -1) k = j;
					else if (marker_info[j].cf> marker_info[k].cf) k = j;
				}
			}


			if (k != -1) {
				arGetTransMat(&(marker_info[k]), gPatt_centre, gPatt_width, gCharacter[i].trans);
				gCharacter[i].patt_found = TRUE;
			}
		}


		glutPostRedisplay();
	}

}



static void Visibility(int visible)
{

	if (visible == GLUT_VISIBLE) {
		glutIdleFunc(Idle);
	}
	else{
		glutIdleFunc(NULL);
	}
}



static void Reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}








static void Display(void)
{
	
	int i;

	glDrawBuffer(GL_BACK); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	
	arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings); 
	
	arVideoCapNext();
	gARTImage = NULL;

	
	arglCameraFrustumRH(&gARTCparam, gViewDistanceMin, gViewDistanceMax, p);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(p);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST); 

	for (i = 0; i <NUM_MODEL; i++) {
		
		DrawCube();

	}



	glutSwapBuffers();
}

void menu(int value)
{
	int mode;
	switch (value) {
	case '+': {
				  EarthDayIncrement *= 1.5;
				  if (EarthDayIncrement > 10.0)
					  EarthDayIncrement = 10.0;
				  break;
	}
	case '-': {
				  EarthDayIncrement *= 0.5;
				  if (EarthDayIncrement < 0.001)
					  EarthDayIncrement = 0.001;
				  break;
	}
	case 'z': {xx += 0.5;
		yy += 0.5;
		z += 0.5;
		if (xx>35){
			xx = 15, yy = 15, z = 15;
		}
		/*ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
		if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
		ViewerDistance = MINIMUM_VIEWER_DISTANCE;*/
		break;
	}
	case 'Z': {
				  ViewerDistance += VIEWER_DISTANCE_INCREMENT;
				  if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
					  ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
				  break;
	}

	case 'p': {
				  particleFlag = !particleFlag;
				  break;
	}

	case 'b': {
				  blendFlag = !blendFlag;
				  break;
	}
	case 's': {
				  skyflag = !skyflag;
				  break;
	}
	case 'e': {
				  wire = !wire;
				  break;
	}
	case 0x1B:
	case 'Q':
	case 'q':
		Quit();
		break;


	case 'D':
	case 'd':
		arDebug = !arDebug;
		break;

	case '/':
		printf("Keys:\n");
		printf(" q or [esc]    Quit .\n");
		printf(" c             Change arglDrawMode and arglTexmapMode.\n");
		printf(" d             Activate / deactivate debug mode.\n");
		printf(" ? or /        Show this help.\n");
		
		arVideoDispOption();
		break;

	case SPACEBAR:{
					  pause = 2;
					  break;
	}
	
	default:
		guss = 0;

		break;
	}
}

int main(int argc, char ** argv)
{
	int i;

	
	glutInit(&argc, argv);

	
	if (!SetupCamera(gCparamName, gVconf, &gARTCparam)) return 0;

	
	for (i = 0; i <NUM_MODEL; i++) {
		if (!SetupMarker(gPattName[i], &(gCharacter[i].pattId))) return 0;
	}

	
	if (gWindowed) {
		if (!SetupGraphicsWin("THIRD EYE", arImXsize, arImYsize)) return 0;
	}
	else{
		if (!SetupGraphicsFull(gFullWidth, gFullHeight, gFullDepth, gFullRefresh)) return 0;
	}

	
	for (i = 0; i <NUM_MODEL; i++) {
		gCharacter[i].patt_found = FALSE;
		gCharacter[i].rot = 0.0;
		gCharacter[i].x = 0.0;
		gCharacter[i].y = 0.0;
		gCharacter[i].z = 0.0;
	}

	// Set of functions to be called at the end of
	atexit(Quit);

	glutDisplayFunc(Display);


	//glutReshapeFunc(Reshape);
	glutVisibilityFunc(Visibility);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(NonASCIIKeyboardPress);
	glutMouseFunc(processMouse);
	glutCreateMenu(menu);
	glutAddMenuEntry("[+]increase the revolution of planets", '+');
	glutAddMenuEntry("[-]decrease the revolution of planets", '-');
	glutAddMenuEntry("[z]zoom in ", 'z');
	glutAddMenuEntry("[Z]zoom out", 'Z');
	glutAddMenuEntry("[d] debug moode", 'd');
	glutAddMenuEntry("[e]disable solid texture", 'e');
	glutAddMenuEntry("[s]disable background texture", 's');
	glutAddMenuEntry("[p]disable partical effect", 'e');
	glutAddMenuEntry("[b]disable blending effect", 'e');
	glutAddMenuEntry("[spacebar]pause video", SPACEBAR);
	glutAddMenuEntry("[/]print help", '/');
	glutAddMenuEntry("[q]quit", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetLights();
MakeAllImages();
	//init();
	init2();
	sound(argc, argv);
	loadObj("data/eva.obj");

	//init1();


	glutMainLoop();

	return 0;
}
int sound(int argc, char **argv)
{


	// initialise fmod, 44000 Hz, 64 channels
	if (FSOUND_Init(32000, 32, 0) == FALSE)
	{
		std::cerr << "[ERROR] Could not initialise fmod\n";
		return 0;
	}

	g_mp3_stream1 = FSOUND_Stream_Open(data1, FSOUND_2D, 0, 0);
	g_mp3_stream2 = FSOUND_Stream_Open(data2, FSOUND_2D, 0, 0);
	g_mp3_stream3 = FSOUND_Stream_Open(data3, FSOUND_2D, 0, 0);
	g_mp3_stream4 = FSOUND_Stream_Open(data4, FSOUND_2D, 0, 0);
	g_mp3_stream5 = FSOUND_Stream_Open(data5, FSOUND_2D, 0, 0);
	g_mp3_stream6 = FSOUND_Stream_Open(data6, FSOUND_2D, 0, 0);
	g_mp3_stream7 = FSOUND_Stream_Open(data7, FSOUND_2D, 0, 0);
	g_mp3_stream8 = FSOUND_Stream_Open(data8, FSOUND_2D, 0, 0);
	g_mp3_stream9 = FSOUND_Stream_Open(data9, FSOUND_2D, 0, 0);
	g_mp3_stream10 = FSOUND_Stream_Open(data10, FSOUND_2D, 0, 0);
	g_mp3_stream11 = FSOUND_Stream_Open(data11, FSOUND_2D, 0, 0);
	g_mp3_stream12 = FSOUND_Stream_Open(data12, FSOUND_2D, 0, 0);
	g_mp3_stream13 = FSOUND_Stream_Open(data13, FSOUND_2D, 0, 0);
	g_mp3_stream14 = FSOUND_Stream_Open(data14, FSOUND_2D, 0, 0);
	g_mp3_stream15 = FSOUND_Stream_Open(data15, FSOUND_2D, 0, 0);
	g_mp3_stream16 = FSOUND_Stream_Open(data16, FSOUND_2D, 0, 0);
	// make sure mp3 opened OK
	if (!g_mp3_stream1) {
		std::cerr << "[ERROR] could not open file\n";
		return 0;
	}





	// get a pointer to fmods fft (fast fourier transform) unit 
	DLL_API FSOUND_DSPUNIT *fft = FSOUND_DSP_GetFFTUnit();

	// enable the fft unit 
	FSOUND_DSP_SetActive(fft, TRUE);
}


void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha)
{
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}

void drawParticle(Particle currParticle)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glRotatef(currParticle.azimuthRoation, 0, 1, 0);
	glRotatef(currParticle.zenithRotation, 0, 0, 1);
	glTranslatef(SUN_RADIUS + currParticle.surfaceTranslationFactor, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.5, .5, 1.0);
	glBindTexture(GL_TEXTURE_2D, ParticleTextureName);

	
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(1, 1);
	glVertex3f(0.5f, 0.5f, 0.0f); // Top Right
	glTexCoord2d(0, 1);
	glVertex3f(-0.5f, 0.5f, 0.0f); // Top Left
	glTexCoord2d(1, 0);
	glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Right
	glTexCoord2d(0, 0);
	glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
	glEnd();

	
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(1, 1);
	glVertex3f(-0.5f, 0.5f, 0.0f); // Top Right
	glTexCoord2d(0, 1);
	glVertex3f(0.5f, 0.5f, 0.0f); // Top Left
	glTexCoord2d(1, 0);
	glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Right
	glTexCoord2d(0, 0);
	glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Left
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void UpdateLight()
{
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
	glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void SetLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);

	glLightfv(GL_LIGHT2, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

	glLightfv(GL_LIGHT3, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
}
void drawAllParticles(){
	particles.updateAll();
	for (int i = 0; i < particles.getNumberOfParticles(); i++)
		drawParticle(particles.getNextParticle());

}

void renderBitmapString(float x,float y,	float z,	void *font,	char *string) {

	char *c;

	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		
		glutBitmapCharacter(font, *c);
	}

}
void drawsat(){
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, RingTextureName);
	glScalef(1, 1, .02);
	if (wire){
		glutWireSphere(SATURN_RADIUS * 2, 48, 48);
	}
	else
		gluSphere(quadro, SATURN_RADIUS * 2, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawSaturnRing()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, RingTextureName);
	glScalef(1, 1, .02);
	if (wire){
		glutWireSphere(SATURN_RADIUS * 2, 48, 48);
	}
	else
		gluSphere(quadro, SATURN_RADIUS * 2, 48, 48);

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawEarthAndMoon()
{
	GLfloat MoonRevolution = EarthDaysTranspired / LUNAR_CYCLE;
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, EarthTextureName);
	if (wire){
		glutWireSphere(EARTH_RADIUS, 48, 48);
	}
	else
		gluSphere(quadro, EARTH_RADIUS, 48, 48);
	glPopMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * MoonRevolution, 0.0, 1.0, 0.0);
	glTranslatef(MOON_ORBIT_RADIUS, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MoonTextureName);
	gluSphere(quadro, MOON_RADIUS, 48, 48);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawsat1(){
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	//glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	//glRotatef(360.0 * (EarthDaysTranspired / SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
	glTranslatef(0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, RingTextureName);
	glScalef(1, 1, .02);
	if (wire){
		glutWireSphere(SATURN_RADIUS * 2, 48, 48);
	}
	else
		gluSphere(quadro, SATURN_RADIUS * 2, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawSaturnRing1()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	//glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
	//glRotatef(360.0 * (EarthDaysTranspired / SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
	//glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, RingTextureName);
	glScalef(1, 1, .02);
	if (wire){
		glutWireSphere(SATURN_RADIUS * 2, 48, 48);
	}
	else
		gluSphere(quadro, SATURN_RADIUS * 2, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawEarthAndMoon1()
{
	GLfloat MoonRevolution = EarthDaysTranspired / LUNAR_CYCLE;
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	//glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	//glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, EarthTextureName);
	gluSphere(quadro, EARTH_RADIUS, 48, 48);
	glPopMatrix();
	//glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
	//glRotatef(360.0 * (EarthDaysTranspired / EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
	//glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0);
	glRotatef(360.0 * MoonRevolution, 0.0, 1.0, 0.0);
	glTranslatef(MOON_ORBIT_RADIUS, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, MoonTextureName);
	gluSphere(quadro, MOON_RADIUS, 48, 48);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawSun()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, SunTextureName);
	if (wire)
	{
		glutWireSphere(SUN_RADIUS, 48, 48);
	}
	else
		gluSphere(quadro, SUN_RADIUS, 48, 48);

	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -20);
	if (skyflag){
		OnDraw2();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);

}
void MakeAllImages()
{
	MakeImage(EARTH_BMP_FILENAME, EarthTextureName, false);
	MakeImage(MOON_BMP_FILENAME, MoonTextureName, false);
	MakeImage(SUN_BMP_FILENAME, SunTextureName, false);
	MakeImage(MERCURY_BMP_FILENAME, MercuryTextureName, false);
	MakeImage(VENUS_BMP_FILENAME, VenusTextureName, false);
	MakeImage(PARTICLE_BMP_FILENAME, ParticleTextureName, false);
	MakeImage(MARS_BMP_FILENAME, MarsTextureName, false);
	MakeImage(JUPITER_BMP_FILENAME, JupiterTextureName, false);
	MakeImage(SATURN_BMP_FILENAME, SaturnTextureName, false);
	MakeImage(URANUS_BMP_FILENAME, UranusTextureName, false);
	MakeImage(NEPTUNE_BMP_FILENAME, NeptuneTextureName, false);
	MakeImage(PLUTO_BMP_FILENAME, PlutoTextureName, false);
	MakeImage(RING_BMP_FILENAME, RingTextureName, false);
	return;
}


void drawAllPlanets(){

	drawGenericPlanet(MERCURY_INCLINATION, MERCURY_ORBIT_DUR, MERCURY_ORBIT_RADIUS,
		MERCURY_ROTATION_DUR, MercuryTextureName, MERCURY_RADIUS);
	drawGenericPlanet(VENUS_INCLINATION, VENUS_ORBIT_DUR, VENUS_ORBIT_RADIUS,
		VENUS_ROTATION_DUR, VenusTextureName, VENUS_RADIUS);
	drawGenericPlanet(MARS_INCLINATION, MARS_ORBIT_DUR, MARS_ORBIT_RADIUS,
		MARS_ROTATION_DUR, MarsTextureName, MARS_RADIUS);
	drawGenericPlanet(JUPITER_INCLINATION, JUPITER_ORBIT_DUR, JUPITER_ORBIT_RADIUS,
		JUPITER_ROTATION_DUR, JupiterTextureName, JUPITER_RADIUS);
	drawGenericPlanet(SATURN_INCLINATION, SATURN_ORBIT_DUR, SATURN_ORBIT_RADIUS,
		SATURN_ROTATION_DUR, SaturnTextureName, SATURN_RADIUS);
	drawGenericPlanet(URANUS_INCLINATION, URANUS_ORBIT_DUR, URANUS_ORBIT_RADIUS,
		URANUS_ROTATION_DUR, UranusTextureName, URANUS_RADIUS);
	drawGenericPlanet(NEPTUNE_INCLINATION, NEPTUNE_ORBIT_DUR, NEPTUNE_ORBIT_RADIUS,
		NEPTUNE_ROTATION_DUR, NeptuneTextureName, NEPTUNE_RADIUS);
	drawGenericPlanet(PLUTO_INCLINATION, PLUTO_ORBIT_DUR, PLUTO_ORBIT_RADIUS,
		PLUTO_ROTATION_DUR, PlutoTextureName, PLUTO_RADIUS);



}


void drawOne(){


	if ((t > 0 && t<2) || (next1 == 1))
	{
		glScaled(3,3 ,3);
		drawSun();

		if (blendFlag){ //if the user has selected blending, enable it.
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_COLOR, GL_ONE);
		}

		if (particleFlag)
			drawAllParticles();

		glScaled(-2, -2, -2);
		
		renderBitmapString(0.75, 0.1, 0.5, GLUT_BITMAP_HELVETICA_18,
			"Name:Sun");
	
		renderBitmapString(0.3, 0.4, 0.5, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.4, 0.4, 0.5, GLUT_BITMAP_HELVETICA_18, "Named for : Messenger of the Roman gods  ");
		renderBitmapString(0.5, 0.4, 0.5, GLUT_BITMAP_HELVETICA_18, "  Diameter : 3, 031 miles(4, 878 km");
		renderBitmapString(0.6, 0.4, 0.5, GLUT_BITMAP_HELVETICA_18, "  Orbit : 88 Earth days");
		renderBitmapString(0.7, 0.4, 0.5, GLUT_BITMAP_HELVETICA_18, "Day: 58.6 Earth days");

		


	}
	else if ((t > 2 && t<3) || (next1 == 11))
	{
		glScaled(9,9, 9);
		drawOnePlanet(MERCURY_INCLINATION, MERCURY_ORBIT_DUR, MERCURY_ORBIT_RADIUS,
			MERCURY_ROTATION_DUR, MercuryTextureName, MERCURY_RADIUS);
		//glScaled(-2, -2, -2);
		glColor3d(0, 0, 0);
		renderBitmapString(0.65, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18,
			"Name:Mercury");
		renderBitmapString(0.1, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.2, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18, "Named for : Messenger of the Roman gods  ");
		renderBitmapString(0.3, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18, "  Diameter : 3, 031 miles(4, 878 km");
		renderBitmapString(0.4, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18, "  Orbit : 88 Earth days");
		renderBitmapString(0.5, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18, "Day: 58.6 Earth days");

		FSOUND_Stream_Play(0, g_mp3_stream7);


	}

	else if ((t > 3 && t<4) || (next1 == 2)){
		glScaled(9, 9, 9);
		drawOnePlanet(VENUS_INCLINATION, VENUS_ORBIT_DUR, VENUS_ORBIT_RADIUS,
			VENUS_ROTATION_DUR, VenusTextureName, VENUS_RADIUS);
		//glScaled(-2, -2, -2);
		glColor3d(1, 1, 1);
		renderBitmapString(0.7, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Venus");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for: Roman goddess of love and beauty");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Diameter: 7,521 miles (12,104 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit: 225 Earth days");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day: 241 Earth days");
		FSOUND_Stream_Play(0, g_mp3_stream8);

	}
	else if ((t > 4 && t<5) || (next1 == 3)){
		glScaled(9, 9, 9);
		drawEarthAndMoon1();
		//glScaled(-2, -2, -2);
		glColor3d(1, 1, 1);
		renderBitmapString(0.7, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Earth");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Diameter:7,926 miles (12,760 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:365.24 days");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day:23 hours, 56 minutes");
		FSOUND_Stream_Play(0, g_mp3_stream9);
	}
	else if ((t > 5 && t<6) || (next1 == 4)){
		glScaled(9, 9, 9);
		drawOnePlanet(MARS_INCLINATION, MARS_ORBIT_DUR, MARS_ORBIT_RADIUS,
			MARS_ROTATION_DUR, MarsTextureName, MARS_RADIUS);
		//glScaled(-2, -2, -2);
		glColor3d(1, 1, 1);
		renderBitmapString(0.7, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Mars");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for: Roman god of war");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, " Diameter: 4,217 miles (6,787 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:687 Earth days");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day: Just more than one Earth day (24 hours, 37 minutes)");
		FSOUND_Stream_Play(0, g_mp3_stream10);
	}
	else if ((t > 6 && t<7) || (next1 == 5)){
		glScaled(9, 9, 9);
		glTranslated(-4, -9, 1);
		drawGenericPlanet(JUPITER_INCLINATION, JUPITER_ORBIT_DUR, JUPITER_ORBIT_RADIUS,
			JUPITER_ROTATION_DUR, JupiterTextureName, JUPITER_RADIUS);
		//glScaled(-2, -2, -2);
		glTranslated(-3, -3, 0);
		glColor3d(1, 1, 1);
		renderBitmapString(0.7, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Jupiter");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for:Roman god of war");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, " Diameter: 88,730 miles (428,400 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:11.9 Earth years");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day:9.8 Earth hours");
		FSOUND_Stream_Play(0, g_mp3_stream11);
	}
	else if ((t > 7 && t<8) || (next1 == 6)){
		glScaled(7, 7, 7);
		drawOnePlanet(SATURN_INCLINATION, SATURN_ORBIT_DUR, SATURN_ORBIT_RADIUS,
			SATURN_ROTATION_DUR, SaturnTextureName, SATURN_RADIUS);
		drawsat1();
		drawSaturnRing1();
		//glScaled(-2, -2, -2);
		glColor3d(1, 1, 1);
		renderBitmapString(0.7, 0.3, 0.3, GLUT_BITMAP_HELVETICA_18,
			"Name:Saturn");
		renderBitmapString(0.2, 0.3, 0.3, GLUT_BITMAP_HELVETICA_18,
			"Discovery: Known to the ancients and visible to the naked eye");

		renderBitmapString(0.3, 0.3,0.3, GLUT_BITMAP_HELVETICA_18, "Named for:Roman god of agriculture");
		renderBitmapString(0.4, 0.3, 0.3, GLUT_BITMAP_HELVETICA_18, " Diameter: 74,900 miles (120,500 km)");
		renderBitmapString(0.5, 0.3, 0.3, GLUT_BITMAP_HELVETICA_18, "Orbit:29.5 Earth years");
		renderBitmapString(0.6, 0.3, 0.3, GLUT_BITMAP_HELVETICA_18, "Day:About 10.5 Earth hours");
		FSOUND_Stream_Play(0, g_mp3_stream12);

	}
	else if ((t > 8 && t<9) || (next1 == 7)){
		glScaled(9, 9, 9);
		drawOnePlanet(URANUS_INCLINATION, URANUS_ORBIT_DUR, URANUS_ORBIT_RADIUS,
			URANUS_ROTATION_DUR, UranusTextureName, URANUS_RADIUS);
		//glScaled(-2, -2, -2);
		renderBitmapString(0.7, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Uranus");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery:  1781 by William Herschel (was thought previously to be a star)");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for: Personification of heaven in ancient myth");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, " Diameter: 31,763 miles (51,120 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:84 Earth years");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day:About 18 Earth hours");

		FSOUND_Stream_Play(0, g_mp3_stream13);
	}
	else if ((t > 9 && t<10) || (next1 == 8)){
		glScaled(10, 10, 10);
		drawOnePlanet(NEPTUNE_INCLINATION, NEPTUNE_ORBIT_DUR, NEPTUNE_ORBIT_RADIUS,
			NEPTUNE_ROTATION_DUR, NeptuneTextureName, NEPTUNE_RADIUS);
		//glScaled(-2, -2, -2);
		renderBitmapString(0.1, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Neptune");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery:1846");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for:  Roman god of water");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, " Diameter: 30,775 miles (49,530 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:30,775 miles (49,530 km)");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day:19 Earth hours");
		FSOUND_Stream_Play(0, g_mp3_stream14);

	}
	else if ((t > 10) || (next1 == 9)){
		glScaled(5, 5, 5);
		drawOnePlanet(PLUTO_INCLINATION, PLUTO_ORBIT_DUR, PLUTO_ORBIT_RADIUS,
			PLUTO_ROTATION_DUR, PlutoTextureName, PLUTO_RADIUS);
		//glScaled(-2, -2, -2);
		renderBitmapString(0.1, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Name:Pluto");
		renderBitmapString(0.2, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18,
			"Discovery:1930 by Clyde Tombaugh");

		renderBitmapString(0.3, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Named for:  Roman god of the underworld, Hades");
		renderBitmapString(0.4, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, " Diameter: 1,430 miles (2,301 km)");
		renderBitmapString(0.5, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Orbit:248 Earth years");
		renderBitmapString(0.6, 0.3, 0.1, GLUT_BITMAP_HELVETICA_18, "Day: 6.4 Earth day");
		FSOUND_Stream_Play(0, g_mp3_stream15);
	}


}
void drawOnePlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius)
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(inclination, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / orbitDuration), 0.0, 1.0, 0.0);
	glTranslatef(0, 0.0, 0.0);
	glRotatef(360.0 * (CurrentEarthRotation / rotationDuration), 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texturename);
	gluSphere(quadro, radius, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
	GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius)
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(inclination, 0.0, 0.0, 1.0);
	glRotatef(360.0 * (EarthDaysTranspired / orbitDuration), 0.0, 1.0, 0.0);
	glTranslatef(orbitRadius, 0.0, 0.0);
	glRotatef(360.0 * (CurrentEarthRotation / rotationDuration), 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texturename);
	if (wire)
	{
		glutWireSphere(radius, 48, 48);
	}
	else
		gluSphere(quadro, radius, 48, 48);

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void frontscreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	drawstring(20.0, 90.0, 0.0, "Vivekananda Institute of Technology ");
	glColor3f(0.7, 0, 1);
	drawstring(21, 82, 0.0, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1, 0.5, 0);
	drawstring(38, 70, 0.0, "A MINI PROJECT ON");
	glColor3f(1, 0, 0);
	drawstring(40, 60, 0.0, "THIRD EYE");
	glColor3f(1, 0.5, 0);
	drawstring(20, 50, 0.0, "BY:");
	glColor3f(0.5, 0, 0.5);
	drawstring(10, 40, 0.0, "GURUCHARAN.R           (1VK12CS017)");
	drawstring(10, 34, 0.0, "DIVYA.M        (1VK12CS013)");
	glColor3f(1, 0.5, 0);
	drawstring(68, 50, 0.0, "GUIDES:");
	glColor3f(0.5, 0.2, 0.2);
	drawstring(63, 40, 0.0, "PROF LOKHANA");
	
	glColor3f(1, 0.1, 1);
	drawstring(32, 10, 0.0, "PRESS ENTER TO START");
	glFlush();
}

void drawstring(int x,int y, int z,const char *s)   { 
	 int i;
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

};


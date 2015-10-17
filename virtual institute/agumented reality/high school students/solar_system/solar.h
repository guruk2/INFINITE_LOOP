#include<gl/glut.h>
#include"Header.h"

#include "RGBpixmap.h"
#include "ParticleSystem.h"





#define VIEW_SCALEFACTOR		0.025		
#define VIEW_DISTANCE_MIN		0.1			
#define VIEW_DISTANCE_MAX		100.0		
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysTranspired = 0.00;
GLfloat EarthDayIncrement = 0.001;




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
	gluSphere(quadro, SUN_RADIUS, 48, 48);
	glPopMatrix();
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

	if (t > 4 && t<10)
	{
		drawOnePlanet(MERCURY_INCLINATION, MERCURY_ORBIT_DUR, MERCURY_ORBIT_RADIUS,
			MERCURY_ROTATION_DUR, MercuryTextureName, MERCURY_RADIUS);
		renderBitmapString(0, 0.5, 1, GLUT_BITMAP_HELVETICA_18, "Lighthouse3D");

	}
	else if (t > 10 && t<15){
		drawOnePlanet(VENUS_INCLINATION, VENUS_ORBIT_DUR, VENUS_ORBIT_RADIUS,
			VENUS_ROTATION_DUR, VenusTextureName, VENUS_RADIUS);
	}
	else if (t > 15 && t<17){
		drawOnePlanet(MARS_INCLINATION, MARS_ORBIT_DUR, MARS_ORBIT_RADIUS,
			MARS_ROTATION_DUR, MarsTextureName, MARS_RADIUS);

	}
	else if (t > 17 && t<20){
		drawOnePlanet(MARS_INCLINATION, MARS_ORBIT_DUR, MARS_ORBIT_RADIUS,
			MARS_ROTATION_DUR, MarsTextureName, MARS_RADIUS);

	}
	else if (t > 20 && t<23){
		drawOnePlanet(SATURN_INCLINATION, SATURN_ORBIT_DUR, SATURN_ORBIT_RADIUS,
			SATURN_ROTATION_DUR, SaturnTextureName, SATURN_RADIUS);


	}
	else if (t > 23 && t<25){
		drawOnePlanet(URANUS_INCLINATION, URANUS_ORBIT_DUR, URANUS_ORBIT_RADIUS,
			URANUS_ROTATION_DUR, UranusTextureName, URANUS_RADIUS);

	}
	else if (t > 25 && t<27){
		drawOnePlanet(NEPTUNE_INCLINATION, NEPTUNE_ORBIT_DUR, NEPTUNE_ORBIT_RADIUS,
			NEPTUNE_ROTATION_DUR, NeptuneTextureName, NEPTUNE_RADIUS);

	}
	else if (t > 27){
		drawOnePlanet(PLUTO_INCLINATION, PLUTO_ORBIT_DUR, PLUTO_ORBIT_RADIUS,
			PLUTO_ROTATION_DUR, PlutoTextureName, PLUTO_RADIUS);

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
	glRotatef(90.0, 1.0, 0.0, 0.0);
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
	gluSphere(quadro, radius, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

static void DrawCubeUpdate(int timeDelta)
{
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysTranspired += EarthDayIncrement;
	if (EarthDaysTranspired == EARTH_ORBIT_DUR)
		EarthDaysTranspired = 1;
	////glutPostRedisplay();
	glutTimerFunc(20, DrawCubeUpdate, 1);


}
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha)
{
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}
//Draws one individual particle, given a particle struct from the particle
//system object
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

	// Logo Facing Earth
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

	// Logo Facing Away From Earth
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
// Set the two lights to illuminate the scene. //
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

void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}

}




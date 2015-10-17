#include <stdlib.h>
#include <iostream>
#include <glut.h>
#include "texture.h"
unsigned int g_Texture2 = 0;
unsigned int g_Texture3 = 0;
unsigned int g_Texture4 = 0;



void OnDraw() {

	

	
	glBindTexture(GL_TEXTURE_2D, g_Texture2);

	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(-15, 15);

	glTexCoord2f(0, 1);
	glVertex2f(-15, -15);

	glTexCoord2f(1, 1);
	glVertex2f(15, -15);

	glTexCoord2f(1, 0);
	glVertex2f(15, 15);
	glEnd();

	
}
void OnDraw1() {




	glBindTexture(GL_TEXTURE_2D, g_Texture3);


	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(-15, 15);

	glTexCoord2f(0, 1);
	glVertex2f(-15, -15);

	glTexCoord2f(1, 1);
	glVertex2f(15, -15);

	glTexCoord2f(1, 0);
	glVertex2f(15, 15);
	glEnd();


}
void OnDraw2() {




	glBindTexture(GL_TEXTURE_2D, g_Texture4);


	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(-25, 25);

	glTexCoord2f(0, 1);
	glVertex2f(-25, -25);

	glTexCoord2f(1, 1);
	glVertex2f(25, -25);

	glTexCoord2f(1, 0);
	glVertex2f(25, 25);
	glEnd();


}
void init2() {

	// enable the depth test and 2D texturing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// load texture as compressed
	g_Texture2 = LoadTexture("color.tga");
	g_Texture3 = LoadTexture("color2.tga");
	g_Texture4 = LoadTexture("sky2.tga");

	// outputs the size of the texture
	std::cout << "Texture Size=" << (GetTextureSize(g_Texture4) / 1024.0f) << "Kb" << std::endl;
}
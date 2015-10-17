


#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <glut.h>

#define TEXTURE_LOAD_ERROR 0


GLuint texture[8];


GLuint LoadTexture(const char * filename, int width, int
	height)
{
	GLuint texture;
	unsigned char * data;
	FILE * file;

	//The following code will read in our RAW file
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture); //generate the texture with 
	//the loaded data
	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture
	//to it’s array
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
		GL_MODULATE); //set texture environment parameters

	//here we are setting what textures to use and when. The MIN 
	//filter is which quality to show
	//when the texture is near the view, and the MAG filter is which
	//quality to show when the texture
	//is far from the view.

	//The qualities are (in order from worst to best)
	//GL_NEAREST
	//GL_LINEAR
	//GL_LINEAR_MIPMAP_NEAREST
	//GL_LINEAR_MIPMAP_LINEAR

	//And if you go and use extensions, you can use Anisotropic 
	//filtering textures which are of an
	//even better quality, but this will do for now.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	//Here we are setting the parameter to repeat the texture 
	//instead of clamping the texture
	//to the edge of our shape. 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		GL_REPEAT);

	//Generate the texture with mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
		GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data); //free the texture
	return texture; //return whether it was successfull
}



void sky(void) {
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glScalef(2, 2, 1);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2d(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2d(1, 1);
	glVertex3f(1, -1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-1, -1, 1);
	glEnd();
}




void init1(void) {
	int i = 408, b = 408;
	texture[1] = LoadTexture("textures/sky.bmp", i, b);

}
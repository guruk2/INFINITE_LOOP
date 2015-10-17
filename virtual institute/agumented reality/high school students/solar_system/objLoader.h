

#include<stdio.h>
#include<glut.h>
GLuint elephant;
float elephantrot;
char ch = '1';
int camerW, camerH;

void loadObj(char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}

void drawElephant()

{
	//glViewport(camerW / 2, 0, camerW / 2, camerH
	//	);


	glTranslatef(-5,- 5,5);
	glShadeModel(GL_FLAT);

	glScalef(1, 1, 1);
	glRotated(90, 0, 25, 25);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.3;
	if (elephantrot > 360)elephantrot = elephantrot - 360;
}
void drawElephant2()

{
	//glViewport(camerW / 2, 0, camerW / 2, camerH
	//	);


	glTranslatef(0, 0, 0);
	glShadeModel(GL_FLAT);

	glScalef(1, 1, 1);
	glRotated(90, 1, 0, 0);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.3;
	if (elephantrot > 360)elephantrot = elephantrot - 360;
	glColor3f(1, 0, 0);
}

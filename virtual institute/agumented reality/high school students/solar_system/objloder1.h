
#include<GL/glut.h>

#include<stdio.h>
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
void reshape(int w, int h)
{
	camerW = w;
	camerH = h;
	glViewport(w / 2, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);
	glMatrixMode(GL_MODELVIEW);
}
void drawElephant()

{
	glViewport(camerW / 2, 0, camerW / 2, camerH
		);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)camerW / (GLfloat)camerH, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0, 5, -105);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(5, 5, 5);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.1;
	if (elephantrot>360)elephantrot = elephantrot - 360;
	glViewport(0, 0, camerW / 2, camerH
		);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)camerW / (GLfloat)camerH, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0, 5, -105);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(5, 5, 5);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.1;
	if (elephantrot>360)elephantrot = elephantrot - 360;
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawElephant();
	glutSwapBuffers(); //swap the buffers
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 400);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("ObjLoader");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	loadObj("data/Scimitar Dragon.obj");
	glutMainLoop();
	return 0;
}
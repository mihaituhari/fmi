/* Functii pentru desenarea unor poliedre */
#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 6.0, y0 = 9.0, z0 = 10.0;
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 1.0, Vy = -1.0, Vz = 0.0;

GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;

GLfloat dnear = 1.0, dfar = 40.0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//octaedru rosu
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(3.0, 4.0, 2.0);
	glScaled(2.2, 2.2, 2.2);
	glutSolidOctahedron();
	glPopMatrix();

	//cub albastru 
	glColor3f(0.0, 0.0, 1.0);
	glutWireCube(6.0);

	//axele de coordonate
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(20, 0, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 20, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 20);
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Poliedre");

	init();
	glutDisplayFunc(displayFcn);
	glutMainLoop();

    return 1;
}



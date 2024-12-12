/* Obiecte 3D. Transformarea de vizualizare. Transformarea de proiectie.
Elemente de noutate:
- functia pentru vizualizare gluLookAt
- functii pentru proiectii (glOrtho, glFrustum, gluPerspective)
*/

#include <windows.h>
#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 3.0, y0 = 5.0, z0 = 7.0; // pozitia observatorului
GLfloat xref = 1.0, yref = 5.0, zref = 7.0; // punctul de referinta --> spre care se uita observatorul
GLfloat Vx = 0.0, Vy = 0.0, Vz = 1.0; // "verticala din planul de vizualizare" // GLfloat Vx = 12.0, Vy = 18.0, Vz = 21.0;

GLfloat xwMin = -10.0, ywMin = -10.0, xwMax = 10.0, ywMax = 10.0;
GLfloat dnear = 1, dfar = 400.0;

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
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3i(0, 3, 7);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3i(0, 7, 7);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3i(0, 4, 9);
	glEnd();
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Aplicatie");

	init();
	glutDisplayFunc(displayFcn);
	glutMainLoop();
}



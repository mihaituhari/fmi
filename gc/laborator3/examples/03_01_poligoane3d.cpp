/* De retinut:
(i) functii (specifice OpenGL "vechi")
 prin care sunt generate transformari pentru vizualizare 3D
	gluLookAt
	glOrtho
	glMatrixMode
(ii) aspecte legate de fata / spatele poligoanelor
  a) glPolygonMode - L38,39
  b) glCullFace - L40,41,56
  c) glFrontFace - L37
*/

#include <GL/freeglut.h>

GLint winWidth = 600, winHeight = 600; // dimensiunea ferestrei
GLfloat x0 = 0.0, y0 = 0.0, z0 = 40.0; // pozitia observatorului
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; // punctul de referinta (spre care se uita)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // verticala din planul de vizualizare
GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0, dnear = 0.0, dfar = 60.0; // pentru proiectie

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Pozitia observatorului (in (0,0,0), se uita in lungul axei Oz
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
    // Tipul de proiectie realizat
    glMatrixMode(GL_PROJECTION);
    glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void desen(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4.0);
    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    //glEnable(GL_CULL_FACE); //activeaza eliminarea poligoanele vazute din fata/spate
    //glCullFace(GL_FRONT);
    glBegin(GL_QUADS);
    // patratul rosu, situat in planul z=5
    glColor3f(1.0, 0.0, 0.0);
    glVertex3i(5, -5, 5);
    glVertex3i(-5, -5, 5);
    glVertex3i(-5, 5, 5);
    glVertex3i(5, 5, 5);
    // patratul albastru, situat in planul z=10
    glColor3f(0.0, 0.0, 0.5);
    glVertex3i(3, 3, 10);
    glVertex3i(-3, 3, 10);
    glVertex3i(-3, -3, 10);
    glVertex3i(3, -3, 10);
    glEnd();
    // glDisable(GL_CULL_FACE);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Patrate in context 3D");
    init();
    glutDisplayFunc(desen);
    glutMainLoop();
}

/* Rotatii si scalari cu centrul diferit de origine. Triunghi rotit (static)
De retinut:
- daca dorim sa efectuam o rotatie/scalare cu centrul C diferit de O=(0,0,0):
(i) centrul rotatiei/scalarii este translatat in origine
(ii) se efectueaza rotatia/scalarea
(iii) se aplica translatia inversa, pentru a "muta" originea inapoi, in centrul C
*/

#include <gl/freeglut.h>

void init(void)  // initializare fereastra de vizualizare
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-800.0, 800.0, -600.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void rotireTriunghi(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    // AXELE
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(0.5);
    glBegin(GL_LINES);
    glVertex2f(-800, 0);
    glVertex2f(800, 0);
    glVertex2f(0, -600);
    glVertex2f(0, 600);
    glEnd();

    // TRIUNGHIUL ORIGINAL. Centrul de greutate este (300, 200)
    glLineWidth(6.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 1);
    glVertex2f(100, 100);
    glColor3f(0, 1, 0);
    glVertex2f(500, 100);
    glColor3f(1, 0, 0);
    glVertex2f(300, 400);
    glEnd();

    // CENTRUL DE GREUTATE
    glColor3f(0, 0, 0);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glVertex2f(300, 200);
    glEnd();

    // APLICAREA TRANSFORMARII ASUPRA TRIUNGHIULUI
    glPushMatrix(); // pastram in stiva matricea identica
    glTranslated(300, 200, 0); // translatia in centrul de greutate initial - DE COMENTAT
    glRotated(10, 0, 0, 1); // aplicam rotatia
    glTranslated(-300, -200, 0); // centrul de greutate este translatat in origine - DE COMENTAT

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 1);
    glVertex2f(100, 100);
    glColor3f(0, 1, 0);
    glVertex2f(500, 100);
    glColor3f(1, 0, 0);
    glVertex2f(300, 400);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();

    glFlush();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Triunghi rotit in jurul centrului de greutate");
    init();
    glutDisplayFunc(rotireTriunghi);
    glutMainLoop();
}

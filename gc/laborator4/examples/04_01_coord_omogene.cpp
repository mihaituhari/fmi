/* Acest cod sursa are rolul de a ilustra utilizarea celei de-a patra coordonate.
De retinut:
- daca a 4-a coordonata este 0, e vorba de o directie
- daca a 4-a coordonata este !=0, e vorba de un punct; coordonatele sale pot fi obtinute impartind la a 4-a coord
*/

#include <gl/freeglut.h>

// coordonatele varfurilor
float p1[] = {-100, -100, 0, 1}; // rosu, a 4-a coordonata este 1
float p2[] = {100, -100, 0, 1};
float p3[] = {100, 100, 0, 1};
float p4[] = {-100, 100, 0, 1};
float p5[] = {-100, -100, 0, 0.5}; // albastru, a 4-a coordonata este 0.5
float p6[] = {100, -100, 0, 0.5};
float p7[] = {100, 100, 0, 0.5};
float p8[] = {-100, 100, 0, 0.5};
float p9[] = {-100, -100, 0, 0.0}; // varful 9 (stanga jos) are a 4a coordonata egala cu 0

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION); // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(-800.0, 800.0, -600.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // ILUSTRARE COORDONATE OMOGENE
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(6.0);
    glColor3f(1.0, 0.0, 0.0); // primul poligon (vf. cu ultima coordonata omogena 1) este rosu
    glBegin(GL_POLYGON);
    glVertex4fv(p1);
    glVertex4fv(p2);
    glVertex4fv(p3);
    glVertex4fv(p4);
    glEnd();

    glColor3f(0.0, 0.0, 1.0); // al doilea poligon (vf. cu ultima coordonata omogena 0.5) este albastru
    glBegin(GL_POLYGON);
    glVertex4fv(p5);
    //glVertex4fv (p9); // varful este dat de o directie
    glVertex4fv(p6);
    glVertex4fv(p7);
    glVertex4fv(p8);
    glEnd();

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Coordonate omogene. Rolul celei de-a 4-a coordonate");
    init();
    glutDisplayFunc(desen);
    glutMainLoop();
}

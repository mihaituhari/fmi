/* Compunerea transformarilor.
De retinut:
- ORDINEA in care sunt indicate transformarile in codul sursa este esentiala!
- pot fi utilizate simultan doua ferestre de desenare
- functia glViewport
*/

#include <gl/freeglut.h>

void init1(void)  // initializare fereastra de vizualizare 1
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizar
    glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(-400.0, 400.0, -300.0, 300.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void init2(void)  // initializare fereastra de vizualizare 2
{
    glClearColor(1.0, 1.0, 0.7, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizar
    glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(-400.0, 400.0, -300.0, 300.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare
{
    // glViewport (0, 0, 400, 300);

    // axele
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 0.0);
    glVertex2i(-400, 0);
    glVertex2i(400, 0);
    glVertex2i(0, -300);
    glVertex2i(0, 300);
    glEnd();

    // patrat original albastru
    glColor3f(0.0, 0.0, 1.0);
    glRecti(-20, -20, 20, 20);

    // patrat translatat rosu
    glPushMatrix();
    glTranslated(200.0, 100.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glRecti(-20, -20, 20, 20);
    glPopMatrix();

    // reflexia fata de Ox1 violet
    glPushMatrix();
    GLdouble ref1[16];
    GLint k;
    for (k = 0; k < 16; k++)
        ref1[k] = 0.0;
    ref1[0] = 1.0;
    ref1[5] = -1.0;
    ref1[10] = 1.0;
    ref1[15] = 1.0;
    glMultMatrixd(ref1);
    glTranslated(200.0, 100.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glRecti(-20, -20, 20, 20);
    glPopMatrix();

    // COMPUNERILE
    // compunerea T o S, dreptunghi verde
    glPushMatrix();
    glTranslated(200.0, 100.0, 0.0);
    glScalef(0.5, 2.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glRecti(-20, -20, 20, 20);
    glPopMatrix();
    // compunerea S o T, dreptunghi galben 
    glPushMatrix();
    glScalef(0.5, 2.0, 0.0);
    glTranslated(200.0, 100.0, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    glRecti(-20, -20, 20, 20);
    glPopMatrix();

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); // initializare GLUT
    int windowID1;
    int windowID2;
    glutInitDisplayMode(
            GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)

    // fereastra 1
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(800, 600); // dimensiunile ferestrei
    windowID1 = glutCreateWindow("Fereastra 1"); // creeaza fereastra1
    init1();
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie

    // fereastra 2
    glutInitWindowPosition(900, 550); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(400, 300); // dimensiunile ferestrei
    windowID2 = glutCreateWindow("Fereastra 2"); // creeaza fereastra2
    init2(); // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie

    glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}

#include <GL/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)

void init(void)  // initializare fereastra de vizualizare
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
    glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(0.0, 400.0, 0.0, 300.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare
{
    glColor3f(0.0, 0.0, 1.0); // culoarea punctelor: albastru
    // glEnable(GL_POINT_SMOOTH);
    // glPointSize(30.0);
    glBegin(GL_POINTS); // reprezinta puncte
    glVertex2i(20, 20);
    glVertex2i(21, 21);
    glVertex2i(22, 22);
    glVertex2i(23, 23);
    glVertex2i(24, 24);
    glVertex2i(100, 100);
    glEnd();
    // glDisable(GL_POINT_SMOOTH);

    int p1[] = {50, 100};;
    glColor3f(0.0, 0.6, 0.2);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2iv(p1);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // culoarea liniei frante: rosu
    glBegin(GL_LINE_STRIP);
    glVertex2i(0, 0);
    glVertex2i(200, 100);
    glVertex2i(300, 120);
    glVertex2i(300, 220);
    glEnd();

    glColor3f(1.0, 1.0, 0.0); // culoarea triunghiului: galben
    glPointSize(3.0);
    // glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(150, 100); // centru jos
    glColor3f(0.2, 1.0, 0.0);
    glVertex2i(250, 100); // centru jos
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(200, 200); // centru sus
    glEnd();

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); // initializare GLUT
    glutInitDisplayMode(
            GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(800, 600); // dimensiunile ferestrei
    glutCreateWindow(
            "Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
    init(); // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
    glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

    return 0;
}

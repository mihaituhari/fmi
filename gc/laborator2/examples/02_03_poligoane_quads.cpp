#include <GL/freeglut.h>

GLint winWidth = 800, winHeight = 600;

void init(void)  // initializare fereastra de vizualizare
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
    glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void reshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    winWidth = newWidth;
    winHeight = newHeight;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void desen1(void) // procedura desenare
{
// Valorile coordonatelor
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    x1 = 10;
    y1 = 10;
    x2 = 110;
    y2 = 10;
    x3 = 110;
    y3 = 110;
    x4 = 10;
    y4 = 110;
    x5 = 210;
    y5 = 10;
    x6 = 210;
    y6 = 110;

    x1 = 10;
    y1 = 10;
    x3 = 110;
    y3 = 10;
    x4 = 110;
    y4 = 110;
    x2 = 10;
    y2 = 110;
    x5 = 210;
    y5 = 10;
    x6 = 210;
    y6 = 110;

// Desenarea dreptunghiurilor (culoarea este rosu)
// glPolygonMode (GL_BACK, GL_LINE);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUAD_STRIP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glVertex2i(x5, y5);
    glVertex2i(x6, y6);
    glEnd();

    // Desenarea unor primitive de tip litera folosind functii din biblioteca GLUT
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(x1, y1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    glRasterPos2i(x2, y2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
    glRasterPos2i(x3, y3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');
    glRasterPos2i(x4, y4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '4');
    glRasterPos2i(x5, y5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '5');
    glRasterPos2i(x6, y6);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '6');

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void desen2(void) // procedura desenare
{
// Valorile coordonatelor
    int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    x1 = 10;
    y1 = 10;
    x2 = 110;
    y2 = 10;
    x3 = 110;
    y3 = 110;
    x4 = 10;
    y4 = 110;
    x5 = 210;
    y5 = 10;
    x6 = 210;
    y6 = 110;

    x1 = 10;
    y1 = 10;
    x3 = 110;
    y3 = 10;
    x4 = 110;
    y4 = 110;
    x2 = 10;
    y2 = 110;
    x5 = 210;
    y5 = 10;
    x6 = 210;
    y6 = 110;

// Desenarea dreptunghiurilor (fiecare varf are culoarea lui)
    glPolygonMode(GL_BACK, GL_LINE);
    glLineWidth(4.0);

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(x1, y1);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(x2, y2);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(x3, y3);
    glColor3f(0.8, 0.4, 0.0);
    glVertex2i(x4, y4);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(x5, y5);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(x6, y6);
    glEnd();

    // Desenarea unor primitive de tip litera folosind functii din biblioteca GLUT
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(x1, y1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    glRasterPos2i(x2, y2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
    glRasterPos2i(x3, y3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');
    glRasterPos2i(x4, y4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '4');
    glRasterPos2i(x5, y5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '5');
    glRasterPos2i(x6, y6);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '6');

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); // initializare GLUT
    glutInitDisplayMode(
            GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(winWidth, winHeight); // dimensiunile ferestrei
    glutCreateWindow(
            "Dreptunghiuri - GL_QUAD_STRIP"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

    init(); // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen2); // procedura desen este invocata ori de cate ori este nevoie
    //glutReshapeFunc (reshapeFcn);
    glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

    return 0;
}
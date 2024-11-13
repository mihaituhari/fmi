#include <GL/freeglut.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

/**
 * Punctul 1.
 *
 * Desenati, in aceeasi figura, un poligon convex si un poligon concav.
 * Fundalul este un gradient (nu exista o functie dedicata in acest sens).
 */
void drawGradientBackground() {
    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 1.0); // Jos - albastru
    glVertex2i(0, 0);
    glVertex2i(800, 0);

    glColor3f(1.0, 1.0, 1.0); // Sus - alb
    glVertex2i(800, 600); // Intreg ecranul
    glVertex2i(0, 600);
    glEnd();
}

void drawConvexPolygon() {
    glColor3f(1.0, 0.5, 0.0); // Portocaliu
    glBegin(GL_POLYGON);
    glVertex2i(100, 450);
    glVertex2i(200, 550);
    glVertex2i(300, 550);
    glVertex2i(400, 450);
    glVertex2i(250, 350);
    glEnd();
}

void drawConcavePolygon() {
    glColor3f(0.5, 0.0, 0.5); // Violet
    glBegin(GL_POLYGON);
    glVertex2i(500, 450);
    glVertex2i(600, 550);
    glVertex2i(700, 450);
    glVertex2i(625, 400); // In interior
    glVertex2i(700, 350);
    glVertex2i(500, 350);
    glEnd();
}

/**
 * Punctul 2.
 *
 * Desenati, in aceeasi figura, un triunghi ABC vazut din fata si un triunghi DEF vazut din spate.
 * Triunghiul vazut din fata este desenat cu modul GL_FILL, cel vazut din spate cu modul GL_LINE.
 * Indicati, cu litere, varfurile triunghiurilor pe figura.
 */
void drawFrontTriangle() {
    // Triunghi ABC, din fata (GL_FILL)
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    glVertex2i(100, 200); // A
    glVertex2i(300, 200); // B
    glVertex2i(200, 300); // C
    glEnd();

    // Litere ABC
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(100, 200); // A
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
    glRasterPos2i(300, 200); // C
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');
    glRasterPos2i(200, 300); // B
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
}

void drawBackTriangle() {
    // Triunghi DEF, din spate (GL_LINE)
    glPolygonMode(GL_BACK, GL_LINE);
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    glVertex2i(500, 200); // D
    glVertex2i(600, 300); // E
    glVertex2i(700, 200); // F
    glEnd();

    // Litere DEF
    glColor3f(1.0, 1.0, 1.0); // Alb
    glRasterPos2i(500, 200); // D
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');
    glRasterPos2i(600, 300); // E
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    glRasterPos2i(700, 200); // F
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'F');
}

/**
 * Punctul 3.
 *
 * Creati un model (desen) 2D mai complex, folosind diverse tipuri de primitive grafice
 * (inclusiv liste de display).
 */
GLuint treeDisplayList;

void renderTree(int x) {
    int yOffset = 5; // Offset de la marginea de jos
    int trunkWidth = 20; // Latime trunchi
    int trunkHeight = 50; // Inaltime trunchi
    int triangleHeight = 60; // Inaltime triunghi coroana

    treeDisplayList = glGenLists(1);
    glNewList(treeDisplayList, GL_COMPILE);

    // Trunchiul copacului (maro)
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_QUADS);
    glVertex2i(x - trunkWidth / 2, yOffset);
    glVertex2i(x + trunkWidth / 2, yOffset);
    glVertex2i(x + trunkWidth / 2, yOffset + trunkHeight);
    glVertex2i(x - trunkWidth / 2, yOffset + trunkHeight);
    glEnd();

    // Coroana copacului (verde)
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(x, yOffset + trunkHeight + triangleHeight);
    glVertex2i(x - trunkWidth, yOffset + trunkHeight);
    glVertex2i(x + trunkWidth, yOffset + trunkHeight);
    glEnd();
    glEndList();
}

void drawForest() {
    int treeSpacing = 50; // Spatierea intre copaci

    for (int x = 20; x < 800; x += treeSpacing) { // Toata latimea ecranului
        renderTree(x);
        glCallList(treeDisplayList);
    }
}

/**
 * Main.
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Punctul 1
    drawGradientBackground();
    drawConvexPolygon();
    drawConcavePolygon();

    // Punctul 2
    drawFrontTriangle();
    drawBackTriangle();

    // Punctul 3
    drawForest();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Curs 2 - poligoane - Mihai Tuhari");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

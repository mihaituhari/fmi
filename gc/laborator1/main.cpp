#include <gl/freeglut.h>

// 04/11/2024
void init() {
    glClearColor(0.282f, 0.545f, 0.639f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

// 2. Draw the text "MIHAI"
void drawText() {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6.0);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw letter M
    glBegin(GL_LINES);
    glVertex2i(10, 10);
    glVertex2i(10, 50);
    glVertex2i(10, 50);
    glVertex2i(20, 30);
    glVertex2i(20, 30);
    glVertex2i(30, 50);
    glVertex2i(30, 50);
    glVertex2i(30, 10);
    glEnd();

    // Draw letter I
    glBegin(GL_LINES);
    glVertex2i(40, 10);
    glVertex2i(40, 50);
    glEnd();

    // Draw letter H
    glBegin(GL_LINES);
    glVertex2i(50, 10);
    glVertex2i(50, 50);
    glVertex2i(50, 30);
    glVertex2i(60, 30);
    glVertex2i(60, 10);
    glVertex2i(60, 50);
    glEnd();

    // Draw letter A
    glBegin(GL_LINES);
    glVertex2i(70, 10);
    glVertex2i(80, 50);
    glVertex2i(80, 50);
    glVertex2i(90, 10);
    glVertex2i(75, 30);
    glVertex2i(85, 30);
    glEnd();

    // Draw letter I
    glBegin(GL_LINES);
    glVertex2i(100, 10);
    glVertex2i(100, 50);
    glEnd();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
}

// 3. Draw a cube with RGB colors
void drawCubeRGB() {
    glBegin(GL_QUADS);

    // FRONT FACE
    // Top-left corner: cyan
    glColor3f(0.0, 1.0, 1.0);
    glVertex2i(50, 200);

    // Top-right corner: white
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(150, 200);

    // Bottom-right corner: yellow
    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(150, 100);

    // Bottom-left corner: green
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(50, 100);

    // TOP FACE
    // Bottom-left corner: cyan
    glColor3f(0.0, 1.0, 1.0);
    glVertex2i(50, 200);

    // Top-left corner: cyan
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(100, 230);

    // Top-right corner: magenta
    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(200, 230);

    // Bottom-right corner: white
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(150, 200);

    // RIGHT FACE
    // Bottom-left corner: yellow
    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(150, 100);

    // Bottom-right corner: red
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(200, 130);

    // Top-right corner: magenta
    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(200, 230);

    // Top-left corner: white
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(150, 200);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawText();
    drawCubeRGB();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(300, 300); // 1. Change window position
    glutInitWindowSize(900, 700); // 1. Change window size
    glutCreateWindow("Curs 1 - text/cub - Mihai Tuhari");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

/**
 * Laborator 3 / tema 2
 * Mihai Tuhari
 *
 * Desenati un patrat care se rostogoleste de-a lungul unei axe.
 */
#include <GL/freeglut.h>

static GLdouble x = 0.0;
static GLdouble angle = 0.0;
static GLdouble step = 10.0;
static GLdouble rotation_speed = 10.0;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw X-axis
    glColor3f(0.0, 0.0, 0.0); // Black color for the axis
    glBegin(GL_LINES);
    glVertex2f(0.0, 300.0);
    glVertex2f(800.0, 300.0);
    glEnd();

    // Draw red square (rotates and moves along the X-axis)
    glPushMatrix();
    glTranslated(x, 300.0, 0.0); // Translate X-axis
    glRotated(angle, 0.0, 0.0, 1); // Rotate square
    glTranslated(-20.0, -20.0, 0.0); // Adjust to square center

    glColor3f(1.0, 0.0, 0.0);
    glRecti(0, 0, 40, 40);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 820.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update(int value) {
    x += step;

    // Rotate based on the direction of movement
    if (step > 0) {
        angle -= rotation_speed; // Rotate clockwise (right)
    } else {
        angle += rotation_speed; // Rotate counterclockwise (left)
    }

    // Reverse direction if hitting screen edges
    if (x > 800.0 || x < 0.0) {
        step = -step; // Reverse direction
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Approximately 60 FPS
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mihai Tuhari - Lab 3 / Punctul 2");

    init();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
}
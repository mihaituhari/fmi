#include <GL/freeglut.h>

static GLdouble i = 0.0;
static GLdouble j = 0.0;
static GLdouble alpha = 0.1;
static GLdouble step = 0.1;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void dreptunghi(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(350, i, 0.0); // Translatam pe axa Oy

    // Patrat mic rosu - se roteste
    glPushMatrix();
    glRotated(j, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glRecti(-5, 30, 5, 40);
    glPopMatrix();

    // Matrat mare albastru
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glRecti(-20, -12, 20, 12);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void miscad(void) {
    i = i + step;
    if (i > 550.0)
        step = -alpha;
    else if (i < 0.0)
        step = alpha;
    j = j + step;
    glutPostRedisplay();
}

void miscas(void) {
    i = i + step;
    if (i < 0.0)
        step = alpha;
    else if (i > 550.0)
        step = -alpha;
    j = j + step;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                step = -alpha;
            glutIdleFunc(miscas);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                step = alpha;
            glutIdleFunc(miscad);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Mihai Tuhari - Lab 3 / Punctul 1");
    init();

    glutDisplayFunc(dreptunghi);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
}

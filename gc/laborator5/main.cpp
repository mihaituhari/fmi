#include <GL/freeglut.h>
#include <cmath>

float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0, beta = 0, dist = 10.0f;
float Obsx, Obsy, Obsz;

void reshapeAndProjection(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    float ratio = w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(50.0f, ratio, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawChristmasTree() {
    // Conul de jos
    glPushMatrix();
    glColor3f(0.0, 0.6, 0.0);
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(1.5, 3.0, 12, 20);
    glPopMatrix();

    // Conul din mijloc
    glPushMatrix();
    glColor3f(0.0, 0.7, 0.0);
    glTranslatef(0.0, 0.0, -0.5);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(1.2, 2.5, 12, 20);
    glPopMatrix();

    // Conul de sus
    glPushMatrix();
    glColor3f(0.0, 0.8, 0.0);
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.9, 2.0, 12, 20);
    glPopMatrix();

    // Trunchiul bradului
    glPushMatrix();
    glColor3f(0.5, 0.35, 0.05); // Maro
    glTranslatef(0.0, 0.0, -3.0);

    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.4, 0.4, 1.0, 20, 20);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    Obsx = Refx + dist * cos(alpha) * cos(beta);
    Obsy = Refy + dist * cos(alpha) * sin(beta);
    Obsz = Refz + dist * sin(alpha);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Obsx, Obsy, Obsz, Refx, Refy, Refz, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    drawChristmasTree();
    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT:
            beta -= 0.05;
            break;
        case GLUT_KEY_RIGHT:
            beta += 0.05;
            break;
        case GLUT_KEY_UP:
            alpha += 0.05;
            break;
        case GLUT_KEY_DOWN:
            alpha -= 0.05;
            break;
    }
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            dist += 0.5;
            break;
        case '-':
            dist -= 0.5;
            break;
        case 27:
            exit(0); // ESC
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Brad de Craciun 3D");

    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    glClearColor(0.8, 0.9, 0.95, 0.0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

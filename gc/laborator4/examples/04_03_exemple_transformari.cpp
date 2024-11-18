/* Transformari. Meniuri GLUT
De retinut:
- desenarea unui cerc/disc ca un poligon folosind liste de display (si exemplul 03_L_1_hexagon)
- utilizarea matricelor
- utilizarea meniurilor GLUT; functiile specifice
*/

#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

const double TWO_PI = 6.2831853;
GLsizei winWidth = 500, winHeight = 500;
GLuint cercID;
static GLfloat rotTheta = 0.0;

class scrPt {
public:
    GLint x, y;
};

// Initializari ptr meniu
enum {
    NONE, AFIN, PERSP
};
int rendermode = NONE;

void menu(int selection) {
    rendermode = selection;
    glutPostRedisplay();
}

static void init(void) {
    // cercul este definit in init sub forma de display list
    scrPt cerc;
    GLdouble theta;
    GLint k;
    GLint n = 2000;
    cercID = glGenLists(1);
    glNewList(cercID, GL_COMPILE);
    glPointSize(2.0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // vizualizare contur
    glBegin(GL_POLYGON);
    for (k = 0; k < n; k++) {
        theta = TWO_PI * k / n;
        cerc.x = 100 * cos(theta);
        cerc.y = 100 * sin(theta);
        glVertex2f(cerc.x, cerc.y);
    }
    glEnd();
    glEndList();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void desenCerc(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    switch (rendermode) {

        case NONE:
            glColor3f(0.0, 1.0, 0.0);
            glCallList(cercID);
            break;

        case AFIN:
            glColor3f(1.0, 0.0, 0.0);
            GLdouble mat1[16];
            GLint k;
            for (k = 0; k < 16; k++)
                mat1[k] = 0.0;
            mat1[0] = 1.0;
            mat1[5] = 2.0;
            mat1[4] = 3.0;
            mat1[1] = 3.0;
            mat1[10] = 1.0;
            mat1[15] = 1.0;
            glMultMatrixd(mat1);
            glCallList(cercID);
            glLoadIdentity();
            break;

        case PERSP:
            glColor3f(0.0, 0.0, 1.0);
            GLdouble mat2[16];
            for (k = 0; k < 16; k++)
                mat2[k] = 0.0;
            mat2[0] = 1.0;
            mat2[10] = 1.0;

            mat2[13] = 100;
            mat2[7] = 1.0;
            glMultMatrixd(mat2);
            glCallList(cercID);
            glLoadIdentity();
            break;
    };

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Transformari. Matrice 4x4");

    init();
    glutDisplayFunc(desenCerc);

    glutCreateMenu(menu);
    glutAddMenuEntry("Original", NONE);
    glutAddMenuEntry("Transformare afina", AFIN);
    glutAddMenuEntry("Transformare perspectiva", PERSP);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}

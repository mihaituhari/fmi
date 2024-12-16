#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 6.0, y0 = 9.0, z0 = 10.0;
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 1.0, Vy = -1.0, Vz = 0.0;

GLfloat xwMin = -30.0, ywMin = -30.0, xwMax = 30.0, ywMax = 30.0;

GLfloat dnear = 1.0, dfar = 40.0;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

    glMatrixMode(GL_PROJECTION);
    glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void displayFcn(void) {
    glClearDepth(0.88);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc (GL_GREATER);
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(1.0);
    //cub albastru
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCube(6.0);

    //cub rosu
    glColor3f(1.0, 0.0, 0.0);
    //glMatrixMode (GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(4.0, 0.0, 0.0);
    //glScaled (2.2, 2.2, 2.2);
    glutWireCube(6.0);
    glPopMatrix();


    //sfera verde
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(4.0, 25, 25);


    //glDisable (GL_DEPTH_TEST);

    //axele de coordonate
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(20, 0, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 20, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 19);
    glEnd();
    //literele
    glRasterPos3i(21, 0, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'x');
    glRasterPos3i(0, 21, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'y');
    glRasterPos3i(0, 0, 20);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'z');
    glFlush();

}

void reshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newWidth, newHeight);

    winWidth = newWidth;
    winHeight = newHeight;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Poliedre 3D - teste de adancime");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(reshapeFcn);
    glutMainLoop();

    return 1;
}



#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static GLint fogMode;

static void init(void) {
    GLfloat position[] = {0.5, 0.5, 3.0, 0.0};

    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {
        GLfloat mat[3] = {0.1745, 0.01175, 0.01175};
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
        mat[0] = 0.61424;
        mat[1] = 0.04136;
        mat[2] = 0.04136;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
        mat[0] = 0.727811;
        mat[1] = 0.626959;
        mat[2] = 0.626959;
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
    }

    glEnable(GL_FOG);
    {
        GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

        fogMode = GL_EXP;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.3);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 5.0);
    }
    glClearColor(0.5, 0.5, 0.5, 1.0);  /* fog color */
}

static void renderSphere(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();
}

/* display() draws 5 spheres at different z positions.
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, -0.4, 1.0, 0.0, -0.4, -1.0, 0, 1, 0);
    renderSphere(-1., -0.5, -2.0);
    renderSphere(0., -0.5, -3.0);
    renderSphere(1., -0.5, -4.0);
    renderSphere(2., -0.5, -5.0);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, w / h, 0.01, 25);
    /*
    if (w <= h)
       glOrtho (-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
          2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
       glOrtho (-2.5*(GLfloat)w/(GLfloat)h,
          2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
          */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
        case 'F':
            if (fogMode == GL_EXP) {
                fogMode = GL_EXP2;
                printf("Fog mode is GL_EXP2\n");
            } else if (fogMode == GL_EXP2) {
                fogMode = GL_LINEAR;
                printf("Fog mode is GL_LINEAR\n");
            } else if (fogMode == GL_LINEAR) {
                fogMode = GL_EXP;
                printf("Fog mode is GL_EXP\n");
            }
            glFogi(GL_FOG_MODE, fogMode);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, depth buffer, and handle input events.
 */
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

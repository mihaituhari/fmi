#include <GL/freeglut.h>
#include <cmath>

float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0, beta = 0, dist = 10.0f;
float Obsx, Obsy, Obsz;

bool fog = false;

void reshapeAndProjection(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    float ratio = (float) w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(50.0f, ratio, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    GLfloat position[] = {5.0, 5.0, 5.0, 1.0};
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void setupFog() {
    GLfloat fogColor[] = {0.5, 0.5, 0.5, 1.0};

    glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.25);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 2.0);
    glFogf(GL_FOG_END, 10.0);
}

void drawChristmasTree() {
    // Brad
    GLfloat tree_ambient[] = {0.0, 0.2, 0.0, 1.0};
    GLfloat tree_diffuse[] = {0.0, 0.6, 0.0, 1.0};
    GLfloat tree_specular[] = {0.0, 0.1, 0.0, 1.0};
    GLfloat tree_shininess[] = {10.0};
    GLfloat tree_emission[] = {0.2, 0.2, 0.2, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, tree_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tree_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, tree_emission);

    // Conul de jos
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(1.5, 3.0, 12, 20);
    glPopMatrix();

    // Conul din mijloc
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(1.2, 2.5, 12, 20);
    glPopMatrix();

    // Conul de sus
    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.9, 2.0, 12, 20);
    glPopMatrix();

    // Trunchiul bradului
    GLfloat trunk_ambient[] = {0.2, 0.1, 0.0, 1.0};
    GLfloat trunk_diffuse[] = {0.5, 0.35, 0.05, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, trunk_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, trunk_diffuse);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.4, 0.4, 1.0, 20, 20);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

void drawShadow() {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Culoare umbra
    glColor4f(0.0, 0.0, 0.0, 0.5);

    // Proiectie umbra
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 0.2);
    glutSolidCone(1.0, 1.0, 12, 20);
    glPopMatrix();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void setSceneColor() {
    if (fog) {
        glClearColor(0.5, 0.5, 0.5, 1.0); // Ceata
    } else {
        glClearColor(0.8, 0.9, 0.95, 0.0); // Fundal implicit
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Obsx = Refx + dist * cos(alpha) * cos(beta);
    Obsy = Refy + dist * cos(alpha) * sin(beta);
    Obsz = Refz + dist * sin(alpha);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Obsx, Obsy, Obsz, Refx, Refy, Refz, 0.0f, 0.0f, 1.0f);

    setupLighting();
    setupFog();
    drawChristmasTree();
    drawShadow();

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
        case 'f':
        case 'F':
            fog = !fog;

            if (fog) {
                glEnable(GL_FOG);
            } else {
                glDisable(GL_FOG);
            }

            setSceneColor();
            glutPostRedisplay();
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
    glutCreateWindow("Brad cu lumina si umbra");

    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    setSceneColor();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}

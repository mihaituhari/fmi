/* Hearn & Baker , p. 650 */

#include <gl/freeglut.h>

void init(void) {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void desen(void) {
    GLint k;
    GLubyte texLine[16]; // 16-element texture array

    /* Define two green elements for the texturee pattern */
    /* Each texture color is specified in four array positions */

    for (k = 0; k <= 2; k += 2) {
        texLine[4 * k] = 0;
        texLine[4 * k + 1] = 255;
        texLine[4 * k + 2] = 0;
        texLine[4 * k + 3] = 255;
    };
    /* Define two red elements for the texture pattern */

    for (k = 1; k <= 3; k += 2) {
        texLine[4 * k] = 255;
        texLine[4 * k + 1] = 0;
        texLine[4 * k + 2] = 0;
        texLine[4 * k + 3] = 255;
    };

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, texLine);
    glEnable(GL_TEXTURE_1D);


    float endPt1[3], endPt2[3];
    endPt1[0] = 110;
    endPt1[1] = 170;
    endPt1[2] = 0;
    endPt2[0] = 290;
    endPt2[1] = 170;
    endPt2[2] = 0;

    //glColor3f (0.3, 1.0, 1.0);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glTexCoord1f(0.0);
    glVertex3fv(endPt1);
    glTexCoord1f(1.0);
    glVertex3fv(endPt2);
    glEnd();
    glDisable(GL_TEXTURE_1D);

    glFlush();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texturi 1D");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(desen);
    glutMainLoop();
}

/* Acest cod sursa are rolul de a ilustra utilizarea matricelor.
De retinut:
- matricele pot fi definite ca atare in codul sursa (conventie: pe coloane);
- manevrarea stivelor de matrice;
Nu uitati!
- daca a 4-a coordonata este 0, e vorba de o directie
- daca a 4-a coordonata este !=0, e vorba de un punct; coordonatele sale pot fi obtinute impartind la a 4-a coord
*/
#include <gl/freeglut.h>

// varfurile
float p1[] = {-100, -100, 0, 1};
float p2[] = {100, -100, 0, 1};
float p3[] = {100, 100, 0, 1};
float p4[] = {-100, 100, 0, 1};

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-800.0, 800.0, -600.0, 600.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void desen(void) // ILUSTRARE MATRICE
{
    glLineWidth(6.0);

    // POLIGONUL INITIAL
    glColor3f(0.0, 1.0, 0.0); // poligonul initial este verde
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex4fv(p1);
    glVertex4fv(p2);
    glVertex4fv(p3);
    glVertex4fv(p4);
    glEnd();

    // TRANSLATIE
    glColor3f(0.0, 0.0, 1.0); // poligonul translatat este albastru
    glPushMatrix();
    glTranslatef(100.0, 150.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex4fv(p1);
    glVertex4fv(p2);
    glVertex4fv(p3);
    glVertex4fv(p4);
    glEnd();
    glPopMatrix(); // daca nu este apelat glPopMatrix, matr. translatie ramane in vf stivei

    // EXEMPLIFICARE MATRICE
    GLdouble mat[16]; // definire si initializare matrice
    GLint k;
    for (k = 0; k < 16; k++)
        mat[k] = 0.0;

    /* 1. Matrice de scalare  */
    mat[0] = 2.0;
    mat[5] = 0.5;
    mat[10] = 1.0, mat[15] = 1.0; // diagonala principala; poligonul este scalat

    /* 2. Scalare + translatie
    mat[0] = 2.0; mat[5] = 0.5; mat[10] = 1.0, mat[15]=1.0;
    mat[12] = 100.0; mat[13] = 150.0;
    */

    /* 3. Exemplul de matrice de la curs
    mat[0] = 2.0; mat[4] = 4.0; mat[8] = 0.0; mat[12] = 5.0;
    mat[1] = 3.0; mat[5] = -1.0; mat[9] = 0.0; mat[13] = -2.0;
    mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
    mat[3] = 0.0; mat[7] = 0.0; mat[11] = 0.0; mat[15] = 1.0;
     */

    /* 4. Transformare de forfecare (shear transform)
    mat[0] = 2.0; mat[5] = 0.5; mat[10] = 1.0, mat[15] = 1.0;
    mat[4] = 0.4;
    */

    /* 5. Ultima linie diferita de (0 0 0 1)
    mat[0] = 2.0; mat[4] = 4.0; mat[8] = 0.0; mat[12] = 5.0;
    mat[1] = 3.0; mat[5] = -1.0; mat[9] = 0.0; mat[13] = -2.0;
    mat[2] = 0.0; mat[6] = 0.0; mat[10] = 1.0; mat[14] = 0.0;
    mat[3] = 1.0; mat[7] = 1.0; mat[11] = 0.0; mat[15] = 40.0;
    */

    glMultMatrixd(mat); // inmultirea cu matricea
    glColor3f(1.0, 0.0, 0.0); // poligonul obtinut este desenat cu rosu
    glBegin(GL_POLYGON);
    glVertex4fv(p1);
    glVertex4fv(p2);
    glVertex4fv(p3);
    glVertex4fv(p4);
    glEnd();
    glPopMatrix();
    glLoadIdentity();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Transformari si matrice");
    init();
    glutDisplayFunc(desen);
    glutMainLoop();
}

/**
 * Laborator 3 / tema 3
 * Mihai Tuhari
 *
 * Mini sistem solar (soare, pamant, luna) cu rotatii si orbite.
 */
#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>

// Sizes of planets
const double SUN_SIZE = 50.0;
const double EARTH_SIZE = 30.0;
const double MOON_SIZE = 15.0;

// Distance between planets
const double EARTH_DISTANCE = 150.0; // From sun
const double MOON_DISTANCE = 50.0; // From earth

// Rotation speeds
const double SUN_ROTATION_SPEED = 0.5;
const double EARTH_SPEED = 0.2;
const double MOON_SPEED = 1.0;
const int SLOW_FACTOR = 20;

// Rotation angles (defaults)
static GLdouble sunAngle = 0.0;
static GLdouble earthAngle = 0.0;
static GLdouble moonAngle = 0.0;

// Star positions
const int NUM_STARS = 100;
GLfloat starPositions[NUM_STARS][2];

// Lists
GLuint sunList, earthList, moonList;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-400.0, 400.0, -300.0, 300.0);

    // Initialize random seed
    std::srand(std::time(0));

    // Generate random star positions
    for (int i = 0; i < NUM_STARS; ++i) {
        starPositions[i][0] = (std::rand() % 800) - 400.0f; // X position
        starPositions[i][1] = (std::rand() % 600) - 300.0f; // Y position
    }

    // Sun display list
    sunList = glGenLists(1);
    glNewList(sunList, GL_COMPILE);
    glColor3f(1.0, 1.0, 0.0); // Yellow Sun
    glBegin(GL_QUADS);
    glVertex2f(-SUN_SIZE / 2, -SUN_SIZE / 2);
    glVertex2f(SUN_SIZE / 2, -SUN_SIZE / 2);
    glVertex2f(SUN_SIZE / 2, SUN_SIZE / 2);
    glVertex2f(-SUN_SIZE / 2, SUN_SIZE / 2);
    glEnd();
    glEndList();

    // Earth display list
    earthList = glGenLists(1);
    glNewList(earthList, GL_COMPILE);
    glColor3f(0.0, 0.0, 1.0); // Blue Earth
    glBegin(GL_QUADS);
    glVertex2f(-EARTH_SIZE / 2, -EARTH_SIZE / 2);
    glVertex2f(EARTH_SIZE / 2, -EARTH_SIZE / 2);
    glVertex2f(EARTH_SIZE / 2, EARTH_SIZE / 2);
    glVertex2f(-EARTH_SIZE / 2, EARTH_SIZE / 2);
    glEnd();
    glEndList();

    // Moon display list
    moonList = glGenLists(1);
    glNewList(moonList, GL_COMPILE);
    glColor3f(0.5, 0.5, 0.5); // Gray Moon
    glBegin(GL_QUADS);
    glVertex2f(-MOON_SIZE / 2, -MOON_SIZE / 2);
    glVertex2f(MOON_SIZE / 2, -MOON_SIZE / 2);
    glVertex2f(MOON_SIZE / 2, MOON_SIZE / 2);
    glVertex2f(-MOON_SIZE / 2, MOON_SIZE / 2);
    glEnd();
    glEndList();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw stars
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; ++i) {
        glVertex2f(starPositions[i][0], starPositions[i][1]);
    }
    glEnd();

    // Sun - center with self-rotation
    glPushMatrix();
    glRotated(sunAngle, 0.0, 0.0, 1.0);
    glCallList(sunList);
    glPopMatrix();

    // Earth - orbiting the Sun
    glPushMatrix();
    glRotated(earthAngle, 0.0, 0.0, 1.0);
    glTranslated(EARTH_DISTANCE, 0.0, 0.0);
    glCallList(earthList);

    // Moon - orbiting the Earth
    glPushMatrix();
    glRotated(moonAngle, 0.0, 0.0, 1.0);
    glTranslated(MOON_DISTANCE, 0.0, 0.0);
    glCallList(moonList);
    glPopMatrix(); // pop Moon

    glPopMatrix(); // pop Earth

    glutSwapBuffers();
    glFlush();
}

void update() {
    sunAngle += SUN_ROTATION_SPEED / SLOW_FACTOR;
    if (sunAngle >= 360.0) sunAngle -= 360.0; // Reset

    earthAngle += EARTH_SPEED / SLOW_FACTOR;
    if (earthAngle >= 360.0) earthAngle -= 360.0; // Reset

    moonAngle += MOON_SPEED / SLOW_FACTOR;
    if (moonAngle >= 360.0) moonAngle -= 360.0; // Reset

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mihai Tuhari - Lab 3 / Punctul 3");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}

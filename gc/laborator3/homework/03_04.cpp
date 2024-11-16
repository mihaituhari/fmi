/**
 * Laborator 3 / tema 4
 * Mihai Tuhari
 *
 * Desenati un patrat centrat in origine, avand latura egala cu 30.
 * Utilizati apoi o scalare cu factori (2.0, 0.5) si o translatie de vector (100,100).
 *
 * Desenati, in plus, in acelasi desen (atentie la ordinea transformarilor!):
 *  • cu un amestec de culori ceea ce se obtine aplicand intai scalarea, apoi translatia
 *  • texturat ce se obtine aplicand intai translatia, apoi scalarea.
 */
#define STB_IMAGE_IMPLEMENTATION

#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "../libs/stb_image.h"

// Constants
const GLfloat SIDE_LENGTH = 30.0;
const std::string path = "/Volumes/mihai/dev/fmi/gc/laborator3/examples/";

// Texture variables
GLuint textureID;
int width, height, channels;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
}

void loadTexture(const std::string &path) {
    unsigned char *image = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if (!image) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        exit(1);
    }

    // Generate and bind texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

void display() {
    GLfloat half = SIDE_LENGTH / 2;

    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Original square
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2f(-half, -half);
    glVertex2f(half, -half);
    glVertex2f(half, half);
    glVertex2f(-half, half);
    glEnd();
    glPopMatrix();

    // 2. Apply (S o T) with gradient color
    glPushMatrix();
    glTranslatef(100.0, 100.0, 0.0);
    glScalef(2.0, 0.5, 1);
    glBegin(GL_QUADS);

    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(-half, -half);

    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(half, -half);

    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(half, half);

    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(-half, half);
    glEnd();
    glPopMatrix();

    // 3. Apply (T o S) with texture
    glPushMatrix();
    glScalef(2, 0.5, 1);
    glTranslatef(100, 100, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-half, -half);
    glTexCoord2f(1, 0);
    glVertex2f(half, -half);
    glTexCoord2f(1, 1);
    glVertex2f(half, half);
    glTexCoord2f(0, 1);
    glVertex2f(-half, half);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        gluOrtho2D(-200.0, 200.0, -200.0 * (GLfloat) h / (GLfloat) w, 200.0 * (GLfloat) h / (GLfloat) w);
    } else {
        gluOrtho2D(-200.0 * (GLfloat) w / (GLfloat) h, 200.0 * (GLfloat) w / (GLfloat) h, -200.0, 200.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mihai Tuhari - Lab 3 / Punctul 4");

    init();
    loadTexture(path + "text_smiley_face.png");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

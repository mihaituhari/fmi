/**
 * Laborator 3 / tema 5
 * Mihai Tuhari
 *
 * Adaugati o textura intr-unul din desenele realizate la o tema anterioara (se acorda 2p pentru un desen
 * "static", respectiv 3p pentru un desen "dinamic" animat).
 */
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include "../libs/stb_image.h"

// Constants
const std::string path = "/Volumes/mihai/dev/fmi/gc/laborator3/";

// Tilt animation variables
GLfloat tiltAngle = 0.0;
GLfloat tiltStep = 0.01;
GLfloat tiltMaxAngle = 10;

// Texture variables
GLuint textureID;
int width, height, channels;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
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

void renderTree(int x) {
    int yOffset = 5; // Offset de la marginea de jos
    int trunkWidth = 20; // Latime trunchi
    int trunkHeight = 50; // Inaltime trunchi
    int triangleHeight = 60; // Inaltime triunghi coroana

    // Draw trunk (brown)
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_QUADS);
    glVertex2i(x - trunkWidth / 2, yOffset);
    glVertex2i(x + trunkWidth / 2, yOffset);
    glVertex2i(x + trunkWidth / 2, yOffset + trunkHeight);
    glVertex2i(x - trunkWidth / 2, yOffset + trunkHeight);
    glEnd();

    // Draw canopy (textured green part)
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Apply tilt animation
    glPushMatrix();
    glTranslatef(x, yOffset + trunkHeight, 0.0f); // Move to pivot point
    glRotatef(tiltAngle, 0.0f, 0.0f, 1.0f); // Rotate around pivot
    glTranslatef(-x, -(yOffset + trunkHeight), 0.0f); // Move back

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);
    glVertex2i(x, yOffset + trunkHeight + triangleHeight); // Top of the triangle
    glTexCoord2f(0.0, 0.0);
    glVertex2i(x - trunkWidth, yOffset + trunkHeight); // Bottom-left
    glTexCoord2f(1.0, 0.0);
    glVertex2i(x + trunkWidth, yOffset + trunkHeight); // Bottom-right
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawDancingForest() {
    int treeSpacing = 50;

    for (int x = 20; x < 800; x += treeSpacing) {
        renderTree(x);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawDancingForest();

    glFlush();
}

void update() {
    tiltAngle += tiltStep;

    // Reverse tilt
    if (tiltAngle > tiltMaxAngle || tiltAngle < -tiltMaxAngle) {
        tiltStep = -tiltStep;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mihai Tuhari - Lab 3 / Punctul 5");

    init();
    loadTexture(path + "homework/texture-pine.png");

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMainLoop();

    return 0;
}

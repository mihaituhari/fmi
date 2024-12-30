/**
 * Project 1 - simplified scene
 *
 * @author Mihai Tuhari
 * @date November 2024
 */
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include "libs/stb_image.h"

// Globals
const int windowWidth = 1200;
const int windowHeight = 600;
const double PI = 3.141592653589793; // For circles

// Texture variables
GLuint textureTree;
const std::string texturePath = "/Volumes/mihai/dev/fmi/gc/proiect1/textures/";
int width, height, channels;

// Road elements
GLfloat roadDividerWidth = 5;
GLint treeSpacing = 120;

// Scene variables
GLfloat animationInterval = 16; // ~60 FPS (= 1000 / 60)
GLfloat sceneSpeed = 3.6;
GLfloat sceneOffset = 0;

// Load a texture from file
void loadTexture(const std::string &path, GLuint &textureID) {
    stbi_set_flip_vertically_on_load(1); // Flip the image vertically on load
    unsigned char *image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!image) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        exit(1);
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

// Draw the moving trees on the side of the road
void drawTrees() {
    int yOffset = 450;
    int rectWidth = 39 * 2.5;
    int rectHeight = 32 * 2.5;

    int numTrees = (windowWidth / treeSpacing) + 2; // Extra trees for smooth transition

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTree);

    for (int i = 0; i < numTrees; ++i) {
        GLfloat treeX = (i * treeSpacing) + fmod(sceneOffset, treeSpacing);

        glPushMatrix();
        glTranslatef(treeX, 0, 0);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); // Bottom-left
        glVertex2i(-rectWidth / 2, yOffset);

        glTexCoord2f(1.0, 0.0); // Bottom-right
        glVertex2i(rectWidth / 2, yOffset);

        glTexCoord2f(1.0, 1.0); // Top-right
        glVertex2i(rectWidth / 2, yOffset + rectHeight);

        glTexCoord2f(0.0, 1.0); // Top-left
        glVertex2i(-rectWidth / 2, yOffset + rectHeight);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
}


// Draw asphalt road with moving dividers
void drawRoad() {
    // Asphalt
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0, 200);
    glVertex2f(windowWidth, 200);
    glVertex2f(windowWidth, 400);
    glVertex2f(0, 400);
    glEnd();

    // Road divider (moving vertical lines)
    glColor3f(1, 1, 1);

    for (GLfloat x = sceneOffset; x < windowWidth; x += 50) {
        glBegin(GL_QUADS);
        glVertex2f(x, 300 - roadDividerWidth); // Center of the road
        glVertex2f(x + 30, 300 - roadDividerWidth);
        glVertex2f(x + 30, 300 + roadDividerWidth);
        glVertex2f(x, 300 + roadDividerWidth);
        glEnd();
    }
}

void init() {
    glClearColor(0, 0.6, 0, 1);  // Green background, grass
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRoad();

    // Enable blending for trees and cars
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawTrees();

    glDisable(GL_BLEND);
    glutSwapBuffers();
}

void update(int value) {
    sceneOffset -= sceneSpeed;

    glutPostRedisplay();
    glutTimerFunc(animationInterval, update, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Mihai Tuhari - Project 1 scene only");

    init();

    loadTexture(texturePath + "tree.png", textureTree);

    glutDisplayFunc(display);
    glutTimerFunc(animationInterval, update, 0);
    glutMainLoop();

    return 0;
}

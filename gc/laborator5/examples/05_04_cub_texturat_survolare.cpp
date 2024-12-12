
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stdlib.h>
#include <gl/freeglut.h>
#include <math.h>
#include <stdlib.h>  
#include <cstdlib> 
#include "stb_image.h"

float PI = 3.141592;
// punctul de referinta (centrul sistemului de coordonate de modelare)
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
// initializare unghiuri
float alpha = 0, beta = 0, dist = 15.0f;
// observator
float Obsx, Obsy, Obsz;

void reshapeAndProjection(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w  / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60.0f, ratio, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GLfloat texpts[2][2][2] = { {{1.0, 1.0}, {1.0, 0.0}},
            {{0.0, 1.0}, {0.0, 0.0}} };

#define	imageWidth 64
#define	imageHeight 64
GLubyte image[3 * imageWidth * imageHeight];
GLuint texture1;

void drawCube()
{
    glBegin(GL_QUADS);
    // Fata de jos
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Fata de sus
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Fata lateral dreapta
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

    // Fata lateral stanga
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);

    // Fata frontala
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

    // Fata din spate
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
}

void LoadTexture(void)
{
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    unsigned char* image = stbi_load("/Volumes/mihai/dev/fmi/gc/laborator5/examples/text_smiley_face.png", &width, &height, &channels, STBI_rgb);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
}

void init(void)
{
    glClearColor(0.6, 0.9, 0.95, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    // Pozitia observatorului
    Obsx = Refx + dist * cos(alpha) * cos(beta);
    Obsy = Refy + dist * cos(alpha) * sin(beta);
    Obsz = Refz + dist * sin(alpha);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Obsx, Obsy, Obsz, Refx, Refy, Refz, 0.0f, 0.0f, 1.0f);;
    
    glEnable(GL_TEXTURE_2D);
    LoadTexture();
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.8, 0.7, 1.0);
    glScalef(3.0, 2.0, 1.0);
    drawCube();
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
    glFlush();

}

// schimbare pozitie observator
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
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutMainLoop();
    return 0;
}

#include <cstdio>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../../shaders/include/loadShaders.h"

// Function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the display
    glFlush(); // Ensure all commands are executed
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1100, 100);
    glutInitWindowSize(600, 400);
    glutCreateWindow("GL_VERSION");

    // Initialize GLEW
    glewExperimental = GL_TRUE;  // Required for some drivers
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    printf("OpenGL version supported by this platform: (%s) \n", glGetString(GL_VERSION));
    printf("GLSL version supported by this platform: (%s) \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glutDisplayFunc(display);
    glutMainLoop();
}

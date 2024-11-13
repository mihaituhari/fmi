#include <cstdio>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../include/loadShaders.h"

GLuint
        VaoId,
        VboId,
        ColorBufferId,
        ProgramId;


void CreateVBO(void) {
    // varfurile
    GLfloat Vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f
    };

    // culorile, ca atribute ale varfurilor
    GLfloat Colors[] = {
            1.0f, 0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f, 1.0f,
    };

    // se creeaza un buffer nou
    glGenBuffers(1, &VboId);

    // este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VboId);

    // varfurile sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);
    // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    //
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // un nou buffer, pentru culoare
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    // atributul 1 =  culoare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void DestroyVBO(void) {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void) {
    ProgramId = LoadShaders("example.vert", "example.frag");
    glUseProgram(ProgramId);
}

void DestroyShaders(void) {
    glDeleteProgram(ProgramId);
}

void Initialize(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // culoarea de fond a ecranului
    CreateVBO();
    CreateShaders();
}

void RenderFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Functiile de desenare
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    glFlush();
}

void Cleanup(void) {
    DestroyShaders();
    DestroyVBO();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
    glutInitWindowSize(600, 600); //dimensiunile ferestrei


    // Create window
    glutCreateWindow("Grafica pe calculator - primul exemplu"); // titlul ferestrei

    // Initialize GLEW
    glewExperimental = GL_TRUE;  // Required for some drivers
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    // Print OpenGL info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));

    Initialize();
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);
    glutMainLoop();
}

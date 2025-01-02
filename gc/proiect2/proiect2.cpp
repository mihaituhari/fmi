#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GL/freeglut.h>
#include "libs/stb_image.h"

// Camera position
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0.05f;
float beta = -1.3f;
float dist = 26.0f;
float Obsx, Obsy, Obsz;

// Fog flag
bool fog = false;

// Road elements
float roadOffset = 0.0f;
const float ROAD_SPEED = 0.1f;
const float ROAD_WIDTH = 10.0f;
const float ROAD_LENGTH = 800.0f;

// Moon texture
GLuint textureMoon;
const std::string texturePath = "/Volumes/mihai/dev/fmi/gc/proiect2/textures/";
int width, height, channels;

// Tree positions
struct TreePosition {
    float x, y, z;
    float scaleFactor;
};

std::vector<TreePosition> treePositions;

// Function to load textures
void loadTexture(const std::string &path, GLuint &textureID) {
    stbi_set_flip_vertically_on_load(1);
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

void drawMoon() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureMoon);

    GLfloat moonAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Bright white
    GLfloat moonDiffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; // Increased diffuse brightness
    GLfloat moonSpecular[] = {2.0f, 2.0f, 2.0f, 1.0f}; // High specular reflection
    GLfloat moonShininess[] = {128.0f}; // Very shiny surface

    glMaterialfv(GL_FRONT, GL_AMBIENT, moonAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moonDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moonSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, moonShininess);

    glPushMatrix();
    glTranslatef(15.0f, 30.0f, 15.0f);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, 3.0f, 30, 30);
    gluDeleteQuadric(quad);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void initTreePositions() {
    float spacing = 3.5f;
    int numTrees = (int) (ROAD_LENGTH / spacing) + 1;

    for (int i = 0; i < numTrees; i++) {
        TreePosition tree;

        tree.x = -ROAD_WIDTH / 2 - 2.0f;  // Left side of road
        tree.y = i * spacing; // Evenly spaced along the road
        tree.z = 0.0f;

        // Random scale factor (e.g., between 0.8 and 1.2)
        tree.scaleFactor = 0.8f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
        treePositions.push_back(tree);
    }
}

void drawRoad() {
    // Road surface
    glDisable(GL_LIGHTING);
    glPushMatrix();

    // Main road surface (gray)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3f(-ROAD_WIDTH / 2, -ROAD_LENGTH / 2, -3.0f);
    glVertex3f(ROAD_WIDTH / 2, -ROAD_LENGTH / 2, -3.0f);
    glVertex3f(ROAD_WIDTH / 2, ROAD_LENGTH / 2, -3.0f);
    glVertex3f(-ROAD_WIDTH / 2, ROAD_LENGTH / 2, -3.0f);
    glEnd();

    // Road divider lines (white)
    glColor3f(1.0f, 1.0f, 1.0f);

    float lineSpacing = 5.0f;
    float offset = 0;

    for (float z = -ROAD_LENGTH / 2; z < ROAD_LENGTH / 2; z += lineSpacing) {
        float adjustedZ = z + roadOffset + offset;

        // Wrap the position if it goes beyond the road length
        if (adjustedZ > ROAD_LENGTH / 2) {
            adjustedZ -= ROAD_LENGTH;
        }
        if (adjustedZ < -ROAD_LENGTH / 2) {
            adjustedZ += ROAD_LENGTH;
        }

        glBegin(GL_QUADS);
        glVertex3f(-0.15f, adjustedZ, -2.99f);
        glVertex3f(0.15f, adjustedZ, -2.99f);
        glVertex3f(0.15f, adjustedZ + 3.0f, -2.99f);
        glVertex3f(-0.15f, adjustedZ + 3.0f, -2.99f);
        glEnd();
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawTree(float scaleFactor) {
    // Set tree material (green)
    GLfloat tree_ambient[] = {0.0f, 0.2f, 0.0f, 1.0f};
    GLfloat tree_diffuse[] = {0.0f, 0.6f, 0.0f, 1.0f};
    GLfloat tree_specular[] = {0.0f, 0.1f, 0.0f, 1.0f};
    GLfloat tree_shininess[] = {10.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, tree_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tree_shininess);

    // Apply the consistent scaling factor
    glPushMatrix();
    glScalef(scaleFactor, scaleFactor, scaleFactor);

    // Draw bottom cone
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glutSolidCone(1.5, 3.0, 12, 20);
    glPopMatrix();

    // Draw middle cone
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);
    glutSolidCone(1.2, 2.5, 12, 20);
    glPopMatrix();

    // Draw top cone
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glutSolidCone(0.9, 2.0, 12, 20);
    glPopMatrix();

    // Set trunk material (brown)
    GLfloat trunk_ambient[] = {0.4f, 0.2f, 0.0f, 1.0f};  // Brown ambient
    GLfloat trunk_diffuse[] = {0.6f, 0.3f, 0.1f, 1.0f};  // Brown diffuse

    glMaterialfv(GL_FRONT, GL_AMBIENT, trunk_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, trunk_diffuse);

    // Draw trunk
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f);
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.4f, 0.4f, 1.0f, 20, 20);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPopMatrix(); // Undo scaling
}

void drawTrees() {
    for (const auto &pos: treePositions) {
        for (int set = -1; set <= 1; set++) {
            float yOffset = pos.y + roadOffset + (set * ROAD_LENGTH);

            if (yOffset >= -ROAD_LENGTH / 2 && yOffset <= ROAD_LENGTH * 0.5) {
                glPushMatrix();
                glTranslatef(pos.x, yOffset, pos.z);
                drawTree(pos.scaleFactor);
                glPopMatrix();
            }
        }
    }
}

void reshapeAndProjection(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float) w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
}

void setupLighting() {
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT1);   // Enable the moonlight as the primary light source

    // Enhanced moonlight properties (bright white light)
    GLfloat moonLightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Stronger ambient light
    GLfloat moonLightDiffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; // Intense diffuse light
    GLfloat moonLightSpecular[] = {2.0f, 2.0f, 2.0f, 1.0f}; // Bright specular highlights
    GLfloat moonLightPosition[] = {15.0f, 30.0f, 15.0f, 1.0f}; // Position near the moon

    glLightfv(GL_LIGHT1, GL_AMBIENT, moonLightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, moonLightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, moonLightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, moonLightPosition);
}

void setupFog() {
    GLfloat fogColor[] = {0.5, 0.5, 0.5, 1.0}; // Fog color: light gray

    glFogi(GL_FOG_MODE, GL_EXP); // Fog mode: exponential
    glFogfv(GL_FOG_COLOR, fogColor); // Set fog color
    glFogf(GL_FOG_DENSITY, 0.05f); // Reduced fog density (was 0.25)
    glHint(GL_FOG_HINT, GL_NICEST); // High-quality fog rendering
    glFogf(GL_FOG_START, 10.0f); // Fog starts farther away
    glFogf(GL_FOG_END, 100.0f); // Fog ends much farther away
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update camera position
    Obsx = Refx + dist * cos(alpha) * cos(beta);
    Obsy = Refy + dist * cos(alpha) * sin(beta);
    Obsz = Refz + dist * sin(alpha);

    glLoadIdentity();
    gluLookAt(Obsx, Obsy, Obsz, Refx, Refy, Refz, 0.0f, 0.0f, 1.0f);

    setupLighting();
    setupFog();

    drawRoad();
    drawMoon();
    drawTrees();

    glutSwapBuffers();
}

void setSceneColor() {
    if (fog) {
        glClearColor(0.5, 0.5, 0.5, 1.0); // Ceata
    } else {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dusk-like background color
    }
}

void update(int value) {
    roadOffset -= ROAD_SPEED;
    if (roadOffset < -ROAD_LENGTH) {
        roadOffset += ROAD_LENGTH;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
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
            dist -= 0.5;
            break;
        case '-':
            dist += 0.5;
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
            break;

        // Default camera
        case '1':
            alpha = 0.05f;
            beta = -1.3f;
            dist = 26.0f;
            break;

        // Behind trees camera
        case '2':
            alpha = 22.05f;
            beta = 1.0f;
            dist = 26.0f;
            break;

        // Top view camera
        case '3':
            alpha = 1.57f;
            beta = 0.0f;
            dist = 26.0f;
            break;

        // Front view camera
        case '4':
            alpha = 0.0f;
            beta = -1.57f;
            dist = 26.0f;
            break;

        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mihai Tuhari - 3D Project");

    initTreePositions();

    loadTexture(texturePath + "moon.jpg", textureMoon);

    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    glutTimerFunc(16, update, 0);

    setSceneColor();
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}

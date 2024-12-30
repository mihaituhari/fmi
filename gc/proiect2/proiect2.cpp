#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <cstdlib> // For random numbers
#include <ctime>   // For seeding random number generator
#include "libs/stb_image.h"

float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
// Modified initial camera angles for isometric-like view
float alpha = 0.4f;  // -45 degrees in radians for looking down
float beta = -0.6f;    // 45 degrees in radians for side angle
float dist = 30.0f;        // Increased distance to see more of the scene
float Obsx, Obsy, Obsz;

bool fog = false;
float roadOffset = 0.0f;
const float ROAD_SPEED = 0.1f;
const float ROAD_WIDTH = 10.0f;
const float ROAD_LENGTH = 800.0f;

GLuint textureMoon; // Texture for the moon
const std::string texturePath = "/Volumes/mihai/dev/fmi/gc/proiect2/textures/";
int width, height, channels;

struct TreePosition {
    float x, y, z;
    float scaleFactor; // Random scale factor for consistent tree size
};

std::vector<TreePosition> treePositions;

// Function to load textures
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

void drawMoon() {
    glEnable(GL_TEXTURE_2D); // Enable texture mapping
    glBindTexture(GL_TEXTURE_2D, textureMoon);

    // Enhanced moon material properties
    GLfloat moonAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Bright white
    GLfloat moonDiffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; // Increased diffuse brightness
    GLfloat moonSpecular[] = {2.0f, 2.0f, 2.0f, 1.0f}; // High specular reflection
    GLfloat moonShininess[] = {128.0f};               // Very shiny surface

    glMaterialfv(GL_FRONT, GL_AMBIENT, moonAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moonDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moonSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, moonShininess);

    // Draw the moon as a textured sphere
    glPushMatrix();
    glTranslatef(20.0f, 20.0f, 15.0f); // Position the moon
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);  // Enable texture mapping for the sphere
    gluSphere(quad, 3.0f, 30, 30);    // Radius 3.0, 30 slices, 30 stacks
    gluDeleteQuadric(quad);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D); // Disable texture mapping
}

void initTreePositions() {
    float spacing = 3.5f;  // Reduced spacing between trees
    int numTrees = (int)(ROAD_LENGTH / spacing) + 1;  // Calculate number of trees needed

    for (int i = 0; i < numTrees; i++) {
        TreePosition tree;
        tree.x = -ROAD_WIDTH / 2 - 2.0f;  // Left side of road
        tree.y = i * spacing;            // Evenly spaced along the road
        tree.z = 0.0f;

        // Assign a random scale factor (e.g., between 0.8 and 1.2)
        tree.scaleFactor = 0.8f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));

        treePositions.push_back(tree);
    }
}

void reshapeAndProjection(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 500.0f);  // Adjusted FOV to 45 degrees
    glMatrixMode(GL_MODELVIEW);
}

void drawRoad() {
    // Road surface
    glDisable(GL_LIGHTING);
    glPushMatrix();

    // Main road surface (gray)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3f(-ROAD_WIDTH/2, -ROAD_LENGTH/2, -3.0f);
    glVertex3f(ROAD_WIDTH/2, -ROAD_LENGTH/2, -3.0f);
    glVertex3f(ROAD_WIDTH/2, ROAD_LENGTH/2, -3.0f);
    glVertex3f(-ROAD_WIDTH/2, ROAD_LENGTH/2, -3.0f);
    glEnd();

    // Road divider lines (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    float lineSpacing = 5.0f;

    // Draw two sets of lines to ensure seamless looping
    for (int set = 0; set < 2; set++) {
        float offset = set * ROAD_LENGTH;
        for (float z = -ROAD_LENGTH/2; z < ROAD_LENGTH/2; z += lineSpacing) {
            float adjustedZ = z + roadOffset + offset;

            // Wrap the position if it goes beyond the road length
            if (adjustedZ > ROAD_LENGTH/2) {
                adjustedZ -= ROAD_LENGTH;
            }
            if (adjustedZ < -ROAD_LENGTH/2) {
                adjustedZ += ROAD_LENGTH;
            }

            glBegin(GL_QUADS);
            glVertex3f(-0.15f, adjustedZ, -2.99f);
            glVertex3f(0.15f, adjustedZ, -2.99f);
            glVertex3f(0.15f, adjustedZ + 3.0f, -2.99f);
            glVertex3f(-0.15f, adjustedZ + 3.0f, -2.99f);
            glEnd();
        }
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void drawChristmasTree(float scaleFactor) {
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
    GLUquadricObj* cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.4f, 0.4f, 1.0f, 20, 20);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPopMatrix(); // Undo scaling
}

void setupLighting() {
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT1);   // Enable the moonlight as the primary light source

    // Enhanced moonlight properties (bright white light)
    GLfloat moonLightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Stronger ambient light
    GLfloat moonLightDiffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; // Intense diffuse light
    GLfloat moonLightSpecular[] = {2.0f, 2.0f, 2.0f, 1.0f}; // Bright specular highlights
    GLfloat moonLightPosition[] = {20.0f, 20.0f, 15.0f, 1.0f}; // Position near the moon

    glLightfv(GL_LIGHT1, GL_AMBIENT, moonLightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, moonLightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, moonLightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, moonLightPosition);
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

    // Draw the moon
    drawMoon();

    // Draw the road
    drawRoad();

    // Draw trees with seamless wrapping
    for (const auto& pos : treePositions) {
        for (int set = -1; set <= 1; set++) {
            float yOffset = pos.y + roadOffset + (set * ROAD_LENGTH);
            if (yOffset >= -ROAD_LENGTH / 2 && yOffset <= ROAD_LENGTH * 1.5) {
                glPushMatrix();
                glTranslatef(pos.x, yOffset, pos.z);
                drawChristmasTree(pos.scaleFactor);
                glPopMatrix();
            }
        }
    }

    glutSwapBuffers();
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
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Animated Road Scene with Moonlight");

    srand(static_cast<unsigned int>(time(0))); // Seed random generator
    initTreePositions();

    // Load the moon texture
    loadTexture(texturePath + "moon.jpg", textureMoon);

    glutReshapeFunc(reshapeAndProjection);
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    glutTimerFunc(16, update, 0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dusk-like background color

    glutMainLoop();
    return 0;
}

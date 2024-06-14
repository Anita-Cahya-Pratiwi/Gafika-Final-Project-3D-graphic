#include <GL/glut.h>
#include "imageloader.h"
#include <cmath>

// Global variables for texture
GLuint textureIdkubus;
GLuint textureIdtop;
GLuint textureIdbalok;
GLuint textureIdkaki;
GLuint textureIdbola;

GLuint textureIddinding;
GLuint textureIddinding2;
GLuint textureIdlantai;

// Variables for camera position and orientation
float cameraX = -15.0f, cameraY = 10.0f, cameraZ = 30.0f;
float pitch = 0.0f, yaw = -45.0f;  // menghadap -z

// Variables to store the last mouse position
int lastMouseX, lastMouseY;
bool firstMouse = true;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Load texture kubus
    Image* kubusimage = loadBMP("kardus.bmp");

    //colors(image); //pewarnaan jika tanpa konversi

    glGenTextures(1, &textureIdkubus);
    glBindTexture(GL_TEXTURE_2D, textureIdkubus);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, kubusimage->width, kubusimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, kubusimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //atas kardus
    Image* topimage = loadBMP("top.bmp");

    glGenTextures(1, &textureIdtop);
    glBindTexture(GL_TEXTURE_2D, textureIdtop);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, topimage->width, topimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, topimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     // Load texture balok papan meja
    Image* balokimage = loadBMP("kayu.bmp");

    glGenTextures(1, &textureIdbalok);
    glBindTexture(GL_TEXTURE_2D, textureIdbalok);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, balokimage->width, balokimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, balokimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 // Load texture balok kaki meja
    Image* kakiimage = loadBMP("kayu.bmp");

    glGenTextures(1, &textureIdkaki);
    glBindTexture(GL_TEXTURE_2D, textureIdkaki);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, kakiimage->width, kakiimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, kakiimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 // Load texture lantai
    Image* lantaiimage = loadBMP("floor2.bmp");

    glGenTextures(1, &textureIdlantai);
    glBindTexture(GL_TEXTURE_2D, textureIdlantai);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lantaiimage->width, lantaiimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, lantaiimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture dinding
    Image* dindingimage = loadBMP("bigwall.bmp");

    glGenTextures(1, &textureIddinding);
    glBindTexture(GL_TEXTURE_2D, textureIddinding);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dindingimage->width, dindingimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, dindingimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     // Load texture dinding2
    Image* dinding2image = loadBMP("dindingpintu.bmp");

    glGenTextures(1, &textureIddinding2);
    glBindTexture(GL_TEXTURE_2D, textureIddinding2);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dinding2image->width, dinding2image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, dinding2image->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //bola
    Image* bolaimage = loadBMP("bulan.bmp");

    glGenTextures(1, &textureIdbola);
    glBindTexture(GL_TEXTURE_2D, textureIdbola);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bolaimage->width, bolaimage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, bolaimage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete balokimage;
    delete kubusimage;
    delete kakiimage;
    delete topimage;
    delete lantaiimage;
    delete dindingimage;
    delete bolaimage;
}

void ambientLight(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightPosition[] = {15.0f, 15.0f, 15.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


void sourceLight(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //posisi sumber cahaya
    GLfloat light_position[] = {15.0, 15.0, 15.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //warna dan sifat material objek
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0}; // Warna ambient objek
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0}; // Warna specular objek

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0); // Tingkat kehalusan objek

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}


void drawSphere(float radius, int slices, int stacks) {
    glBindTexture(GL_TEXTURE_2D, textureIdbola);
    for (int i = 0; i <= stacks; ++i) {
        float V = i / (float) stacks;
        float phi = V * M_PI;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float U = j / (float) slices;
            float theta = U * (M_PI * 2);

            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);

            glTexCoord2f(U, V);
            glNormal3f(x, y, z);
            glVertex3f(x * radius, y * radius, z * radius);

            float nextPhi = (V + 1.0 / stacks) * M_PI;
            float nx = cosf(theta) * sinf(nextPhi);
            float ny = cosf(nextPhi);
            float nz = sinf(theta) * sinf(nextPhi);

            glTexCoord2f(U, V + 1.0 / stacks);
            glNormal3f(nx, ny, nz);
            glVertex3f(nx * radius, ny * radius, nz * radius);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Calculate camera direction based on pitch and yaw
    float frontX = cosf(pitch) * cosf(yaw);
    float frontY = sinf(pitch);
    float frontZ = cosf(pitch) * sinf(yaw);
    float cameraFront[] = {frontX, frontY, frontZ};

    gluLookAt(cameraX, cameraY, cameraZ,
              cameraX + cameraFront[0], cameraY + cameraFront[1], cameraZ + cameraFront[2],
              0.0, 1.0, 0.0);

    ambientLight();
    sourceLight();

    //bola
    drawSphere(3.0f, 20, 20);
    glTranslatef(5.0f, 2.0f, 10.0f); //koordinat

    //KUBUS
    glBindTexture(GL_TEXTURE_2D, textureIdkubus);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);

    // Left
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);

    // Right
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -1.0);


    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 1.0);

    glEnd();


    // Top
    glBindTexture(GL_TEXTURE_2D, textureIdtop);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
    glEnd();


    //BALOK
    glBindTexture(GL_TEXTURE_2D, textureIdbalok);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.0, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.0, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -1.5, 2.5);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.5, -2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.0, -2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -1.5, -2.5);

    // kanan
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(5.0, -1.0, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -1.0, -2.5);

    // kiri
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.0, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -1.0, -2.5);

    // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.0, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.0, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -1.0, -2.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -1.5, -2.5);

    glEnd();


    //KAKI1
    glBindTexture(GL_TEXTURE_2D, textureIdkaki);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -1.5, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, -2.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, -2.0);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -1.5, -2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, -2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, -2.5);

    // kanan
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(5.0, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -5.0, -2.5);

    // kiri
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(4.5, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(4.5, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, -2.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -5.0, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, -2.5);

    glEnd();

    //KAKI2
    glBindTexture(GL_TEXTURE_2D, textureIdkaki);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -1.5, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, -2.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, -2.0);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -1.5, -2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, -2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, -2.5);

    // kiri
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -5.0, -2.5);

    // kanan
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-4.5, -1.5, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-4.5, -1.5, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, -2.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -5.0, -2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -5.0, -2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, -2.5);

    glEnd();

    //KAKI3
    glBindTexture(GL_TEXTURE_2D, textureIdkaki);

    glBegin(GL_QUADS);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -1.5, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, 2.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, 2.0);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -1.5, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, 2.5);

    // kiri
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -1.5, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -5.0, 2.5);

    // kanan
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-4.5, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-4.5, -1.5, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, 2.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-4.5, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -5.0, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, -5.0, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-4.5, -5.0, 2.5);

    glEnd();

    //KAKI4
    glBindTexture(GL_TEXTURE_2D, textureIdkaki);

    glBegin(GL_QUADS);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -1.5, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, 2.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, 2.0);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -1.5, 2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, 2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, 2.5);

    // kanan
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(5.0, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.5, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -5.0, 2.5);

    // kiri
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(4.5, -1.5, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(4.5, -1.5, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, 2.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(4.5, -5.0, 2.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -5.0, 2.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -5.0, 2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(4.5, -5.0, 2.5);

    glEnd();

    //LANTAI
    glBindTexture(GL_TEXTURE_2D, textureIdlantai);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-15.0, -5.0, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.0, 15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, -5.5, 15.0);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -1.5, -2.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -1.0, -2.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -1.0, -2.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(5.0, -1.5, -2.5);


    // kiri
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.0, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-15.0, -5.5, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.0, -5.0, -15.0);

    // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.0, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.0, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.0, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.0, -5.0, -15.0);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.5, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.0, -5.5, -15.0);

    glEnd();

    //DINDING1
    glBindTexture(GL_TEXTURE_2D, textureIddinding);

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.5, -15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-15.0, 15.0, -15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, 15.0, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, -5.5, -15.0);

    // Back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, -5.5, -15.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(-15.0, 15.0, -15.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, 15.0, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, -5.5, -15.5);

    // kanan
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.0, 15.0, -15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, -15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.5, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, 15.0, -15.5);

    // kiri
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, 15.0, -15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-15.0, -5.5, -15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-15.0, -5.5, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.0, 15.0, -15.5);

    // Top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.0, 15.0, -15.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, 15.0, -15.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, 15.0, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.0, 15.0, -15.0);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15.5, -5.5, -15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, -15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.5, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-15.5, -5.5, -15.0);

    glEnd();


     //DINDING2
    glBindTexture(GL_TEXTURE_2D, textureIddinding2);

    glBegin(GL_QUADS);

    // Kanan
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, 15.0, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, 15.0, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, -5.5, -15.0);

    // Kiri
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.5, -5.5, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.5, 15.0, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.5, 15.0, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.5, -5.5, -15.5);

    // Depan
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.0, 15.0, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.5, -5.5, 15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.5, 15.0, 15.0);

    // Belakang
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.0, 15.0, -15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, -15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.5, -5.5, -15.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.5, 15.0, -15.0);

    // Top
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.0, 15.0, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.5, 15.0, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.5, 15.0, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.0, 15.0, -15.5);

    // Bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15.5, -5.5, 15.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(15.0, -5.5, 15.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(15.0, -5.5, -15.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(15.5, -5.5, -15.5);

    glEnd();


    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void handleKeypress(unsigned char key, int x, int y) {
    float step = 0.5f;
    switch (key) {
        case 'w': {
            cameraX += step * cosf(pitch) * cosf(yaw);
            cameraY += step * sinf(pitch);
            cameraZ += step * cosf(pitch) * sinf(yaw);
            break;
        }
        case 's': {
            cameraX -= step * cosf(pitch) * cosf(yaw);
            cameraY -= step * sinf(pitch);
            cameraZ -= step * cosf(pitch) * sinf(yaw);
            break;
        }
        case 'a': {
            // Vector perpendicular to the yaw vector
            float strafeX = -sinf(yaw);
            float strafeZ = cosf(yaw);
            cameraX -= step * strafeX;
            cameraZ -= step * strafeZ;
            break;
        }
        case 'd': {
            // Vector perpendicular to the yaw vector
            float strafeX = -sinf(yaw);
            float strafeZ = cosf(yaw);
            cameraX += step * strafeX;
            cameraZ += step * strafeZ;
            break;
        }

        case 'q': {
            cameraY += step;
            break;
        }
        case 'e': {
            cameraY -= step;
            break;
        }

        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void handleMouseMotion(int x, int y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    float xoffset = x - lastMouseX;
    float yoffset = lastMouseY - y; //ke atas posy
    lastMouseX = x;
    lastMouseY = y;

    float sensitivity = 0.005f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // X-axis nilai
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3 World of Abandoned Room");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutPassiveMotionFunc(handleMouseMotion);
    glutMainLoop();
    return 0;
}

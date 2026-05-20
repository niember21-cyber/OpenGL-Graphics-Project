
#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float angleRotation = 0.0f;

// Real RGB Colors
const float PEPSI_RED[] = {0.89f, 0.16f, 0.20f};
const float PEPSI_BLUE[] = {0.00f, 0.24f, 0.67f};
const float WHITE[] = {1.0f, 1.0f, 1.0f};
const float EU_BLUE[] = {0.00f, 0.20f, 0.60f};
const float EU_GOLD[] = {1.0f, 0.80f, 0.0f};

void init() {
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

// POINT primitive
void drawPoint() {
    glPointSize(6);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2f(0.0f, 0.0f);
    glEnd();
}

// LINE primitive
void drawLine() {
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(0.8f, 0.0f);
    glEnd();
}

void drawCircle(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void drawPepsiLogo() {

    // White base circle
    drawCircle(0.6f, 1,1,1);

    // Red upper part
    glColor3fv(PEPSI_RED);
    glBegin(GL_POLYGON);
    for(int i=0; i<=180; i++) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(0.6f*cos(theta), 0.6f*sin(theta));
    }
    glVertex2f(0.6f,0.0f);
    glVertex2f(-0.6f,0.0f);
    glEnd();

    // Blue lower part
    glColor3fv(PEPSI_BLUE);
    glBegin(GL_POLYGON);
    for(int i=180; i<=360; i++) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(0.6f*cos(theta), 0.6f*sin(theta));
    }
    glVertex2f(0.6f,0.0f);
    glVertex2f(-0.6f,0.0f);
    glEnd();

    // White wave
    glColor3fv(WHITE);
    glBegin(GL_POLYGON);
    for(float x=-0.6f; x<=0.6f; x+=0.01f) {
        float y = 0.08f * sin(6*x);
        glVertex2f(x,y+0.05f);
    }
    for(float x=0.6f; x>=-0.6f; x-=0.01f) {
        float y = 0.08f * sin(6*x);
        glVertex2f(x,y-0.05f);
    }
    glEnd();

    drawPoint();
    drawLine();

    glColor3f(1,1,1);
    drawText("PEPSI", -0.12f, -0.9f);
}

void drawStar(float x, float y, float radius) {
    glColor3fv(EU_GOLD);

    glBegin(GL_TRIANGLE_FAN);

    for(int i=0; i<=10; i++) {
        float angle = i * 3.14159f / 5.0f;
        float r = (i % 2 == 0) ? radius : radius/2;

        glVertex2f(
            x + cos(angle - 3.14159f/2) * r,
            y + sin(angle - 3.14159f/2) * r
        );
    }

    glEnd();
}

void drawEUFlag() {

    // Background
    glColor3fv(EU_BLUE);

    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // 12 stars
    for(int i=0; i<12; i++) {

        float angle = i * 2 * 3.14159f / 12;

        float x = 0.55f * cos(angle);
        float y = 0.55f * sin(angle);

        drawStar(x, y, 0.08f);
    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Translation
    glTranslatef(0.0f, 0.1f, 0.0f);

    // Rotation
    glRotatef(angleRotation, 0.0f, 0.0f, 1.0f);

    // Scaling
    glScalef(1.1f, 1.1f, 1.0f);

    drawPepsiLogo();

    glutSwapBuffers();
}

void displayEU() {

    glClear(GL_COLOR_BUFFER_BIT);

    drawEUFlag();

    glutSwapBuffers();
}

void update(int value) {

    angleRotation += 1.0f;

    if(angleRotation > 360)
        angleRotation = 0;

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-1,1,-1,1);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Pepsi Window
    glutInitWindowSize(700,700);
    glutCreateWindow("Pepsi Logo Project");

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutTimerFunc(16, update, 0);

    // EU Window
    glutInitWindowPosition(750,100);

    glutInitWindowSize(700,700);

    glutCreateWindow("European Union Flag");

    init();

    glutDisplayFunc(displayEU);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

#include <GL/glut.h>
#include <windows.h>
#include <time.h>

typedef unsigned char u8;
typedef unsigned long u32;

typedef u8 bool;

#define true ((bool) 1)
#define false ((bool) 0)

typedef union {
    const u32 color;
    struct {
        union {
            const u8 blue;
            const u8 b;
        };
        union {
            const u8 green;
            const u8 g;
        };
        union {
            const u8 red;
            const u8 r;
        };
        union {
            const u8 alpha;
            const u8 a;
        };
    };
} Color;

#define black   0xff000000
#define white   0xffffffff
#define red     0xffff0000
#define green   0xff00ff00
#define blue    0xff0000ff
#define cyan    0xff00ffff
#define magenta 0xffff00ff
#define yellow  0xffffff00
#define gray    0xff7f7f7f

int mouseX = -1;
int mouseY = -1;

bool keys[256] = {false};

unsigned int seed = 12345;
unsigned int random() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    return seed ^= seed << 5;
}

void mouseEvent(int button, int state, int x, int y);

void mouseHandler(int button, int state, int x, int y) {
    mouseEvent(button, state, x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

void keyboardHandler(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
    keys[key] = TRUE;
}

void keyboardUpHandler(unsigned char key, int x, int y) {
    keys[key] = FALSE;
}

void updateMousePosition(int x, int y) {
    mouseX = x;
    mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
}

void loop();

bool shouldLoop = true;
void noLoop() {
    shouldLoop = false;
}

void display() {
    //glClear(GL_COLOR_BUFFER_BIT);
    loop();
    glutSwapBuffers();
    if (shouldLoop) {
        glutPostRedisplay();
    }
}

void init(int argc, char** argv, char *title, int width, int height) {
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    seed = time(NULL);
    glutMouseFunc(mouseHandler);
    glutPassiveMotionFunc(updateMousePosition);
    glutMotionFunc(updateMousePosition);
    glutKeyboardFunc(keyboardHandler);
    glutKeyboardUpFunc(keyboardUpHandler);
    glutDisplayFunc(display);
    glutMainLoop();
}

void fillRect(float x, float y, float w, float h, Color c) {
    glColor3f((float) c.r / 256.f, (float) c.g / 256.f, (float) c.b / 256.f);
    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);

    glEnd();
}

void setPixel(float x, float y, Color c) {
    //glColor3f((float) c.r / 256.f, (float) c.g / 256.f, (float) c.b / 256.f);
    //glBegin(GL_POINTS);
    //glVertex2f(x, y);
    //glEnd();
    fillRect(x, y, 1, 1, c);
}

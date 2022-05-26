// g++ file.cpp -lGL -lGLU -lglut -lGLEW -o executable

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

// Global variables_______________

int fps = 1000;
int randomizeAllValues = -1;
int mouse_x = 0;
int mouse_y = 0;

vector<pair<float, float>> points;

void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

float randColor()
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void drawPoints(vector<pair<float, float>> p)
{
    int size = p.size();
    glPointSize(5);
    // points
    for (int i = 0; i < size; i++)
    {
        plot(p[i].first, p[i].second);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    plot(mouse_x, mouse_y);
    drawPoints(points);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y);

// mouse callback
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        points.push_back(make_pair(mouse_x, mouse_y));
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (!points.empty())
            points.pop_back();
    }
}

// mouse motion callback
void motion(int x, int y)
{
    mouse_x = x;
    mouse_y = 1000 - y;
    glutPostRedisplay();
}

void timer(int)
{
    glutTimerFunc(fps, timer, 0);
    glutKeyboardFunc(keyboard);

    if (randomizeAllValues == 1)
    {
    }

    glutPostRedisplay();
}

void myinit(void)
{
    glClearColor(0.1, 0.11, 0.12, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutReshapeFunc(changeViewPort);
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(1000, 1000);

    // printf("print in terminal\n");
    glutCreateWindow("Quadratic Bezier Curve Animation");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(changeViewPort);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        glutDestroyWindow(glutGetWindow());
        printf("terminal statement\n");
        glutCreateWindow("windowname");
        myinit();
        glutDisplayFunc(display);
        break;
    case '2':

        break;
    case '3':

    case 'r':
        randomizeAllValues *= -1;
        glutPostRedisplay();
        break;

    case 'w':

        break;
    case 's':

        break;
    case 'a':

        break;
    case 'd':

        break;
    }
    glutPostRedisplay();
}

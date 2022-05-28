// g++ file.cpp -lGL -lGLU -lglut -lGLEW -o executable

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

// Global variables_______________

int fps = 30;
int randomizeAllValues = -1;
int mouse_x = 0;
int mouse_y = 0;
float t = 0;

vector<pair<float, float>> points;
vector<pair<float, float>> arc;

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

void drawLines(vector<pair<float, float>> p)
{
    glBegin(GL_LINES);
    for (int i = 1; i < p.size(); i++)
    {
        glVertex2f(p[i - 1].first, p[i - 1].second);
        glVertex2f(p[i].first, p[i].second);
    }
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

void quadBC(vector<pair<float, float>> p)
{
    if (points.size() == 3)
    {
        float ax = (1 - t) * p[0].first + t * p[1].first;
        float ay = (1 - t) * p[0].second + t * p[1].second;

        float bx = (1 - t) * p[1].first + t * p[2].first;
        float by = (1 - t) * p[1].second + t * p[2].second;

        glColor3f(1, 0, 0);
        plot(ax, ay);
        plot(bx, by);
        glBegin(GL_LINES);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
        glEnd();

        float cx = (1 - t) * ax + t * bx;
        float cy = (1 - t) * ay + t * by;
        glColor3f(.52, .82, .9);
        plot(cx, cy);
        arc.push_back(make_pair(cx, cy));
        drawLines(arc);
    }
}

void qbcTrace(vector<pair<float, float>> p)
{
    for (int i = 0; i < 1; i += 0.01)
    {
        float ax = (1 - i) * p[0].first + i * p[1].first;
        float ay = (1 - i) * p[0].second + i * p[1].second;

        float bx = (1 - i) * p[1].first + i * p[2].first;
        float by = (1 - i) * p[1].second + i * p[2].second;

        float cx = (1 - i) * ax + i * bx;
        float cy = (1 - i) * ay + i * by;
        glColor3f(.5, .5, .5);
        plot(cx, cy);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    drawPoints(points);

    glColor3f(.5, .5, .5);
    drawLines(points);
    quadBC(points);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y);

// mouse callback
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if (points.size() < 3)
        {
            t = 0;
            points.push_back(make_pair(mouse_x, mouse_y));
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (!points.empty())
            points.pop_back();
        arc.clear();
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

    t += 0.01;
    if (t > 1)
    {
        t = 0;
        arc.clear();
    }

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
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
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

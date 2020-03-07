#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define SCALE 500

int th = 0;
int ph = 0;
int asp = 1;
float zoom = 1.0;
float dim = 1.0;

void tokenize(string const &str, const char delim, float out[])
{
    size_t start;
    size_t end = 0;
    int i = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out[i] = stof(str.substr(start, end - start));
        i++;
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_plane(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    glScalef(zoom, zoom, 1);
    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);

    ifstream MyReadFile;
    MyReadFile.open("main_wing.txt");

    while (!MyReadFile.eof())
    {
        string color, num_point;
        float colors[3], points[3];

        getline(MyReadFile, color);
        tokenize(color, ' ', colors);

        glBegin(GL_POLYGON);
        glColor3f(colors[0], colors[1], colors[2]);

        getline(MyReadFile, num_point);

        int i = 0;
        while (i < stoi(num_point))
        {
            string point;

            getline(MyReadFile, point);
            tokenize(point, ' ', points);
            glVertex3f(points[0], points[1], points[2]);

            i++;
        }

        glEnd();
    }

    MyReadFile.close();

    glutSwapBuffers();
}

void special_key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        th += 2;
        break;
    case GLUT_KEY_LEFT:
        th -= 2;
        break;
    case GLUT_KEY_UP:
        ph -= 2;
        break;
    case GLUT_KEY_DOWN:
        ph += 2;
        break;
    default:
        break;
    }

    th %= 360;
    ph %= 360;

    init();
    glutPostRedisplay();
}

void normal_key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ']':
        zoom += 0.2;
        break;
    case '[':
        zoom -= 0.2;
        if (zoom < 0)
            zoom = 0;
        break;
    default:
        break;
    }

    init();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutCreateWindow("World War I Airplane Showcase");

    init();

    glutDisplayFunc(draw_plane);
    glutSpecialFunc(special_key);
    glutKeyboardFunc(normal_key);

    glutMainLoop();

    return 0;
}

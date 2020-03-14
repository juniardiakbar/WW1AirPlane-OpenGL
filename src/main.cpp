#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define SCALE 500

int th = 32;
int ph = 8;
int asp = 1;
int rotate_speed = 25;
float zoom = 1.0;
float dim = 1.0;
int theta = 0;
string filename[] = {"main_wing.txt", "body.txt"};

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

void Initialize()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Lighting set up
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set lighting intensity and color
    GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat qaDiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    GLfloat qaLightPosition[] = {.5, .5, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

void idleCallBack()
{
    // Spins the cube around the set axis.
    theta += rotate_speed;
    theta %= 360;

    glutPostRedisplay();
}

void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

    glLoadIdentity();

    glScalef(zoom, zoom, 1);
    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);

    for (int i = 0; i < 2; i++)
    {
        ifstream MyReadFile;
        MyReadFile.open(filename[i]);

        while (!MyReadFile.eof())
        {
            string color, num_point;
            float colors[3], points[3];

            getline(MyReadFile, color);
            tokenize(color, ' ', colors);

            glBegin(GL_POLYGON);
            glNormal3f(0.0, 0.0, 1.0);
            glColor3f(colors[0], colors[1], colors[2]);

            getline(MyReadFile, num_point);

            int j = 0;
            while (j < stoi(num_point))
            {
                string point;

                getline(MyReadFile, point);
                tokenize(point, ' ', points);
                glVertex3f(points[0], points[1], points[2]);

                j++;
            }

            glEnd();
        }

        MyReadFile.close();
    }

    // gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(theta, 1.0, 0.0, 0.0);

    ifstream MyReadFile;
    MyReadFile.open("propeller.txt");
    while (!MyReadFile.eof())
    {
        string color, num_point;
        float colors[3], points[3];

        getline(MyReadFile, color);
        tokenize(color, ' ', colors);

        glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        glColor3f(colors[0], colors[1], colors[2]);

        getline(MyReadFile, num_point);

        int j = 0;
        while (j < stoi(num_point))
        {
            string point;

            getline(MyReadFile, point);
            tokenize(point, ' ', points);
            glVertex3f(points[0], points[1], points[2]);

            j++;
        }

        glEnd();
    }

    MyReadFile.close();

    glutSwapBuffers();
}

// void DrawPropeller(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glEnable(GL_DEPTH_TEST);
//     glLoadIdentity();

//     glutSwapBuffers();
// }

void SpecialKey(int key, int x, int y)
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

    Initialize();
    glutPostRedisplay();
}

void NormalKey(unsigned char key, int x, int y)
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
    case 'r':
        zoom = 1.0;
        th = 32;
        ph = 8;
    default:
        break;
    }

    Initialize();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutCreateWindow("World War I Airplane Showcase");

    Initialize();

    glutDisplayFunc(Draw);
    // glutDisplayFunc(DrawPropeller);
    glutIdleFunc(idleCallBack);
    glutSpecialFunc(SpecialKey);
    glutKeyboardFunc(NormalKey);

    glutMainLoop();

    return 0;
}

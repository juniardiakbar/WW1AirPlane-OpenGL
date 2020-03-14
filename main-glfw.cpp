#define GLEW_STATIC
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int th = 32;
int ph = 8;
int asp = 1;
int rotate_speed = 25;
float zoom = 1.0;
float dim = 1.0;
int theta = 0;

const char *gameTitle = "World War I Airplane Showcase";

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

  glClearColor(0.1, 0.1, 0.1, 0.0);
  glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void SpecialKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_RIGHT:
    th += 2;
    break;
  case GLFW_KEY_LEFT:
    th -= 2;
    break;
  case GLFW_KEY_UP:
    ph -= 2;
    break;
  case GLFW_KEY_DOWN:
    ph += 2;
    break;
  default:
    break;
  }

  th %= 360;
  ph %= 360;
}

static void display(GLFWwindow *window)
{
  Initialize();
  ifstream MyReadFile;
  MyReadFile.open("main_wing_backup.txt");
  float points[1024];

  int i = 0;
  while (!MyReadFile.eof())
  {
    string point;
    float out[3];

    getline(MyReadFile, point);
    tokenize(point, ',', out);

    for (int j = 0; j < 3; j++)
    {
      points[i] = out[j];
      cout << out[j] << endl;
      i++;
    }
  }

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, i * sizeof(float), points, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  while (!glfwWindowShouldClose(window))
  {
    Initialize();

    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);

    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, i);

    // update other events like input handling
    glfwPollEvents();

    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);

    glfwSetKeyCallback(window, SpecialKey);
  }
}

int main(int argc, char **argv)
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 800, "World War I Airplane Showcase", NULL, NULL);

  if (!window)
  {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

  /* OTHER STUFF GOES HERE NEXT */
  Initialize();
  display(window);

  glfwTerminate();
  return 0;
}
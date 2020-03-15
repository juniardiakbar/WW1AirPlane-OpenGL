#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include "common/shader.hpp"

using namespace std;
using namespace glm;

GLFWwindow *window;

int th = 32;
int ph = 8;
int zh = 0;
int asp = 1;
int rotate_speed = 25;
float zoom = 1.0;
float dim = 1.0;
int theta = 0;

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
    cout << "right" << endl;
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
  case GLFW_KEY_N:
    zh += 2;
    break;
  case GLFW_KEY_M:
    zh -= 2;
    break;
  default:
    break;
  }

  th %= 360;
  ph %= 360;
}

void display(GLFWwindow *window)
{
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

  ifstream MyReadFile;
  MyReadFile.open("main.txt");
  GLfloat pointsMain[1024];

  int idxMain = 0;
  while (!MyReadFile.eof())
  {
    string point;
    float out[3];

    getline(MyReadFile, point);
    tokenize(point, ',', out);

    for (int j = 0; j < 3; j++)
    {
      pointsMain[idxMain] = out[j];
      cout << out[j] << endl;
      idxMain++;
    }
  }

  MyReadFile.close();

  GLuint mainbo = 0;
  glGenBuffers(1, &mainbo);
  glBindBuffer(GL_ARRAY_BUFFER, mainbo);
  glBufferData(GL_ARRAY_BUFFER, idxMain * sizeof(float), pointsMain, GL_STATIC_DRAW);

  // MyReadFile.open("propeller.txt");
  // float pointsPropeller[1024];

  // int idxPropeller = 0;
  // while (!MyReadFile.eof())
  // {
  //   string point;
  //   float out[3];

  //   getline(MyReadFile, point);
  //   tokenize(point, ',', out);

  //   for (int j = 0; j < 3; j++)
  //   {
  //     pointsPropeller[idxPropeller] = out[j];
  //     cout << out[j] << endl;
  //     idxPropeller++;
  //   }
  // }

  // MyReadFile.close();

  // GLuint propellerbo = 0;
  // glGenBuffers(1, &propellerbo);
  // glBindBuffer(GL_ARRAY_BUFFER, propellerbo);
  // glBufferData(GL_ARRAY_BUFFER, idxPropeller * sizeof(float), pointsPropeller, GL_STATIC_DRAW);
  while (!glfwWindowShouldClose(window))
  {
    Initialize();

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);
    glRotatef(zh, 0, 0, 1);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mainbo);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, idxMain);

    // glRotatef(theta, 1.0, 0.0, 0.0);
    // glBindVertexArray(propellerao);
    // glDrawArrays(GL_TRIANGLES, 0, idxPropeller);

    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    glfwSetKeyCallback(window, SpecialKey);

    theta += rotate_speed;
    theta %= 360;
  }
}

int main(void)
{
  // Initialise GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 800, "World War I Airplane Showcase", NULL, NULL);

  if (!window)
  {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE; // Needed for core profile
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  Initialize();

  display(window);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

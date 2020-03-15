#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"

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

bool isShadersOn = false;

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
  glfwPollEvents();
  glfwSetCursorPos(window, 1024 / 2, 768 / 2);

  // // Enable depth test
  // glEnable(GL_DEPTH_TEST);
  // // Accept fragment if it closer to the camera than the former one
  // glDepthFunc(GL_LESS);

  // // Cull triangles which normal is not towards the camera
  // glEnable(GL_CULL_FACE);

  glClearColor(1, 1, 1, 0.0);
  glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);
}

void SpecialKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_K:
    isShadersOn = false;
    break;
  case GLFW_KEY_L:
    isShadersOn = true;
    break;
  default:
    break;
  }
}

void display(GLFWwindow *window)
{
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
  GLuint defaultID = LoadShaders("SimpleVertexShader.vertexshader", "DefaultFragment.fragmentshader");

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint DefaultMatrixID = glGetUniformLocation(defaultID, "MVP");

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
      idxMain++;
    }
  }

  MyReadFile.close();

  GLuint mainbo = 0;
  glGenBuffers(1, &mainbo);
  glBindBuffer(GL_ARRAY_BUFFER, mainbo);
  glBufferData(GL_ARRAY_BUFFER, idxMain * sizeof(float), pointsMain, GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
  {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    if (isShadersOn)
    {
      glUseProgram(programID);
    }
    else
    {
      glUseProgram(defaultID);
    }

    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mainbo);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, idxMain);

    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();

    glfwSetKeyCallback(window, SpecialKey);
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

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  Initialize();

  display(window);

  glfwTerminate();

  return 0;
}

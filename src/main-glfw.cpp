#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"

using namespace std;
using namespace glm;

GLFWwindow *window;

int asp = 1;
int rotate_speed = 25;
float dim = 1.0;
int theta = 0;

bool isShadersOn = false;

glm::mat4 ModelMatrix = glm::mat4(1.0);

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
  glClearColor(1, 1, 1, 0.0);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);
}

void printHelp()
{
  printf("\033c");
  printf("===============HELP MENU===============\n");
  printf("P : Zoom Out\n");
  printf("O : Zoom In\n");

  printf("=====Rotate Model=====\n");
  printf("W : Rotate Model Upward\n");
  printf("S : Rotate Model Downward\n");
  printf("A : Rotate Model To The Left\n");
  printf("D : Rotate Model To The Right\n");
  printf("Q : Rotate Model Counter Clockwise\n");
  printf("E : Rotate Model Clockwise\n\n");

  printf("=====Colour Shader=====\n");
  printf("L : Turn On Colour Shader\n");
  printf("K : Turn Off Colour Shader\n\n");

  printf("=====Setting=====\n");
  printf("R : Reset View\n");
  printf("T : Reset Model\n");
  printf("H : Help Menu\n\n");
}

void SpecialKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_X:
    isShadersOn = false;
    break;
  case GLFW_KEY_Z:
    isShadersOn = true;
    break;
  case GLFW_KEY_D:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    break;
  case GLFW_KEY_A:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    break;
  case GLFW_KEY_E:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    break;
  case GLFW_KEY_Q:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    break;
  case GLFW_KEY_S:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    break;
  case GLFW_KEY_W:
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    break;
  case GLFW_KEY_T:
    isShadersOn = false;
    ModelMatrix = glm::mat4(1.0);
    break;
  case GLFW_KEY_H:
    printHelp();
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
  GLuint defaultID = LoadShaders("DefaultFragment.vertexshader", "DefaultFragment.fragmentshader");

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint DefaultMatrixID = glGetUniformLocation(defaultID, "MVP");

  ifstream MyReadFile;
  MyReadFile.open("main.txt");
  GLfloat pointsMain[2048];

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

  MyReadFile.open("color.txt");
  GLfloat pointsColor[2048];

  int idxColor = 0;
  while (!MyReadFile.eof())
  {
    string point;
    float out[3];

    getline(MyReadFile, point);
    tokenize(point, ',', out);

    for (int j = 0; j < 3; j++)
    {
      pointsColor[idxColor] = out[j];
      idxColor++;
    }
  }

  MyReadFile.close();

  GLuint mainbo;
  glGenBuffers(1, &mainbo);
  glBindBuffer(GL_ARRAY_BUFFER, mainbo);
  glBufferData(GL_ARRAY_BUFFER, idxMain * sizeof(float), pointsMain, GL_STATIC_DRAW);

  GLuint colorbo;
  glGenBuffers(1, &colorbo);
  glBindBuffer(GL_ARRAY_BUFFER, colorbo);
  glBufferData(GL_ARRAY_BUFFER, idxColor * sizeof(float), pointsColor, GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
  {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    // glm::mat4 ModelMatrix = glm::mat4(1.0);
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

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbo);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, idxMain);

    glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

    glfwSwapBuffers(window);
    glfwPollEvents();

    glfwSetKeyCallback(window, SpecialKey);
  }

  glDeleteBuffers(1, &mainbo);
  glDeleteBuffers(1, &colorbo);
  glDeleteProgram(programID);
  glDeleteProgram(defaultID);
  glDeleteVertexArrays(1, &VertexArrayID);
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

  Initialize();

  display(window);

  glfwTerminate();

  return 0;
}

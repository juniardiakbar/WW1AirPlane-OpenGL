#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "controls.hpp"

using namespace std;
using namespace glm;

extern GLFWwindow *window;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3(-3.0f, 3.0f, 3.0f);

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;

void computeMatricesFromInputs()
{
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	glm::vec3 direction(0.5f, -0.5f, -0.5f);
	glm::vec3 right(0.5f, 0, 1.0f);
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
	}

	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		position = glm::vec3(-3.0f, 3.0f, 3.0f);
	}


	float FoV = initialFoV;

	ProjectionMatrix = glm::perspective(glm::radians(FoV), 1.0f, 0.1f, 100.0f);

	// Camera matrix
	ViewMatrix = glm::lookAt(
			position,
			position + direction,
			up);

	lastTime = currentTime;
}
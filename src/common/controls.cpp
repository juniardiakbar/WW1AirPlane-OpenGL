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

GLfloat initPosX = -3.0f;
GLfloat initPosY = 3.0f;
GLfloat initPosZ = 3.0f;

GLfloat initDirX = 0.5f;
GLfloat initDirY = -0.5f;
GLfloat initDirZ = -0.5f;

GLfloat initRightX = 0.5f;
GLfloat initRightY = 0.0f;
GLfloat initRightZ = 1.0f;

GLfloat initTheta = 0.0f;
GLfloat initPhi = 0.0f;

GLfloat PosX = initPosX;
GLfloat PosY = initPosY;
GLfloat PosZ = initPosZ;

GLfloat DirX = initDirX;
GLfloat DirY = initDirY;
GLfloat DirZ = initDirZ;

GLfloat RightX = initRightX;
GLfloat RightY = initRightY;
GLfloat RightZ = initRightZ;

GLfloat theta2 = 0.0f;
GLfloat phi = 0.0f;

// angle of rotation for the camera direction
float angle = 0.0;

glm::vec3 position = glm::vec3(PosX, PosY, PosZ);

float initialFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;

bool func3 = false;

void computeMatricesFromInputs()
{
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	glm::vec3 direction(DirX, DirY, DirZ);
	glm::vec3 right(RightX, RightY, RightZ);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
		func3 = false;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
		func3 = false;
	}

	//Reset view
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		position = glm::vec3(-3.0f, 3.0f, 3.0f);
	} 

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		angle -= 0.003f;

		if (angle > 0)
		{
			DirX -= sin(angle);
		}
		else
		{
			DirX += sin(angle);
		}

		DirZ -= -cos(angle) + 1;

		direction = glm::vec3(DirX, DirY, DirZ);
		func3 = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		angle += 0.003f;

		if (angle < 0)
		{
			DirX -= sin(angle);
		}
		else
		{
			DirX += sin(angle);
		}
		DirZ += -cos(angle) + 1;

		direction = glm::vec3(DirX, DirY, DirZ);
		func3 = false;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		theta2 = theta2 - 0.01f;
		float pX = PosX;
		float pY = PosY;
		float pZ = PosZ;

		GLfloat radius = sqrt(pX * pX + pY * pY + pZ * pZ);

		pX = DirX + radius * cos(0.0f) * sin(theta2);
		pY = DirY + radius * sin(0.0f) * sin(theta2);
		pZ = DirX + radius * cos(theta2);

		// cout << "J " << theta2 << " " << " " << pX << " " << pY << " "
		// 		 << " " << pZ << endl;

		cout << "J "
				 << " " << position[0] << " " << position[1] << " " << position[2] << endl;
		cout << "J-D "
				 << " " << direction[0] << " " << direction[1] << " " << direction[2] << endl;

		position = glm::vec3(pX, pY, pZ);
		func3 = true;
	}

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		theta2 = theta2 + 0.01f;
		float pX = PosX;
		float pY = PosY;
		float pZ = PosZ;

		GLfloat radius = sqrt(pX * pX + pY * pY + pZ * pZ);

		pX = DirX + radius * cos(0.0f) * sin(theta2);
		pY = DirY + radius * sin(0.0f) * sin(theta2);
		pZ = DirX + radius * cos(theta2);

		position = glm::vec3(pX, pY, pZ);
		func3 = true;
	}

	float FoV = initialFoV;

	ProjectionMatrix = glm::perspective(glm::radians(FoV), 1.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(
			position,
			position + direction,
			up);

	if (func3)
	{
		ViewMatrix = glm::lookAt(
				position,
				direction,
				up);
	}

	lastTime = currentTime;
}
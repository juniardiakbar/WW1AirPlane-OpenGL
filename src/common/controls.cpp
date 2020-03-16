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
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		//up = glm::cross(right, direction);
		//cout << "DirX Origin " << DirX << endl;		
		angle += 0.01f;
		DirX = sin(angle);
		//cout << "DirX 1 " << DirX << endl;
		DirZ = -cos(angle);
		//float dX = DirX;
		//float dZ = DirZ;
		//float pX = PosX;
		//float pZ = PosZ;
		//DirX = dX + PosX;
		//DirZ = dZ + PosZ;
		//cout << "DirX 2 " << DirX << endl;
		position = glm::vec3(PosX, PosY, PosZ);
		direction = glm::vec3(DirX, DirY, DirZ);
		direction = direction + position;
		//DirX += PosX;
		//DirZ += PosZ;
		//DirY += PosY;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		//up = glm::cross(right, direction);
		//cout << "DirX Origin " << DirX << endl;		
		angle += 0.01f;
		DirX = sin(angle);
		//cout << "DirX 1 " << DirX << endl;
		DirZ = -cos(angle);
		//float dX = DirX;
		//float dZ = DirZ;
		//float pX = PosX;
		//float pZ = PosZ;
		//DirX = dX + PosX;
		//DirZ = dZ + PosZ;
		//cout << "DirX 2 " << DirX << endl;
		position = glm::vec3(PosX, PosY, PosZ);
		direction = glm::vec3(DirX, DirY, DirZ);
		direction = direction + position;
		//DirX += PosX;
		//DirZ += PosZ;
		//DirY += PosY;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		//up = glm::vec3(0.0f, 1.0f, 0.0f);
		theta2 = theta2 - 0.01f;
		float pX = PosX;
		float pY = PosY;
		float pZ = PosZ;

		GLfloat radius = sqrt(pX*pX + pY*pY + pZ*pZ);
		//GLfloat radius = sqrt(PosX*PosX + PosY*PosY + PosZ*PosZ);
		//cout << "radius " << radius << endl;
		//PosX = radius * cos(0.0f) * sin(theta2);
		//cout << "sin " << sin(theta2) << endl;
		//cout << "PosX " << PosX << endl;
		//PosY = radius * sin(0.0f) * sin(theta2);
		//PosZ = radius * cos(theta2);
		pX = DirX + radius * cos(0.0f) * sin(theta2);
		cout << "pX " << pX << endl;
		pY = DirY + radius * sin(0.0f) * sin(theta2);
		pZ = DirX + radius * cos(theta2);
		cout << "DirX " << DirX << endl;
		cout << "PosY " << PosY << endl;
		cout << "pY " << pY << endl;
		cout << "pZ " << pZ << endl;

		position = glm::vec3(pX, pY, pZ);
		

	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		//up = glm::vec3(0.0f, 1.0f, 0.0f);
		theta2 = theta2 + 0.01f;
		float pX = PosX;
		float pY = PosY;
		float pZ = PosZ;

		GLfloat radius = sqrt(pX*pX + pY*pY + pZ*pZ);
		//GLfloat radius = sqrt(PosX*PosX + PosY*PosY + PosZ*PosZ);
		//cout << "radius " << radius << endl;
		//PosX = radius * cos(0.0f) * sin(theta2);
		//cout << "sin " << sin(theta2) << endl;
		//cout << "PosX " << PosX << endl;
		//PosY = radius * sin(0.0f) * sin(theta2);
		//PosZ = radius * cos(theta2);
		pX = DirX + radius * cos(0.0f) * sin(theta2);
		cout << "pX " << pX << endl;
		pY = DirY + radius * sin(0.0f) * sin(theta2);
		pZ = DirX + radius * cos(theta2);
		cout << "DirX " << DirX << endl;
		cout << "PosY " << PosY << endl;
		cout << "pY " << pY << endl;
		cout << "pZ " << pZ << endl;

		position = glm::vec3(pX, pY, pZ);
		

	}

	float FoV = initialFoV;

	ProjectionMatrix = glm::perspective(glm::radians(FoV), 1.0f, 0.1f, 100.0f);

	// Camera matrix
	ViewMatrix = glm::lookAt(
			position,
			direction,
			up);

	lastTime = currentTime;
}
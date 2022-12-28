#pragma once
#include "../OpenGLWrapper/Common.h"

class Camera
{
public:
	Camera(bool handleInput, GLFWwindow* window);
	void UpdateInput();

	GLFWwindow* window;
	float camSpeed = 0.1;
	bool handleInput;
	bool isMouseLocked = false;
	vec2 angleXY;
	glm::vec3 direction = glm::vec3(0);
	glm::vec3 position;
	glm::mat4 GetRotMat() const;
};
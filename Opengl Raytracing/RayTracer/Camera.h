#pragma once
#include "../OpenGLWrapper/Common.h"
#include "../OpenGLWrapper/Shader.h"
class Camera
{
public:
	Camera(bool handleInput, GLFWwindow* window);
	void UpdateInput();
	void SetUniforms(Shader* sh);
	GLFWwindow* window;
	float camSpeed = 0.1;
	bool handleInput;
	bool isMouseLocked = false;
	vec2 angleXY;
	glm::vec3 direction = glm::vec3(0);
	glm::vec3 position;
	glm::mat4 GetRotMat() const;
	
	float focusDist = 0.1;
	float aperature = 0.1;
	float fov = PI / 4;
	vec3 Up();
	vec3 Right();
};
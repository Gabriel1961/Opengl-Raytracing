#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

static struct MPos { double x{}, y{}; };

Camera::Camera(bool handleInput, GLFWwindow* window)
	:handleInput(handleInput),window(window)
{
	
}

void Camera::UpdateInput()
{
	if (handleInput == false)
		return;
#pragma region Cursor
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		isMouseLocked = true;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // set cursor to locked 
	}
	else {
		isMouseLocked = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
#pragma endregion


#pragma region MouseMovement

	static MPos prevMousePos{};
	MPos curMousePos{};
	glfwGetCursorPos(window, &curMousePos.x, &curMousePos.y);
	if (isMouseLocked)
	{

		float sensitivity = 0.002;
		MPos mouseSpeed = { curMousePos.x - prevMousePos.x, curMousePos.y - prevMousePos.y };
		if (abs(mouseSpeed.x) < 200 && abs(mouseSpeed.y) < 200)
		{
			this->angleXY.x += mouseSpeed.x * sensitivity;
			this->angleXY.y += mouseSpeed.y * sensitivity;
			if (this->angleXY.y > PI / 2)
				this->angleXY.y = PI / 2;
			if (this->angleXY.y < -PI / 2)
				this->angleXY.y = -PI / 2;
		}
	}
	prevMousePos = curMousePos;
	mat4 rotMat = GetRotMat();
	direction = rotMat * vec4(0, 0, 1, 1);
#pragma endregion


#pragma region KeyMovement
	vec3 dirY = rotMat * vec4(0, 1, 0, 1);

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		position.y += camSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
		position.y -= camSpeed;

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		position -= cross(dirY,direction) * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		position += cross(dirY,direction) * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		position += direction * camSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		position -= direction * camSpeed;
	}

#pragma endregion

#pragma region CamSpeedChange
	if (glfwGetKey(window, GLFW_KEY_UP))
		camSpeed += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_DOWN))
		camSpeed -= 0.001;
#pragma endregion

}



glm::mat4 Camera::GetRotMat() const
{
	return rotate(rotate(mat4(1), angleXY.x, { 0,1,0 }), angleXY.y, { 1,0,0 });
}

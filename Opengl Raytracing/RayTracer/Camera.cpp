#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

static struct MPos { double x{}, y{}; };

Camera::Camera(bool handleInput, GLFWwindow* window)
	:handleInput(handleInput),window(window)
{
	
}

void Camera::UpdateInput(float deltaT)
{
	const float ndeltaT = deltaT * 60;

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
		position.y += camSpeed * ndeltaT;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
		position.y -= camSpeed * ndeltaT;

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		position -= cross(dirY,direction) * camSpeed * ndeltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		position += cross(dirY,direction) * camSpeed * ndeltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		position += direction * camSpeed * ndeltaT;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		position -= direction * camSpeed * ndeltaT;
	}

#pragma endregion

	if (glfwGetKey(window, GLFW_KEY_UP))
		focusDist += 0.01, printf("lensRadius: %f\n", focusDist);
	else if (glfwGetKey(window, GLFW_KEY_DOWN))
		focusDist -= 0.01,printf("lensRadius: %f\n", focusDist);

}

void Camera::SetUniforms(Shader* sh)
{
	sh->SetUniform1f("cam.fov", fov);
	sh->SetUniform1f("cam.aperature", aperature);
	sh->SetUniform1f("cam.focusDist", focusDist);
	sh->SetUniform3f("cam.pos", position);
	sh->SetUniform3f("cam.dir", direction);
	sh->SetUniformMat3f("cam.rot", GetRotMat());

}



glm::mat4 Camera::GetRotMat() const
{
	return rotate(rotate(mat4(1), angleXY.x, { 0,1,0 }), angleXY.y, { 1,0,0 });
}

vec3 Camera::Up()
{
	return mat3(GetRotMat())* vec3(0, 1, 0);
}

vec3 Camera::Right()
{
	return cross(direction, Up());
}

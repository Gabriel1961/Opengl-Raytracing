#pragma once
#include "../OpenGLWrapper/Common.h"
#include "../OpenGLWrapper/Quad.h"
#include "Camera.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
class RayTracer
{
private:
	void GenerateRenderTexture();
	int GetWindowWidth();
	int GetWindowHeight();
	void EnableShaderReload();
public:
	float deltaTime;
	Camera cam;
	GLFWwindow* window;
	RayTracer(GLFWwindow* window);
	Quad* renderQuad;
	Texture* renderTex;
	ComputeShader* rayTracingShader;
	void Start();
	void Render();
};


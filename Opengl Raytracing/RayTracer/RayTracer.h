#pragma once
#include "../OpenGLWrapper/Common.h"
#include "../OpenGLWrapper/Quad.h"
#include "Camera.h"
class RayTracer
{
private:
	void GenerateRenderTexture();
	int GetWindowWidth();
	int GetWindowHeight();
	void EnableShaderReload();
public:
	Camera cam;
	GLFWwindow* window;
	RayTracer(GLFWwindow* window);
	Quad* renderQuad;
	Texture* renderTex;
	ComputeShader* rayTracingShader;
	void Start();
	void Render();
};


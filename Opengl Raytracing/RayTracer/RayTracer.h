#pragma once
#include "../OpenGLWrapper/Common.h"
#include "../OpenGLWrapper/Quad.h"

class RayTracer
{
private:
	void GenerateRenderTexture();
	int GetWindowWidth();
	int GetWindowHeight();
public:
	GLFWwindow* window;
	RayTracer(GLFWwindow* window);
	Quad* renderQuad;
	Texture* renderTex;
	ComputeShader* rayTracingShader;
	void Start();
	void Render();
};


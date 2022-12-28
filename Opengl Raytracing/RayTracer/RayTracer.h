#pragma once
#include "../OpenGLWrapper/Common.h"
#include "../OpenGLWrapper/Quad.h"

class RayTracer
{
private:
	void GenerateRenderTexture();
public:
	GLFWwindow* window;
	RayTracer(GLFWwindow* window);
	Quad* renderQuad;
	Texture* renderTex;
	void Start();
	void Render();
};


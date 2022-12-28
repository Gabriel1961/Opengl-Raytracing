#include "RayTracer.h"

void RayTracer::GenerateRenderTexture()
{
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	renderTex = new Quad(vec4{1,0,1,1});
}

RayTracer::RayTracer(GLFWwindow* window)
	:window(window)
{
	GenerateRenderTexture();
}

void RayTracer::Start()
{
	
}

void RayTracer::Render()
{
	renderTex->Render();
}



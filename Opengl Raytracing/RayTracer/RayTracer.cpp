#include "RayTracer.h"

void RayTracer::GenerateRenderTexture()
{
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	renderQuad = new Quad(true,0);
	renderTex = new Texture("brick_wall.jpg");
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
	renderTex->Bind(0);
	renderQuad->Render();
}



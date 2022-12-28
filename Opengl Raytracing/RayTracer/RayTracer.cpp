#include "RayTracer.h"

void RayTracer::GenerateRenderTexture()
{
	renderQuad = new Quad(true,0);
	renderTex = new Texture(GetWindowWidth(), GetWindowHeight());
}

int RayTracer::GetWindowWidth()
{
	int w = 0;
	glfwGetWindowSize(window, &w,0);
	return w;
}

int RayTracer::GetWindowHeight()
{
	int h = 0;
	glfwGetWindowSize(window, 0, &h);
	return h;
}

RayTracer::RayTracer(GLFWwindow* window)
	:window(window)
{
	GenerateRenderTexture();
	rayTracingShader = new ComputeShader("RayTracer/raytrace.comp");
}

void RayTracer::Start()
{

}

void RayTracer::Render()
{
	renderTex->Bind(0);
	rayTracingShader->Dispatch(renderTex->GetWidth(), renderTex->GetHeight(), 1);
	renderQuad->Render();
}



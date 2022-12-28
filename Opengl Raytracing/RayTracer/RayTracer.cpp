#include "RayTracer.h"

void RayTracer::GenerateRenderTexture()
{
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	int gw = vp[2], gh = vp[3];
	if (renderTex)
		if (renderTex->GetWidth() == gw && renderTex->GetHeight() == gh)
			return;
	delete renderQuad;
	renderQuad = new Quad(true,0);
	delete renderTex;
	renderTex = new Texture(gw, gh);
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

void RayTracer::EnableShaderReload()
{
	static bool lastPressed = false;
	if (glfwGetKey(window, GLFW_KEY_R)) {
		if (lastPressed == false) {
			if (rayTracingShader->Recompile())
				printf("Succesfuly compiled shader.\n");
		}
		lastPressed = true;
	}
	else
		lastPressed = false;
}

RayTracer::RayTracer(GLFWwindow* window)
	:window(window),cam(true,window)
{
	GenerateRenderTexture();
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int height, int width) {
		glViewport(0, 0, height, width);
	});
	rayTracingShader = new ComputeShader("RayTracer/raytrace.comp");
}

void RayTracer::Start()
{

}

void RayTracer::Render()
{
	EnableShaderReload();
	cam.UpdateInput();
	GenerateRenderTexture();
	renderTex->Bind(0);
	rayTracingShader->SetUniform3f("camPos", cam.position);
	rayTracingShader->SetUniformMat4f("camRot", cam.GetRotMat());
	rayTracingShader->Dispatch(renderTex->GetWidth(), renderTex->GetHeight(), 1);
	renderQuad->Render();
}



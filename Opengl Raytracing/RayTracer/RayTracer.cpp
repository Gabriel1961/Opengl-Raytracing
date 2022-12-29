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
	cam.position = { 0,2,0 };
	cam.angleXY.y += PI / 6;
	cam.focusDist = 3;
	cam.aperature = 0.1;
}

void RayTracer::Render()
{
	ImGui::Begin("Camera Settings");
	ImGui::SliderFloat("Aperature",&cam.aperature,0,10);
	ImGui::SliderFloat("Focal length",&cam.focusDist,0,10);
	ImGui::End();

	EnableShaderReload();
	cam.UpdateInput();
	GenerateRenderTexture();
	renderTex->Bind(0);
	cam.SetUniforms(rayTracingShader);
	rayTracingShader->Dispatch(renderTex->GetWidth(), renderTex->GetHeight(), 1);
	renderQuad->Render();
}



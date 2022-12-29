#include "OpenGLWrapper/Common.h"
#include "RayTracer/RayTracer.h"
#include <iomanip>
#include <sstream>

/// returns delta T
float TimeFrame(GLFWwindow* window){
    static float lastTime = glfwGetTime();
    float t = glfwGetTime();
    float d = t-lastTime;
    glfwSetWindowTitle(window,std::to_string(int(1/d)).c_str());
    lastTime = t;
    return d;
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(800, 600, "Raytracing Opengl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        // GLEW initialization failed
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // enable vsync
    glfwSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    RayTracer rayTracer(window);
    rayTracer.Start();

    while (!glfwWindowShouldClose(window))
    {
        rayTracer.deltaTime = TimeFrame(window);
        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        glClear(GL_COLOR_BUFFER_BIT);

        rayTracer.Render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
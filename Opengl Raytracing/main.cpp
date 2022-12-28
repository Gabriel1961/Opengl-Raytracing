#include "OpenGLWrapper/Common.h"
#include "RayTracer/RayTracer.h"
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

    RayTracer rayTracer(window);
    rayTracer.Start();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        rayTracer.Render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
}
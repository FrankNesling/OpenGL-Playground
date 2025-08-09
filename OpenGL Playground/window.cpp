#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <helper.h>


int window()
{
    // GLFW / OpenGL Init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window init
    GLFWwindow* window = glfwCreateWindow(800, 600, "The window of doom", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glfwTerminate();
    return 0;
}


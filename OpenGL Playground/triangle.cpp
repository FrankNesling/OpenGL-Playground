#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <helper.h>

// vertex shader
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// fragment shader
const char* fragmentShaderSourceYellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

const char* fragmentShaderSourceOrange = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


int triangle()
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

    // vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check vertex shader compilation success
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);

    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    // linking - shader program
    unsigned int shaderPrograms[2];
    shaderPrograms[0] = glCreateProgram();

    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaderOrange);
    glLinkProgram(shaderPrograms[0]);

    shaderPrograms[1] = glCreateProgram();

    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaderYellow);
    glLinkProgram(shaderPrograms[1]);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);


    // rectangle
    float verticesRec[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // triangle
    float verticesTri1[] = {
        -1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 0.0f,
        -0.5f,  0.0f, 0.0f
    };

    float verticesTri2[] = {
         0.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.5f, 0.0f, 0.0f
    };


    // element buffer object
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // vertex buffer object
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);

    // vertex array object
    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);

    // binding VAO1
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri1), verticesTri1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // binding VAO2
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri2), verticesTri2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // polygons
        glUseProgram(shaderPrograms[0]);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // wireframe mode
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderPrograms[1]);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glfwTerminate();
    return 0;
}


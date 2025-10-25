
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth)
{
    glViewport(0, 0, width, heigth);
}

void processInpute(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

const char *vertexShaderSource = "#version 450 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos, 1.0);\n"
                                 "vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                 "}\0";

const char *fragmentShader1Source = "#version 450 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec4 vertexColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vertexColor;\n"
                                    "}\n";

const char *fragmentShader2Source = "#version 450 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                    "}\n";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Two triangles", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);

    unsigned int shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);

    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);

    unsigned int shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderYellow);

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.9f, 0.5f, 0.0f};

    float secondTriangle[] = {
        0.9f, -0.5f, 0.0f,
        0.9f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f};

    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3};

    unsigned int VBO[2];
    unsigned int VAO[2];
    // unsigned int EBO;

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    // glGenBuffers(1, &EBO);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        processInpute(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO[0]);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    // glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);

    glfwTerminate();
    return 0;
}

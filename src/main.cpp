#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <../shader_s.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
bool firstMouse = true;
float fov = 45.0f;

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

    const float cameraSpeed = static_cast<float>(2.5f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

    fov -= (float)yoffset;
    if(fov <1.0f){
        fov = 1.0f;
    }
    if(fov > 45.0f) {
        fov = 45.0f;
    }
}

// const char *vertexShaderSource = "#version 450 core\n"
//                                  "layout (location = 0) in vec3 aPos;\n"
//                                  "layout (location = 1) in vec3 aColor;\n"
//                                  "out vec3 ourColor;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "gl_Position = vec4(aPos, 1.0);\n"
//                                  "ourColor = aColor;\n"
//                                  "}\0";

// const char *fragmentShader1Source = "#version 450 core\n"
//                                     "out vec4 FragColor;\n"
//                                     "uniform vec4 ourColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "FragColor = ourColor;\n"
//                                     "}\n";

// const char *fragmentShader2Source = "#version 450 core\n"
//                                     "out vec4 FragColor;\n"
//                                     "in vec3 ourColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "FragColor = vec4(ourColor, 1.0f);\n"
//                                     "}\n";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Textures", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    // Shader firstTriangleShader("shaders/shader_1.vs", "shaders/shader_1.fs");
    // Shader secondTriangleShader("shaders/shader_2.vs", "shaders/shader_2.fs");
    Shader rectangleShader("shaders/rec_shader.vs", "shaders/rec_shader.fs");
    // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    // unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    // glCompileShader(fragmentShaderOrange);

    // unsigned int shaderProgramOrange = glCreateProgram();
    // glAttachShader(shaderProgramOrange, vertexShader);
    // glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    // glLinkProgram(shaderProgramOrange);
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShaderOrange);

    // unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    // glCompileShader(fragmentShaderYellow);

    // unsigned int shaderProgramYellow = glCreateProgram();
    // glAttachShader(shaderProgramYellow, vertexShader);
    // glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    // glLinkProgram(shaderProgramYellow);
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShaderYellow);

    // float firstTriangle[] = {
    //     -0.9f, -0.5f, 0.0f,
    //     0.0f, -0.5f, 0.0f,
    //     -0.9f, 0.5f, 0.0f};

    // float secondTriangle[] = {
    //     0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     0.9f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

    float rectangle[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, 15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3};

    // unsigned int VBO[2];
    // unsigned int VAO[2];
    unsigned int VBO;
    unsigned int VAO;
    // unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // glBindVertexArray(VAO);

    // glBindVertexArray(VAO[0]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(VAO[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    rectangleShader.use();
    rectangleShader.setInt("texture1", 0);
    // glUniform1i(glGetUniformLocation(rectangleShader.ID, "texture1"), 0);
    rectangleShader.setInt("texture2", 1);

    // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    // vec = trans * vec;
    // std::cout << vec.x << vec.y << vec.z << std::endl;

    // glm::mat4 projection = glm::mat4(1.0f);
    // projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    // rectangleShader.setMat4("projection", projection);

    // glfwSetCursorPosCallback(window, mouse_callback);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInpute(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // glm::mat4 transform  = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        // transform = glm::rotate(transform , (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

        // transform  = glm::scale(transform , glm::vec3(0.5, 0.5, 0.5));
        rectangleShader.use();

        // glm::mat4 model = glm::mat4(1.0f);

        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;
        // glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
        rectangleShader.setMat4("projection", projection);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        rectangleShader.setMat4("view", view);
        // glm::mat4 projection = glm::mat4(1.0f);
        // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        // glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        // glm::vec3 cameraDiraction = glm::normalize(cameraPos - cameraTarget);
        // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDiraction));
        // glm::vec3 cameraUp = glm::cross(cameraDiraction, cameraRight);

        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // unsigned int modelLoc = glGetUniformLocation(rectangleShader.ID, "model");
        // unsigned int viewLoc = glGetUniformLocation(rectangleShader.ID, "view");
        // int projLoc = glGetUniformLocation(rectangleShader.ID, "projection");

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // unsigned int transformLoc = glGetUniformLocation(rectangleShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            rectangleShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glUseProgram(shaderProgramOrange);
        // firstTriangleShader.use();
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        // firstTriangleShader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // int vertexColorLocation = glGetUniformLocation(shaderProgramOrange, "ourColor");

        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // glBindVertexArray(VAO[0]);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // secondTriangleShader.use();

        // glUseProgram(shaderProgramYellow);
        // glBindVertexArray(VAO[1]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteVertexArrays(2, VAO);
    // glDeleteBuffers(2, VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgramOrange);
    // glDeleteProgram(shaderProgramYellow);

    glfwTerminate();
    return 0;
}

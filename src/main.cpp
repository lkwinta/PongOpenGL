#include <iostream>
#include <chrono>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "Camera2D.h"
#include "Color.h"
#include "Rectangle.h"
#include "Font.h"
#include "Text.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, double deltaTime);

Rectangle* leftPaddle;
Rectangle* ball;
Rectangle* rightPaddle;
Rectangle* background;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pong Open GL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader rectShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

    background = new Rectangle({800-4, 600-4}, {400, 300}, rectShader, Color(40, 40, 40));
    leftPaddle = new Rectangle({30, 100}, {50, 300}, rectShader, Colors::White);
    ball = new Rectangle({10, 10}, {400, 300}, rectShader, Colors::White);
    rightPaddle = new Rectangle({30, 100}, {750, 300}, rectShader, Colors::White);

    std::chrono::time_point<std::chrono::high_resolution_clock> t1;
    std::chrono::time_point<std::chrono::high_resolution_clock> t2;

    Camera2D camera(glm::vec2(400, 300), 1.0f, 800, 600);

    Font f_arial(WINDOWS_LIBRARY, "arialbd.ttf", 48);
    Text t(&f_arial, "3 : 0");
    t.setPosition({350, 550});

    Font f_casc(WINDOWS_LIBRARY, "CascadiaCode.ttf", 48);
    t.setFont(&f_casc);

    while (!glfwWindowShouldClose(window)){
        t1 = std::chrono::high_resolution_clock::now();

        double deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2).count();

        glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        camera.setScreenSize(width, height);

        background->draw(camera);
        leftPaddle->draw(camera);
        ball->draw(camera);
        rightPaddle->draw(camera);

        t.draw(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
        processInput(window, deltaTime);

        t2 = t1;
    }

    glfwDestroyWindow(window);

    delete leftPaddle;
    delete ball;
    delete rightPaddle;
    delete background;

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, double deltaTime){
   if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y + 1.0f});
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y - 1.0f});
}
//
// Created by Lukasz on 22.07.2022.
//

#ifndef PONGOPENGL_WINDOW_H
#define PONGOPENGL_WINDOW_H

#include <chrono>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Camera2D.h"
#include "Color.h"


class Window {
public:
    Window(int _width, int _height, const std::string& name, bool resizeable);
    ~Window();

    Camera2D camera;

    double deltaTime;

    int windowWidth;
    int windowHeight;

    bool isOpen();
    void clearAndPollEvents();

    int queryKeyState(int keyCode);

    void setClearColor(Color _color);
    GLFWwindow* window;
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);



    Color clearColor = Colors::Black;

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
};


#endif //PONGOPENGL_WINDOW_H

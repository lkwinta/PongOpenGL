//
// Created by Lukasz on 22.07.2022.
//

#include "Window.h"

Window::Window(int _width, int _height, const std::string &name) : camera(CENTER, 1.0f, _width, _height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(_width, _height, name.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }

    windowWidth = _width;
    windowHeight = _height;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(window);
}

void Window::clearAndPollEvents() {
    t2 = t1;
    t1 = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2).count();

    glfwSwapBuffers(window);
    glfwPollEvents();

    glClearColor(clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
    glClear(GL_CLEAR_BUFFER);

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    camera.setScreenSize(windowWidth, windowHeight);
}

Window::~Window() {
    glfwDestroyWindow(window);
}

int Window::queryKeyState(int keyCode) {
    return glfwGetKey(window, keyCode);
};

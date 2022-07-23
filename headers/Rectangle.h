//
// Created by Lukasz on 21.07.2022.
//

#ifndef PONGOPENGL_RECTANGLE_H
#define PONGOPENGL_RECTANGLE_H

#include "glm/glm.hpp"

#include "Color.h"
#include "Shader.h"
#include "Camera2D.h"
#include "Window.h"

class Rectangle {
public:
    Rectangle(glm::vec2 _size, glm::vec2 pos, const std::string& vertexPath, const std::string& fragmentPath, Color _color);
    Rectangle(glm::vec2 _size, glm::vec2 pos, Shader& _shader, Color _color);

    void draw(Window* window);

    void setSize(glm::vec2 _size);
    void setPosition(glm::vec2 _position);
    void setRotationZ(float degrees);
    void setRotationX(float degrees);
    void setRotationY(float degrees);
    void setBackgroundColor(Color color);

    glm::vec2 getSize() const;
    glm::vec2 getPosition() const;
    float getRotationZ() const;
    float getRotationX() const;
    float getRotationY() const;
    Color getBackgroundColor() const;

private:
    void init();

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    glm::vec2 size{};
    glm::vec2 position{};
    float zRotationDegrees = 0;
    float xRotationDegrees = 0;
    float yRotationDegrees = 0;

    float vertices[12] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[6] = {
            0, 1, 3,
            1, 2, 3
    };

    Color backgroundColor;
    Shader shader;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
};


#endif //PONGOPENGL_RECTANGLE_H

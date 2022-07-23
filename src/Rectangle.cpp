//
// Created by Lukasz on 21.07.2022.
//

#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 _size, glm::vec2 pos, const std::string &vertexPath, const std::string &fragmentPath, Color _color) : shader(vertexPath, fragmentPath){
    size = _size;
    position = pos;
    backgroundColor = _color;
    //std::cout << _color.red << " " << _color.green << " " << _color.blue << std::endl;

    init();
}

Rectangle::Rectangle(glm::vec2 _size, glm::vec2 pos, Shader& _shader, Color _color) : shader(_shader){
    size = _size;
    position = pos;
    backgroundColor = _color;
    //std::cout << _color.red << " " << _color.green << " " << _color.blue << std::endl;
    init();
}

void Rectangle::draw(Window* window) {
    projection = window->camera.getProjectionMatrix();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));
    model = glm::rotate(model, glm::radians(xRotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(yRotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(zRotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("projection", projection);
    shader.setVec3("bgcolor", backgroundColor);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Rectangle::setSize(glm::vec2 _size) {
    size = _size;
}

void Rectangle::setPosition(glm::vec2 _position) { 
    position = _position;
}

void Rectangle::setRotationZ(float degrees){
    zRotationDegrees = degrees;
}

void Rectangle::setRotationX(float degrees){
    xRotationDegrees = degrees;
}

void Rectangle::setRotationY(float degrees){
    yRotationDegrees = degrees;
}

void Rectangle::setBackgroundColor(Color color){
    backgroundColor = color;
}

glm::vec2 Rectangle::getSize() const {
    return size;
}

glm::vec2 Rectangle::getPosition() const {
    return position;
}

float Rectangle::getRotationZ() const {
    return zRotationDegrees;
}

float Rectangle::getRotationX() const {
    return xRotationDegrees;
}

float Rectangle::getRotationY()const {
    return yRotationDegrees;
}

Color Rectangle::getBackgroundColor() const {
    return backgroundColor;
}

void Rectangle::init() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


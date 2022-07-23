//
// Created by Lukasz on 20.07.2022.
//

#include "Camera2D.h"

Camera2D::Camera2D(glm::vec2 _focusPoint, float _zoom, int _screenWidth, int _screenHeight) {
    focusPoint = _focusPoint;
    zoom = _zoom;
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    lookAt = CUSTOM_POINT;
}

Camera2D::Camera2D(LOOK_AT lookAt, float _zoom, int _screenWidth, int _screenHeight) {
    zoom = _zoom;
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    lookAt = CENTER;
    focusPoint = glm::vec2(_screenWidth/2, _screenHeight/2);
}

glm::mat4 Camera2D::getProjectionMatrix() const {
    glm::mat4 projection = glm::mat4x4(1.0f);
    glm::mat4 mat_zoom = glm::mat4x4(1.0f);

    projection = glm::ortho(focusPoint.x - (float)screenWidth / 2.0f,
                            focusPoint.x + (float)screenWidth / 2.0f,
                            focusPoint.y - (float)screenHeight / 2.0f,
                            focusPoint.y + (float)screenHeight / 2.0f,
                            -0.01f, 100.0f);

    mat_zoom = glm::scale(mat_zoom, glm::vec3(zoom, zoom, 1.0f));

    return mat_zoom * projection;
}

void Camera2D::setZoom(float _zoom){
    zoom = _zoom;
}

void Camera2D::setFocusPoint(glm::vec2 _focusPoint){
    focusPoint = _focusPoint;
}

void Camera2D::setScreenSize(int width, int height) {
    screenHeight = height;
    screenWidth = width;

    if(lookAt == CENTER)
        setFocusPoint({screenWidth/2, screenHeight/2});
}

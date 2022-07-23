//
// Created by Lukasz on 20.07.2022.
//

#ifndef PONGOPENGL_CAMERA2D_H
#define PONGOPENGL_CAMERA2D_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum LOOK_AT {
    CENTER,
    CUSTOM_POINT,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

class Camera2D {
public:
    Camera2D(glm::vec2 _focusPoint, float _zoom, int _screenWidth, int _screenHeight);
    Camera2D(LOOK_AT _lookAt, float _zoom, int _screenWidth, int _screenHeight);

    [[nodiscard]] glm::mat4 getProjectionMatrix() const;

    void setZoom(float _zoom);
    void setFocusPoint(glm::vec2 _focusPoint);

    void setScreenSize(int width, int height);
private:
    float zoom;
    glm::vec2 focusPoint{};
    LOOK_AT lookAt = CENTER;

    int screenWidth;
    int screenHeight;
};


#endif //PONGOPENGL_CAMERA2D_H

//
// Created by Lukasz on 21.07.2022.
//

#ifndef PONGOPENGL_COLOR_H
#define PONGOPENGL_COLOR_H

#include "glm/glm.hpp"

struct Color {
    float red;
    float green;
    float blue;
    float alpha = 1.0f;

    Color(){
        red = 0;
        green = 0;
        blue = 0;
    }

    Color(int _red, int _green, int _blue){
        red = (float)_red/(float)255;
        green = (float)_green/(float)255;
        blue = (float)_blue/(float)255;
    }

    Color(glm::vec3 _color){
        red = _color.x;
        green = _color.y;
        blue = _color.z;
    }

    Color(int _red, int _green, int _blue, int _alpha){
        red = (float)_red/(float)255;
        green = (float)_green/(float)255;
        blue = (float)_blue/(float)255;
        alpha = (float)_alpha/(float)255;
    }

    Color(glm::vec4 _color){
        red = _color.x;
        green = _color.y;
        blue = _color.z;
        alpha = _color.w;
    }

    [[nodiscard]] glm::vec3 asVec() const{
        return {(float)red, (float)green, (float)blue};
    }

    operator glm::vec3() const { return asVec();};
};

namespace Colors {
    [[maybe_unused]] const Color Red = Color(255, 0, 0);
    [[maybe_unused]] const Color Green = Color(0, 255, 0);
    [[maybe_unused]] const Color Blue = Color(0, 0, 255);
    [[maybe_unused]] const Color White = Color(255, 255, 255);
    [[maybe_unused]] const Color Black = Color(0, 0, 0);
    [[maybe_unused]] const Color Yellow = Color(255, 255, 0);
    [[maybe_unused]] const Color Magenta = Color(255, 0, 255);
    [[maybe_unused]] const Color Cyan = Color(0, 255, 255);
}


#endif //PONGOPENGL_COLOR_H

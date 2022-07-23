//
// Created by Lukasz on 21.07.2022.
//

#ifndef PONGOPENGL_FONT_H
#define PONGOPENGL_FONT_H

#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

enum FONT_TYPE {
    CUSTOM_FONT,
    WINDOWS_LIBRARY,
};

class Font {
public:
    FT_Face fontFace{};

    Font(FONT_TYPE type, const std::string& path, unsigned int pixelSize);

    void fontDone();
private:
    FT_Library freetype{};
};


#endif //PONGOPENGL_FONT_H

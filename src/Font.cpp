//
// Created by Lukasz on 21.07.2022.
//

#include "Font.h"

Font::Font(FONT_TYPE type, const std::string &path, unsigned int pixelSize) {

    if (FT_Init_FreeType(&freetype))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        throw std::runtime_error("Could not init FreeType Library");
    }

    if(type == WINDOWS_LIBRARY){
        if (FT_New_Face(freetype, ("C:/Windows/Fonts/" + path).c_str(), 0, &fontFace))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            throw std::runtime_error("Failed to load font");
        }
    } else {
        if (FT_New_Face(freetype, path.c_str(), 0, &fontFace))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            throw std::runtime_error("Failed to load font");
        }
    }


    FT_Set_Pixel_Sizes(fontFace, 0, pixelSize);
}

void Font::fontDone() {
    FT_Done_Face(fontFace);
    FT_Done_FreeType(freetype);
};
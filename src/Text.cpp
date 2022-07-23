//
// Created by Lukasz on 21.07.2022.
//

#include "Text.h"

#include <utility>

Text::Text(Font* _font, std::string _text) {
    shader = new Shader("shaders/fonts/fontsVertexShader.vert", "shaders/fonts/fontsFragmentShader.frag");
    font = _font;
    createCharacters();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    text = std::move(_text);
}

Text::~Text() {
    delete shader;
}

void Text::createCharacters() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char c = 0; c < 255; c++){
        if(FT_Load_Char(font->fontFace, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        characters.insert(std::pair<char, Character> {c, {
                createTexture(font->fontFace->glyph->bitmap),
                glm::ivec2(font->fontFace->glyph->bitmap.width, font->fontFace->glyph->bitmap.rows),
                glm::ivec2 (font->fontFace->glyph->bitmap_left, font->fontFace->glyph->bitmap_top),
                static_cast<GLuint>(font->fontFace->glyph->advance.x)
        }});
    }

    font->fontDone();
}

GLuint Text::createTexture(FT_Bitmap& bitmap) {
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            (GLsizei) bitmap.width,
            (GLsizei) bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void Text::setFont(Font* _font) {
    font = _font;
    characters.clear();
    createCharacters();
}

void Text::setPosition(glm::vec2 pos) {
    position = pos;
}

void Text::draw(Window *window) {
    projection = glm::ortho(0.0f, (float)window->windowWidth, 0.0f, (float)window->windowHeight, -3.0f, 100.0f);

    shader->use();
    shader->setVec3("textColor", textColor);
    shader->setMat4("projection", projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    Character character{};

    glm::vec2 tempPosition = position;

    for(c = text.begin(); c != text.end(); c++){
        character = characters[*c];

        float x_pos = tempPosition.x + (float)character.Bearing.x * scale;
        float y_pos = tempPosition.y - (float)(character.Size.y - character.Bearing.y) * scale;

        float width = (float)character.Size.x * scale;
        float height = (float)character.Size.y * scale;

        float vertices[6][4] = {
                //  x                          y                    texture coordinates
                { x_pos,            y_pos + height,     0.0f, 0.0f },
                { x_pos,            y_pos,              0.0f, 1.0f },
                { x_pos + width,    y_pos,              1.0f, 1.0f },

                { x_pos,            y_pos + height,     0.0f, 0.0f },
                { x_pos + width,    y_pos,              1.0f, 1.0f },
                { x_pos + width,    y_pos + height,     1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, character.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        tempPosition.x += (float)(character.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::setText(std::string _text) {
    text = std::move(_text);
}

void Text::setColor(Color _color) {
    textColor = _color;
}


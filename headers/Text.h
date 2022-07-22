//
// Created by Lukasz on 21.07.2022.
//

#ifndef PONGOPENGL_TEXT_H
#define PONGOPENGL_TEXT_H

#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "Font.h"
#include "Color.h"

class Text {
public:
    Text(Font* _font, std::string _text);
    ~Text();

    void setFont(Font* _font);
    void setPosition(glm::vec2 pos);

    void draw(GLFWwindow* window);
private:
    void createCharacters();
    static GLuint createTexture(FT_Bitmap& bitmap);

    struct Character {
        GLuint TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint Advance;
    };

    GLuint VAO{};
    GLuint VBO{};

    std::string text;

    std::map<char, Character> characters;

    Shader* shader;
    Font* font;

    int screenWidth{};
    int screenHeight{};

    glm::mat4 projection = glm::mat4(1.0f);
    glm::vec2 position{};

    Color textColor = Colors::White;

    float scale = 1.0f;
};


#endif //PONGOPENGL_TEXT_H

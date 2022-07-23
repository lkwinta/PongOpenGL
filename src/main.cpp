#include <iostream>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "Color.h"
#include "Rectangle.h"
#include "Font.h"
#include "Text.h"
#include "Window.h"

void processInput(Window* window);

Rectangle* leftPaddle;
Rectangle* ball;
Rectangle* rightPaddle;
Rectangle* background;

int main() {
    auto window = new Window(800, 600, "Pong OpenGL");

    Shader rectShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

    background = new Rectangle({800, 600}, {400, 300}, rectShader, Color(40, 40, 40));
    leftPaddle = new Rectangle({20, 100}, {50, 300}, rectShader, Colors::White);
    ball = new Rectangle({10, 10}, {400, 300}, rectShader, Colors::White);
    rightPaddle = new Rectangle({20, 100}, {750, 300}, rectShader, Colors::White);

    Font f_casc(WINDOWS_LIBRARY, "CascadiaCode.ttf", 20);
    Font f_roboto(CUSTOM_FONT, "fonts/Roboto-Regular.ttf", 48);

    Text score(&f_roboto, "3 : 0");
    score.setPosition({350, 550});
    score.setText("4 : 0");

    Text fps(&f_casc, "2344");
    fps.setPosition({0, 580});
    fps.setColor(Colors::Yellow);

    while (window->isOpen()){
        window->clearAndPollEvents();

        background->draw(window);
        leftPaddle->draw(window);
        ball->draw(window);
        rightPaddle->draw(window);

        fps.setText(std::to_string((int)(60/window->deltaTime)));

        score.draw(window);
        fps.draw(window);


        processInput(window);
    }

    delete window;

    delete leftPaddle;
    delete ball;
    delete rightPaddle;
    delete background;

    return 0;
}

void processInput(Window* window){
   if(window->queryKeyState(GLFW_KEY_W) == GLFW_PRESS)
       leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y + 2.0f});
   if(window->queryKeyState(GLFW_KEY_S) == GLFW_PRESS)
       leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y - 2.0f});
   if(window->queryKeyState(GLFW_KEY_UP) == GLFW_PRESS)
       rightPaddle->setPosition({rightPaddle->getPosition().x, rightPaddle->getPosition().y + 2.0f});
   if(window->queryKeyState(GLFW_KEY_DOWN) == GLFW_PRESS)
       rightPaddle->setPosition({rightPaddle->getPosition().x, rightPaddle->getPosition().y - 2.0f});
}
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

float ballVelocityX = 1.0f;
float ballVelocityY = 0.0f;

Rectangle* leftPaddle;
Rectangle* ball;
Rectangle* rightPaddle;
Rectangle* background;

int main() {
    auto window = new Window(800, 600, "Pong OpenGL", false);

    Shader rectShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

    background = new Rectangle({800, 600}, {400, 300}, rectShader, Color(40, 40, 40));
    leftPaddle = new Rectangle({20, 100}, {50, 300}, rectShader, Colors::White);
    ball = new Rectangle({10, 10}, {400, 300}, rectShader, Colors::White);
    rightPaddle = new Rectangle({20, 100}, {750, 300}, rectShader, Colors::White);

    Font f_casc(WINDOWS_LIBRARY, "CascadiaCode.ttf", 20);
    Font f_roboto(CUSTOM_FONT, "fonts/Roboto-Regular.ttf", 48);

    std::string score_str = "0 : 0";
    int score_left = 0;
    int score_right = 0;

    Text score(&f_roboto, "0 : 0");
    score.setPosition({350, 550});


    Text fps(&f_casc, "2344");
    fps.setPosition({0, 580});
    fps.setColor(Colors::Yellow);

    while (window->isOpen()){
        window->clearAndPollEvents();

        background->draw(window);
        leftPaddle->draw(window);
        rightPaddle->draw(window);

        ball->setPosition({ball->getPosition().x + ballVelocityX, ball->getPosition().y + ballVelocityY});

        glm::vec2 ballPos = ball->getPosition();
        glm::vec2 ballSize = ball->getSize();

        glm::vec2 rpadPos = rightPaddle->getPosition();
        glm::vec2 rpadSize = rightPaddle->getSize();

        glm::vec2 lpadPos = leftPaddle->getPosition();
        glm::vec2 lpadSize = leftPaddle->getSize();

        if(ballPos.x + ballSize.x/2 > rpadPos.x - rpadSize.x/2 &&
            ballPos.y - ballSize.y/2 < rpadPos.y + rpadSize.y/2 &&
                ballPos.y + ballSize.y/2 > rpadPos.y - rpadSize.y/2){

            double x = (ballPos.y - rpadPos.y)/(rpadSize.y/2);
            ballVelocityX *= -1;
            ballVelocityY += x;
        }

        if(ballPos.x - ballSize.x/2 < lpadPos.x + lpadSize.x/2 &&
           ballPos.y - ballSize.y/2 < lpadPos.y + lpadSize.y/2 &&
           ballPos.y + ballSize.y/2 > lpadPos.y - lpadSize.y/2){
            ballVelocityX *= -1;
            double x = (ballPos.y - rpadPos.y)/(rpadSize.y/2);
            ballVelocityY += x;
        }

        if(ballPos.y - ballSize.y < 0 || ballPos.y + ballSize.y > (float)window->windowHeight)
            ballVelocityY *= -1;

        if(ballPos.x < 0) {
            ball->setPosition({window->windowWidth/2, window->windowHeight/2});
            score_right++;
            ballVelocityY = 0;
        }

        if(ballPos.x > (float)window->windowWidth){
            ball->setPosition({window->windowWidth/2, window->windowHeight/2});
            ballVelocityY = 0;
            score_left++;
        }

        ball->draw(window);

        score_str = std::to_string(score_left) + " : " + std::to_string(score_right);

        fps.setText(std::to_string((int)(60/window->deltaTime)));
        score.setText(score_str);

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
   if(window->queryKeyState(GLFW_KEY_W) == GLFW_PRESS && leftPaddle->getPosition().y + leftPaddle->getSize().y/2 < (float)window->windowHeight)
       leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y + 4.0f});
   if(window->queryKeyState(GLFW_KEY_S) == GLFW_PRESS && leftPaddle->getPosition().y - leftPaddle->getSize().y/2 > 0)
       leftPaddle->setPosition({leftPaddle->getPosition().x, leftPaddle->getPosition().y - 4.0f});
   if(window->queryKeyState(GLFW_KEY_UP) == GLFW_PRESS && rightPaddle->getPosition().y + rightPaddle->getSize().y/2  < (float)window->windowHeight)
       rightPaddle->setPosition({rightPaddle->getPosition().x, rightPaddle->getPosition().y + 4.0f});
   if(window->queryKeyState(GLFW_KEY_DOWN) == GLFW_PRESS && rightPaddle->getPosition().y - rightPaddle->getSize().y/2 > 0)
       rightPaddle->setPosition({rightPaddle->getPosition().x, rightPaddle->getPosition().y - 4.0f});
}
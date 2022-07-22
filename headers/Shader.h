//
// Created by Lukasz on 21.07.2022.
//

#ifndef PONGOPENGL_SHADER_H
#define PONGOPENGL_SHADER_H

#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    GLuint shaderProgram{};

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader(const Shader& shader);
    ~Shader();

    void use() const;

    void setMat4(const std::string &name, glm::mat4& mat) const;
    void setVec3(const std::string &name, glm::vec3 vec) const;

    void setVertexPath(const std::string& _vertexPath);
    void setFragmentPath(const std::string& _fragmentPath);
private:
    std::string vertexPath;
    std::string fragmentPath;

    std::string read_file(const std::string& path);

    void createFragmentShader(const std::string& path);
    void createVertexShader(const std::string& path);
    void compileShaders();
    void recompileShaders();

    std::ifstream input{};

    GLuint vertexShader{};
    GLuint fragmentShader{};

    GLint success{};
    char infoLog[512]{};
};

#endif //PONGOPENGL_SHADER_H

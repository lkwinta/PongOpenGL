//
// Created by Lukasz on 19.07.2022.
//


#include "Shader.h"

std::string Shader::read_file(const std::string &path) {
    std::string file;
    char c;

    input.close();
    input.clear();
    input.open(path);

    while(input.get(c)){
        file += c;
    }

    input.close();

    return file;
}

void Shader::createFragmentShader(const std::string& path) {
    std::string fragmentStr = read_file(path);
    std::cout << fragmentStr << std::endl;
    const char* fragment_cstr = fragmentStr.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_cstr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::createVertexShader(const std::string& path) {
    std::string vertexStr = read_file(path);
    std::cout << vertexStr << std::endl;
    const char* vertex_cstr = vertexStr.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_cstr, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::compileShaders() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(shaderProgram);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

[[maybe_unused]] Shader::Shader(const std::string& _vertexPath, const std::string& _fragmentPath) {
    vertexPath = _vertexPath;
    fragmentPath = _fragmentPath;

    createVertexShader(_vertexPath);
    createFragmentShader(_fragmentPath);

    compileShaders();
}

void Shader::setMat4(const std::string &name, glm::mat4& mat) const{
    GLint matLoc = glGetUniformLocation(shaderProgram, name.c_str());
    glad_glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string &name, glm::vec3 vec) const {
    GLint vecLoc = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3f(vecLoc, vec.x, vec.y, vec.z);
}

Shader::Shader(const Shader &shader) {
    shaderProgram = shader.shaderProgram;
    vertexPath = shader.vertexPath;
    fragmentPath = shader.fragmentPath;
}

void Shader::setVertexPath(const std::string& _vertexPath) {
    vertexPath = _vertexPath;
    recompileShaders();
}

void Shader::setFragmentPath(const std::string& _fragmentPath) {
    fragmentPath = _fragmentPath;
    recompileShaders();
}

void Shader::recompileShaders() {
    glDeleteProgram(shaderProgram);

    createVertexShader(vertexPath);
    createFragmentShader(fragmentPath);
    compileShaders();
}





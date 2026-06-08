#ifndef SHADER_H
#define SHADER_H

#include "Math.h"

class Shader
{
private:
    unsigned int ID;
    unsigned int vertexShader, fragmentShader;

public:
    Shader(std::string vShader, std::string fShader);
    ~Shader();

    void Use();
    unsigned int GetLoc(const std::string& name);
};

#endif
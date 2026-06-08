#ifndef WORLD_h
#define WORLD_h

#include <iostream>
#include <SDL3/SDL.h>

#include "Shader.h"
#include "Camera.h"

#include <vector>
#include "Vertex.h"

class World
{
private:
    bool* run;
    SDL_Window* window;  

    int width, height;

    const bool* keyboards;

    SDL_GLContext glContext;

    unsigned int VBO, VAO, EBO;
    Shader* shader;

    Camera *camera;

    float m_x, m_y;

    void GetWindowSize(int *width, int *height);

    unsigned int SSBO[2];
    int currSSBO = 0;
    std::vector<Vertex> worldVertices;

    unsigned int worldTex[1000];

    void Transform(std::vector<Vertex> *vertices, Matrix mat);
public:
    World(SDL_Window* window, bool* run);
    ~World();

    void Render(float deltaTime, bool *relative);
};

#endif
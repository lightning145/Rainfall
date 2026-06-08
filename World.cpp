#include "World.h"
#include "Math.h"
#include <glad.h>

#include "Texture.h"

World::World(SDL_Window* window, bool* run) : 
    window(window), run(run)
{
    GetWindowSize(&this->width, &this->height);

    keyboards = SDL_GetKeyboardState(NULL);

    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    shader = new Shader("vertex.glsl", "fragment.glsl");
    shader->Use();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //Use Left!
    camera = new Camera(
        FIRST_PERSON, 
        VEC3(0.0f, 0.0f, -3.0f),

        VEC3(1.0f, 0.0f ,0.0f),
        VEC3(0.0f, 1.0f, 0.0f),
        VEC3(0.0f, 0.0f, 1.0f)
    );

    worldVertices = {
        // ==========================================
    // 1. 大正方体 (物体 - 物体颜色: 黑色, 类型: VEC(1.0f))
    // ==========================================
    
    // 前面 (Front Face) - 法线 (0, 0, 1)
    Vertex(POINT(-1.0f, -1.0f,  1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f,  1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f,  1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f,  1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // 后面 (Back Face) - 法线 (0, 0, -1)
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f, -1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f, -1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f, -1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f, -1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // 左面 (Left Face) - 法线 (-1, 0, 0)
    Vertex(POINT(-1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f, -1.0f), VEC2(0.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(0.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(0.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f,  1.0f), VEC2(1.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // 右面 (Right Face) - 法线 (1, 0, 0)
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(0.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f, -1.0f), VEC2(1.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f, -1.0f), VEC2(1.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f, -1.0f), VEC2(1.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(0.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f,  1.0f), VEC2(0.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // 底面 (Bottom Face) - 法线 (0, -1, 0)
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f, -1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f,  1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f, -1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f, -1.0f,  1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f, -1.0f,  1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // 顶面 (Top Face) - 法线 (0, 1, 0)
    Vertex(POINT(-1.0f,  1.0f, -1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f,  1.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT(-1.0f,  1.0f, -1.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f,  1.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),
    Vertex(POINT( 1.0f,  1.0f, -1.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(0.0f, 0.0f, 0.0f), VEC(1.0f)),

    // ==========================================
    // 2. 小正方体 (光源 - 颜色: 白色, 类型: VEC(0.0f))
    // Center: (0.0f, 3.0f, 0.0f), Size: 0.4
    // ==========================================
    
    // 前面 (Front Face)
    Vertex(POINT(-0.2f, 2.8f,  0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f,  0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f,  0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f,  0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, 1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 后面 (Back Face)
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f, -0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f, -0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f, -0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f, -0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, 0.0f, -1.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 左面 (Left Face)
    Vertex(POINT(-0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f, -0.2f), VEC2(0.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(0.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(0.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f,  0.2f), VEC2(1.0f, 0.0f), VEC3(-1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 右面 (Right Face)
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(0.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f, -0.2f), VEC2(1.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f, -0.2f), VEC2(1.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f, -0.2f), VEC2(1.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(0.0f, 1.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f,  0.2f), VEC2(0.0f, 0.0f), VEC3(1.0f, 0.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 底面 (Bottom Face)
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f, -0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f,  0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f, -0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 2.8f,  0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 2.8f,  0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 顶面 (Top Face)
    Vertex(POINT(-0.2f, 3.2f, -0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f,  0.2f), VEC2(0.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT(-0.2f, 3.2f, -0.2f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f,  0.2f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),
    Vertex(POINT( 0.2f, 3.2f, -0.2f), VEC2(1.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(0.0f)),

    // 三角形 1 (左下、右下、右上)
    Vertex(POINT(-5.0f, -1.0f, -5.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f)),
    Vertex(POINT( 5.0f, -1.0f, -5.0f), VEC2(1.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f)),
    Vertex(POINT( 5.0f, -1.0f,  5.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f)),
    
    // 三角形 2 (左下、右上、左上)
    Vertex(POINT(-5.0f, -1.0f, -5.0f), VEC2(0.0f, 0.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f)),
    Vertex(POINT( 5.0f, -1.0f,  5.0f), VEC2(1.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f)),
    Vertex(POINT(-5.0f, -1.0f,  5.0f), VEC2(0.0f, 1.0f), VEC3(0.0f, 1.0f, 0.0f), VEC3(1.0f, 1.0f, 1.0f), VEC(1.0f))
    };

    for (int i = 36; i < 72; i++)
    {
        worldVertices[i].pos = worldVertices[i].pos * Matrix(1.0f, 0.0f, 0.0f, 2.0f,
                                                             0.0f, 1.0f, 0.0f, -1.0f,
                                                             0.0f, 0.0f, 1.0f, 0.0f,
                                                             0.0f, 0.0f, 0.0f, 1.0f);
    }

    for (int i = 72; i < 78; i++)
    {
        worldVertices[i].pos = worldVertices[i].pos * Matrix(1.0f, 0.0f, 0.0f, 0.0f,
                                                             0.0f, 1.0f, 0.0f, -2.0f,
                                                             0.0f, 0.0f, 1.0f, 0.0f,
                                                             0.0f, 0.0f, 0.0f, 1.0f);
    }

    Transform(&worldVertices, Matrix(0.5f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.5f, 0.0f ,0.0f,
                                     0.0f, 0.0f, 0.5f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f));

    glGenBuffers(2, SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO[currSSBO]);

    glBufferData(GL_SHADER_STORAGE_BUFFER, worldVertices.size() * sizeof(Vertex), worldVertices.data(), GL_STATIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO[currSSBO]);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    worldTex[0] = LoadTexture("image.jpg");

}

World::~World()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, SSBO);

    DeleteTexture(worldTex[0]);
    delete camera;
    delete shader;
    SDL_GL_DestroyContext(glContext);
}

void World::Render(float deltaTime, bool *relvative)
{
    GetWindowSize(&this->width, &this->height);

    if(keyboards[SDL_SCANCODE_ESCAPE])
    {
        *run = false;
    }

    SDL_GetRelativeMouseState(&m_x, &m_y);

    if (*relvative)
    {
        camera->Rotate(m_y * 0.1f, m_x * 0.1f, 0.0f);
        
        if (keyboards[SDL_SCANCODE_W])
        {
            camera->Move(1.0f * deltaTime, 0.0f, 0.0f);
        }

        if (keyboards[SDL_SCANCODE_S])
        {
            camera->Move(-1.0f * deltaTime, 0.0f, 0.0f);
        }

        if (keyboards[SDL_SCANCODE_A])
        {
            camera->Move(0.0f, -1.0f * deltaTime, 0.0f);
        }

        if (keyboards[SDL_SCANCODE_D])
        {
            camera->Move(0.0f, 1.0f * deltaTime, 0.0f);
        }

    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Use();

    glUniform3f(shader->GetLoc("camPos"), camera->GetPos().x, camera->GetPos().y, camera->GetPos().z);
    glUniform3f(shader->GetLoc("camRight"), camera->GetRight().x, camera->GetRight().y, camera->GetRight().z);
    glUniform3f(shader->GetLoc("camUp"), camera->GetUp().x, camera->GetUp().y, camera->GetUp().z);
    glUniform3f(shader->GetLoc("camForward"), camera->GetForward().x, camera->GetForward().y, camera->GetForward().z);

    glUniform1f(shader->GetLoc("width"), (float)width);
    glUniform1f(shader->GetLoc("height"), (float)height);

    currSSBO = (currSSBO + 1) % 2;
    unsigned int activeSSBO = SSBO[currSSBO];

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, activeSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, worldVertices.size() * sizeof(Vertex), worldVertices.data(), GL_DYNAMIC_DRAW);
    
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, activeSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glUniform1i(shader->GetLoc("worldTex[0]"), 0);
    BindTexture(worldTex[0], 0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}

void World::GetWindowSize(int *width, int *height)
{
    SDL_GetWindowSize(window, width, height);
}

void World::Transform(std::vector<Vertex> *vertices, Matrix mat)
{
    for (size_t i = 0; i < vertices->size(); i++)
    {
        (*vertices)[i].pos = mat * (*vertices)[i].pos;
    }
}
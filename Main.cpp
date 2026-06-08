#include "World.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Rainfall",
        1280, 720, SDL_WINDOW_OPENGL
    );

    bool relative = true;

    SDL_Event event;
    bool run = true;

    World world = World(window, &run);

    static float lastTime = (float)SDL_GetTicks();
    while(run)
    {
        SDL_SetWindowRelativeMouseMode(window, relative);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                run = false;
            }

            if(event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_SPACE)
                {
                    relative = !relative;
                }
            }
        }

        float currentTime = (float)SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) * 0.001f;

        world.Render(deltaTime, &relative);
        
        lastTime = currentTime;
    }

    SDL_Quit();
    return 0;
}

#include "../../vendor/sdl/include/SDL2/SDL.h"

void SDL_events(bool *running, int *keyboard)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_QUIT)
        {
            *running = false;
        }
        else if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.scancode < SDL_NUM_SCANCODES)
        {
            keyboard[event.key.keysym.scancode] = 1;
        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0 && event.key.keysym.scancode < SDL_NUM_SCANCODES)
        {
            keyboard[event.key.keysym.scancode] = 0;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            printf("click handler not implemented");
        }
    }
}
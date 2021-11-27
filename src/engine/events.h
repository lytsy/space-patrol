
#include "../../vendor/sdl/include/SDL2/SDL.h"

class Mouse
{
public:
    int x;
    int y;
    int buttons[SDL_MAX_UINT8];
};

void SDL_events(bool *running, int *keyboard, Mouse *mouse)
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
            mouse->buttons[event.button.button] = 1;
            mouse->x = event.button.x;
            mouse->y = event.button.y;
        }
    }
}
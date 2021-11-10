
#include "../../vendor/sdl/include/SDL2/SDL.h"

void keydown_handler(SDL_Scancode key_code);
void keyup_handler(SDL_Scancode key_code);
void click_handler(SDL_MouseButtonEvent event);

void SDL_events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_QUIT)
        {
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            keydown_handler(event.key.keysym.scancode);
        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            keyup_handler(event.key.keysym.scancode);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            click_handler(event.button);
        }
    }
}

#include "headers/sdl_controller.h"
#include "headers/main.h"

int main(int argc, char **argv)
{
    hide_console();
    sdl.init();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
            }
        }
    }
    sdl.destroy();
    return 0;
}
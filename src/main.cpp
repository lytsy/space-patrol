
#include "headers/sdl_controller.h"
void sdl_init(void);
void sdl_destroy(void);

int main(int argc, char **argv)
{
    sdl_init();

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
    sdl_destroy();
    return 0;
}
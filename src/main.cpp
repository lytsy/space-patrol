
#include "headers/sdl_controller.h"
#include "headers/sdl_sound.h"
#include "headers/sdl_image.h"
#include "headers/main.h"

int main(int argc, char **argv)
{
    hide_console();
    sdl.init();

    SDL_Sound test_sound("assets/sound.mp3");
    test_sound.play();
    test_sound.destroy();

    SDL_Img test_img("assets/test_img.png", sdl.renderer);
    test_img.set_dest(20, 20, 50, 50);

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

        SDL_RenderClear(sdl.renderer);
        test_img.draw();
        SDL_RenderPresent(sdl.renderer);
        SDL_Delay(16);
    }

    test_img.destroy();
    sdl.destroy();
    return 0;
}
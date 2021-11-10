
#include "engine/engine.h"
#include "engine/sound.h"
#include "engine/image.h"
#include "engine/text.h"
#include "engine/events.h"
#include "engine/main.h"

int main(int argc, char **argv)
{
    hide_console();
    sdl.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();
    test_sound.destroy();

    Image test_img("assets/test_img.png", sdl.renderer);
    test_img.set_dest(20, 20, 50, 50);

    Text test_text("hello!", sdl.renderer, sdl.font);

    bool running = true;
    while (running)
    {
        SDL_events();

        SDL_RenderClear(sdl.renderer);
        test_img.draw();
        test_text.draw();
        SDL_RenderPresent(sdl.renderer);
        SDL_Delay(16);
    }

    test_img.destroy();
    sdl.destroy();
    return 0;
}

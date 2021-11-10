
#include "engine/engine.h"
#include "engine/sound.h"
#include "engine/image.h"
#include "engine/text.h"

int main(int argc, char **argv)
{
    sdl.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Image test_img("assets/test_img.png", sdl.renderer);
    test_img.set_dest(20, 20, 50, 50);

    Text test_text("hello!", sdl.renderer, sdl.font);

    while (sdl.running)
    {
        sdl.handle_events();
        sdl.render_clear();

        test_img.draw();
        test_text.draw();

        sdl.render_present();
        SDL_Delay(16);
    }

    test_sound.destroy();
    test_img.destroy();
    sdl.destroy();
    return 0;
}

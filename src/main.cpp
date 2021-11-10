
#include "engine/engine.h"
#include "engine/sound.h"
#include "engine/image.h"
#include "engine/text.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Image test_img("assets/test_img.png", engine.renderer);
    test_img.set_dest(20, 20, 50, 50);

    Text test_text("hello!", engine.renderer, engine.font);

    while (engine.running)
    {
        engine.handle_events();
        engine.render_clear();

        test_img.draw();
        test_text.draw();

        engine.render_present();
        SDL_Delay(16);
    }

    test_sound.destroy();
    test_img.destroy();
    engine.destroy();
    return 0;
}

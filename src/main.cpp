
#include "engine/engine.h"
#include "media_types/sound.h"
#include "media_types/image.h"
#include "media_types/text.h"
#include "game/background.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Image test_img("assets/test_img.png", engine.renderer);
    test_img.set_dest(20, 20, 50, 50);

    Text test_text("hello!", engine.renderer, engine.font);

    Background background("assets/images/backgrounds/bg_0.jpg", engine.renderer, engine.window);

    while (engine.running)
    {

        engine.handle_events();
        engine.render_clear();
        engine.check_errors();

        background.refresh();
        background.draw();
        test_img.draw();
        test_text.draw();

        engine.render_present();
        SDL_Delay(5);
    }

    test_sound.destroy();
    test_img.destroy();
    background.destroy();
    engine.destroy();
    return 0;
}

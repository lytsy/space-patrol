
#include "engine/engine.h"
#include "media_types/sound.h"
#include "media_types/image.h"
#include "media_types/text.h"
#include "game/background.h"
#include "game/player.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Text test_text("hello!", engine.renderer, engine.font);

    Background background("assets/images/backgrounds/bg_0.jpg", engine.renderer, engine.window);

    Player player(engine.renderer, engine.window);

    while (engine.running)
    {

        engine.handle_events();
        engine.render_clear();
        engine.check_errors();
        engine.count_delta_time();
        engine.count_fps();

        player.handle_keypress(engine.keyboard);

        background.refresh(engine.dt);
        player.refresh(engine.dt);

        background.draw();
        test_text.draw();
        player.draw();
        engine.draw_fps();

        engine.render_present();
        SDL_Delay(5);
    }

    test_sound.destroy();
    background.destroy();
    player.destroy();
    engine.destroy();
    return 0;
}

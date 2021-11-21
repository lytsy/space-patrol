
#include "engine/engine.h"
#include "media_types/sound.h"
#include "game/game.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Game *game = new Game(engine.window_state);

    while (engine.running)
    {

        engine.handle_events();
        engine.render_clear();
        engine.check_errors();
        engine.count_delta_time();
        engine.count_fps();
        engine.refresh_screen();

        game->handle_events(engine.dt, engine.keyboard);
        game->refresh(engine.dt);

        game->draw();
        engine.draw_fps();
        engine.render_present();
        SDL_Delay(5);
    }

    test_sound.destroy();
    game->destroy();
    engine.destroy();
    return 0;
}

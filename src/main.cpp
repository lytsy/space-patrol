
#include "engine/engine.h"
#include "game/game.h"

int main(int argc, char **argv)
{
    engine.init();
    Game *game = new Game(engine.window_state, engine.font);

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

        if (game->is_play())
        {
            engine.draw_fps();
        }
        engine.render_present();
        SDL_Delay(5);
    }

    game->destroy();
    engine.destroy();
    return 0;
}

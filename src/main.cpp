
#include "engine/engine.h"
#include "media_types/sound.h"
#include "media_types/image.h"
#include "game/background.h"
#include "game/player.h"
#include "game/bullet_list.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Background background("assets/images/backgrounds/bg_0.jpg", engine.renderer, engine.window);

    Bullet_list *bullet_list = new Bullet_list();
    Player player(engine.renderer, engine.window, bullet_list);

    while (engine.running)
    {

        engine.handle_events();
        engine.render_clear();
        engine.check_errors();
        engine.count_delta_time();
        engine.count_fps();

        player.handle_keypress(engine.keyboard, engine.dt);

        background.refresh(engine.dt);
        player.refresh(engine.dt);
        bullet_list->refresh_bullets_positions(engine.dt);
        bullet_list->destroy_remote_bullets();

        background.draw();
        player.draw();
        bullet_list->draw_bullets();
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

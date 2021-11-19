
#include "engine/engine.h"
#include "media_types/sound.h"
#include "media_types/image.h"
#include "game/background.h"
#include "game/player.h"
#include "game/bullet_list.h"
#include "game/enemy_list.h"

int main(int argc, char **argv)
{
    engine.init();

    Sound test_sound("assets/sound.mp3");
    test_sound.play();

    Background background(engine.window_state);

    Bullet_list *bullet_list = new Bullet_list();
    Enemy_list *enemy_list = new Enemy_list(engine.window_state, bullet_list);
    Player player(engine.window_state, bullet_list);

    while (engine.running)
    {

        engine.handle_events();
        engine.render_clear();
        engine.check_errors();
        engine.count_delta_time();
        engine.count_fps();
        engine.refresh_screen();

        player.handle_keypress(engine.keyboard, engine.dt);

        background.refresh(engine.dt);
        player.refresh(engine.dt);
        bullet_list->refresh_bullets_positions(engine.dt);
        bullet_list->destroy_remote_bullets();
        enemy_list->spawn_enemys();
        enemy_list->refresh_enemys_positions(engine.dt);
        enemy_list->destroy_enemys();
        enemy_list->check_collision(bullet_list);

        background.draw();
        enemy_list->draw_enemys();
        bullet_list->draw_bullets();
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

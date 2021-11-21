#include "../media_types/image.h"
#include "background.h"
#include "bullet_list.h"
#include "enemy_list.h"
#include "player.h"

#define MESSAGES_OFFSET_RELATIVE 0.01

class Game
{
public:
    int score = 0;
    Background *background;
    Bullet_list *bullet_list;
    Enemy_list *enemy_list;
    Player *player;

    Game(Window_State window_state, TTF_Font *engine_font)
    {
        renderer = window_state.renderer;
        screen = window_state.screen;
        background = new Background(window_state);
        bullet_list = new Bullet_list();
        enemy_list = new Enemy_list(window_state, bullet_list);
        player = new Player(window_state, bullet_list);
        font = engine_font;

        _init_score();
    }

    void handle_events(long dt, int *keyboard)
    {
        player->handle_keypress(keyboard, dt);
    }

    void refresh(long dt)
    {
        background->refresh(dt);
        player->refresh(engine.dt);
        collisions();

        bullet_list->refresh_bullets_positions(dt);
        bullet_list->destroy_remote_bullets();

        enemy_list->refresh_enemys_positions(dt);
        enemy_list->delete_dead_enemys();
        enemy_list->spawn_enemys();

        _refresh_score_message();
    }

    void draw()
    {
        background->draw();
        enemy_list->draw_enemys();
        bullet_list->draw_bullets();
        player->draw();
        _draw_score();
    }

    void destroy()
    {
        background->destroy();
        player->destroy();
        enemy_list->destroy();
        bullet_list->destroy();
    }

private:
    Text *score_message;
    TTF_Font *font;
    SDL_Renderer *renderer;
    Screen *screen;

    void collisions()
    {
        Enemy *enemy;
        Bullet *bullet;

        bullet = bullet_list->head;
        while (bullet != NULL)
        {
            process_collision(player, bullet);
            enemy = enemy_list->head;
            while (enemy != NULL)
            {
                process_collision(enemy, bullet);
                enemy = enemy->next;
            }
            bullet = bullet->next;
        }
    }

    void process_collision(Character *character, Bullet *bullet)
    {
        bool collided = character->is_colllided(bullet);
        if (collided)
        {
            character->on_collide(bullet);
            bullet->on_collide();
            bool is_player_shoot = strcmp(bullet->owner_type, "player") == 0;
            if (character->is_damage_was_lethal(bullet) && is_player_shoot)
            {
                score++;
            }
        }
    }

    void _init_score()
    {
        score_message = new Text("", renderer, font);
        score_message->color = {70, 255, 70, 0};
    }

    void _refresh_score_message()
    {
        const char *pattern = "score: %d";
        int length = snprintf(NULL, 0, pattern, score);
        char *str = (char *)malloc(length + 1);
        snprintf(str, length + 1, pattern, score);

        score_message->set_message(str);
        free(str);
    }

    void _draw_score()
    {
        int message_x = (1 - MESSAGES_OFFSET_RELATIVE) * screen->w - score_message->dest.w;
        int message_y = 0;
        score_message->draw(message_x, message_y);
    }
};
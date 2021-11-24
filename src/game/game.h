#include "../media_types/image.h"
#include "background.h"
#include "bullet_list.h"
#include "enemy_list.h"
#include "player.h"
#include "result_screen.h"

#define MESSAGES_OFFSET_RELATIVE 0.01
#define VICTORY_MESSAGE "Victory"
#define VICTORY_TIP "Press Enter to start next level."
#define DEFEAT_MESSAGE "Defeat"
#define DEFEAT_TIP "Press Enter to restart level."

class Game
{
public:
    int score = 0;
    int score_to_win = 1;
    int level = 1;
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
        result_screen = new Result_Screen(window_state, engine_font);
    }

    void handle_events(long dt, int *keyboard)
    {
        if (is_win() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            level++;
            reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        if (is_defeat() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        player->handle_keypress(keyboard, dt);
    }

    void refresh(long dt)
    {
        if (is_win())
        {
            result_screen->refresh(VICTORY_MESSAGE, score, VICTORY_TIP);
            return;
        }

        if (is_defeat())
        {
            result_screen->refresh(DEFEAT_MESSAGE, score, DEFEAT_TIP);
            return;
        }

        refresh_game_scene(dt);
    }

    void draw()
    {
        if (is_win() || is_defeat())
        {
            result_screen->draw();
            return;
        }

        draw_game_scene();
    }

    void refresh_game_scene(long dt)
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

    void draw_game_scene()
    {

        background->draw();
        enemy_list->draw_enemys();
        bullet_list->draw_bullets();
        player->draw();
        _draw_score();
    }

    bool is_win()
    {
        return score >= score_to_win;
    }

    bool is_defeat()
    {
        return player->hp <= 0;
    }

    bool is_play()
    {
        return !is_win() && !is_defeat();
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
    Result_Screen *result_screen;

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
        score_message = new Text("score: ", renderer, font);
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

    void reset_level()
    {
        player->init();
        score = 0;
        enemy_list->destroy();
        bullet_list->destroy();
    }
};
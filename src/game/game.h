#include "../media_types/image.h"
#include "background.h"
#include "bullet_list.h"
#include "enemy_list.h"
#include "effect_list.h"
#include "player.h"
#include "result_screen.h"

#define MESSAGES_OFFSET_RELATIVE 0.01
#define VICTORY_MESSAGE "Victory"
#define VICTORY_TIP "Press Enter to start next level."
#define DEFEAT_MESSAGE "Defeat"
#define DEFEAT_TIP "Press Enter to restart level."
#define HINTS_MESSAGE "move(arrows) fire(space) "

class Game
{
public:
    Game(Window_State window_state, TTF_Font *engine_font)
    {
        renderer = window_state.renderer;
        screen = window_state.screen;
        background = new Background(window_state);
        bullet_list = new Bullet_list();
        enemy_list = new Enemy_list(window_state, bullet_list);
        effect_list = new Effect_list(window_state);
        player = new Player(window_state, bullet_list);
        font = engine_font;

        _init_score();
        _init_level();
        _init_hints();
        result_screen = new Result_Screen(window_state, engine_font);
    }

    void handle_events(long dt, int *keyboard)
    {
        if (_is_win() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            _next_level();
            _reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        if (_is_defeat() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            _reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        player->handle_keypress(keyboard, dt);
    }

    void refresh(long dt)
    {
        if (_is_win())
        {
            result_screen->refresh(VICTORY_MESSAGE, score, VICTORY_TIP);
            return;
        }

        if (_is_defeat())
        {
            result_screen->refresh(DEFEAT_MESSAGE, score, DEFEAT_TIP);
            return;
        }

        _refresh_game_scene(dt);
    }

    void draw()
    {
        if (_is_win() || _is_defeat())
        {
            result_screen->draw();
            return;
        }

        _draw_game_scene();
    }

    bool is_play()
    {
        return !_is_win() && !_is_defeat();
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
    Text *level_message;
    Text *hints;
    TTF_Font *font;
    SDL_Renderer *renderer;
    Screen *screen;
    Result_Screen *result_screen;
    Background *background;
    Bullet_list *bullet_list;
    Enemy_list *enemy_list;
    Effect_list *effect_list;
    Player *player;
    int score = 0;
    int score_to_win = 4;
    int level = 1;

    void _refresh_game_scene(long dt)
    {
        background->refresh(dt);
        player->refresh(engine.dt);
        _collisions();

        bullet_list->refresh_bullets_positions(dt);
        bullet_list->destroy_remote_bullets();

        enemy_list->refresh_enemys_positions(dt);
        enemy_list->delete_dead_enemys();
        enemy_list->spawn_enemys();

        effect_list->refresh(dt);
        effect_list->destroy_done();

        _create_text_from_pattern(score_message, "score: %d", score);
        _create_text_from_pattern(level_message, "level: %d", level);
        _refresh_hints_position();
    }

    void _draw_game_scene()
    {
        background->draw();
        hints->draw();
        enemy_list->draw_enemys();
        bullet_list->draw_bullets();
        player->draw();
        effect_list->draw();
        _draw_line(level_message, 0);
        _draw_line(score_message, 1);
    }

    bool _is_win()
    {
        return score >= score_to_win;
    }

    bool _is_defeat()
    {
        return player->hp <= 0;
    }

    void _collisions()
    {
        Enemy *enemy;
        Bullet *bullet;

        bullet = bullet_list->head;
        while (bullet != NULL)
        {
            _process_collision(player, bullet);
            enemy = enemy_list->head;
            while (enemy != NULL)
            {
                _process_collision(enemy, bullet);
                enemy = enemy->next;
            }
            bullet = bullet->next;
        }
    }

    void _process_collision(Character *character, Bullet *bullet)
    {
        bool collided = character->is_colllided(bullet);
        if (collided)
        {
            character->on_collide(bullet);
            bullet->on_collide();
            bool is_player_shoot = strcmp(bullet->owner_type, "player") == 0;
            if (character->is_damage_was_lethal(bullet))
            {
                effect_list->add(character->x, character->y, character->dy);
                if (is_player_shoot)
                {
                    score++;
                }
            }
        }
    }

    void _init_score()
    {
        score_message = new Text("score: ", renderer, font);
        score_message->color = {70, 255, 70, 0};
    }

    void _init_level()
    {
        level_message = new Text("level: ", renderer, font);
        level_message->color = {70, 255, 70, 0};
    }

    void _init_hints()
    {
        hints = new Text(HINTS_MESSAGE, renderer, font);
        hints->set_color(100, 200, 100, 0);
        _refresh_hints_position();
    }

    void _refresh_hints_position()
    {
        hints->dest.y = screen->h - hints->dest.h * 1.2;
        hints->dest.x = screen->w - hints->dest.w;
    }

    void _create_text_from_pattern(Text *text, const char *pattern, int number)
    {
        int length = snprintf(NULL, 0, pattern, number);
        char *str = (char *)malloc(length + 1);
        snprintf(str, length + 1, pattern, number);

        text->set_message(str);
        free(str);
    }

    void _draw_line(Text *text, int line)
    {
        int message_x = (1 - MESSAGES_OFFSET_RELATIVE) * screen->w - text->dest.w;
        int message_y = text->dest.h * line;
        text->draw(message_x, message_y);
    }

    void _next_level()
    {
        level++;
        if (level % 2 == 0)
        {
            score_to_win++;
        }
        if (level % 3 == 0)
        {
            enemy_list->max_length++;
        }
    }

    void _reset_level()
    {
        player->init();
        score = 0;
        enemy_list->destroy();
        bullet_list->destroy();
        effect_list->destroy();
    }
};
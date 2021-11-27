#include "../media_types/image.h"
#include "background.h"
#include "bullet_list.h"
#include "enemy_list.h"
#include "effect_list.h"
#include "player.h"
#include "result_screen.h"
#include "start_screen.h"

#define GAME_BACKGROUND_FILE "assets/images/backgrounds/bg_0.jpg"
#define MESSAGES_LEFT_OFFSET_RELATIVE 0.01
#define VICTORY_MESSAGE "Victory"
#define VICTORY_TIP "Press Enter to start next level."
#define DEFEAT_MESSAGE "Defeat"
#define DEFEAT_TIP "Press Enter to restart level."
#define HINTS_MESSAGE "move(arrows) fire(space) "

class Game
{
public:
    Game(Window_State win_state, TTF_Font *engine_font)
    {
        window_state = win_state;
        renderer = win_state.renderer;
        screen = win_state.screen;
        background = new Background(win_state, GAME_BACKGROUND_FILE);
        bullet_list = new Bullet_list();
        enemy_list = new Enemy_list();
        effect_list = new Effect_list();
        player = new Player(win_state, bullet_list);
        font = engine_font;

        explode_image = new Image(explode_file_name, renderer);

        _init_text(&score_message, "_", text_color);
        _init_text(&total_score_message, "_", text_color);
        _init_text(&level_message, "_", text_color);
        _init_text(&hints, HINTS_MESSAGE, hints_color);
        _refresh_hints_position();
        result_screen = new Result_Screen(win_state, engine_font);
        start_screen = new Start_Screen(win_state, engine_font);
    }

    void handle_events(long dt, int *keyboard, Mouse *mouse)
    {
        if (start_screen_on)
        {
            start_screen->handle_events(keyboard, mouse, &start_screen_on);
            return;
        }

        if (_is_win() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            _next_level();
            _reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        if (_is_defeat() && keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            _reset_game();
            _reset_level();
            keyboard[SDL_SCANCODE_RETURN] = 0;
        }

        if (is_play())
        {
            player->handle_keypress(keyboard, dt);
        }
    }

    void refresh(long dt)
    {
        if (start_screen_on)
        {
            return;
        }

        if (_is_win())
        {
            result_screen->refresh(VICTORY_MESSAGE, score, total_score, VICTORY_TIP);
            return;
        }

        if (_is_defeat())
        {
            result_screen->refresh(DEFEAT_MESSAGE, score, total_score, DEFEAT_TIP);
            return;
        }

        _refresh_game_scene(dt);
    }

    void draw()
    {
        if (start_screen_on)
        {
            start_screen->draw();
            return;
        }

        if (_is_win() || _is_defeat())
        {
            result_screen->draw();
            return;
        }

        _draw_game_scene();
    }

    bool is_play()
    {
        return !_is_win() && !_is_defeat() && !start_screen_on;
    }

    void destroy()
    {
        background->destroy();
        player->destroy();
        enemy_list->destroy();
        bullet_list->destroy();
        explode_image->destroy();
    }

private:
    Text *score_message;
    Text *total_score_message;
    Text *level_message;
    Text *hints;
    TTF_Font *font;
    SDL_Renderer *renderer;
    Screen *screen;
    Result_Screen *result_screen;
    Start_Screen *start_screen;
    Background *background;
    Bullet_list *bullet_list;
    Enemy_list *enemy_list;
    Effect_list *effect_list;
    Player *player;
    Window_State window_state;
    Image *explode_image;
    SDL_Color text_color = {70, 255, 70, 0};
    SDL_Color hints_color = {100, 200, 100, 0};
    const char *explode_file_name = "assets/images/effects/effect.png";
    bool start_screen_on = true;
    int score = 0;
    int score_to_win = 4;
    int total_score = 0;
    int level = 1;
    int max_enemys = 4;

    void _refresh_game_scene(long dt)
    {
        background->refresh(dt);
        player->refresh(engine.dt);
        _collisions();

        bullet_list->refresh_bullets_positions(dt);
        bullet_list->delete_remote_bullets();

        enemy_list->refresh_enemys(dt);
        enemy_list->delete_dead_enemys();

        _spawn_enemys();

        effect_list->refresh(dt);
        effect_list->delete_done();

        _create_text_from_pattern(total_score_message, "total score: %d", total_score);
        _create_text_from_pattern(level_message, "level: %d", level);
        _create_text_from_pattern(score_message, "level score: %d", score);
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
        _draw_line(total_score_message, 0);
        _draw_line(level_message, 1);
        _draw_line(score_message, 2);
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

                Effect *explode = new Effect(window_state, explode_image, character->x, character->y, character->dy);
                effect_list->add(explode);
                if (is_player_shoot)
                {
                    _increase_score();
                }
            }
        }
    }

    void _init_text(Text **text, const char *msg, SDL_Color color)
    {
        *text = new Text(msg, renderer, font);
        Text *tmp = *text;
        tmp->set_color(color.r, color.g, color.b, color.a);
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
        int message_x = (1 - MESSAGES_LEFT_OFFSET_RELATIVE) * screen->w - text->dest.w;
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
            max_enemys++;
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

    void _increase_score()
    {
        score++;
        total_score++;
    }

    void _reset_game()
    {
        level = 0;
        total_score = 0;
    }

    void _spawn_enemys()
    {
        int need_add_enemys = max_enemys - enemy_list->length;
        while (need_add_enemys > 0)
        {
            Enemy *enemy = new Enemy(window_state, bullet_list);
            enemy_list->add(enemy);
            need_add_enemys--;
        }
    }
};
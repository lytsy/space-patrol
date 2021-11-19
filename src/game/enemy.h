#include "character.h"

// Base class config
#define ENEMY_SPRITE_FILE "assets/images/enemys/enemy_0.png"
#define ENEMY_RELATIVE_WIDTH 0.07
#define ENEMY_RELOAD_TIME 500
#define ENEMY_BULLET_DY 1

Character_config ENEMY_BASE_CONFIG = {
    ENEMY_SPRITE_FILE,
    ENEMY_RELATIVE_WIDTH,
    ENEMY_RELOAD_TIME,
    ENEMY_BULLET_DY};

//  Enemy config
#define ENEMY_X_SPEED 0.02
#define ENEMY_Y_SPEED 0.15
#define ENEMY_HP 2

class Enemy : public Character
{
public:
    Enemy *next;
    int hp = ENEMY_HP;

    Enemy(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Screen *engine_screen, Bullet_list *list) : Character(sdl_renderer, sdl_window, engine_screen, list, ENEMY_BASE_CONFIG)
    {
        init_position();
        dx = rand() % 6 - 3;
        dy = rand() % 2 + 1;
    }

    void init_position()
    {
        x = rand() % (screen->w - w) + w * 0.5;
        y = rand() % screen->h * 0.3 * -1;
    }

    void refresh(long dt)
    {
        on_resize();
        y += dy * dt * y_speed;
        x += dx * dt * x_speed;
        fire(dt);
        init_size();
    }

    void check_collision(Bullet_list *bullet_list)
    {
        Bullet *bullet = bullet_list->head;
        while (bullet != NULL)
        {
            bool is_left_top_collision = is_point_in_box(bullet->x, bullet->y, x, y, w, h);
            bool is_right_top_collision = is_point_in_box(bullet->x + bullet->w, bullet->y, x, y, w, h);

            if (is_left_top_collision || is_right_top_collision)
            {
                take_damage(bullet->damage);
                bullet->take_damage(bullet->damage);
            }

            bullet = bullet->next;
        }
    }

    bool is_point_in_box(int x, int y, int bx, int by, int bw, int bh)
    {
        return x > bx && (x < (bx + bw)) && y > by && (y < (by + bh));
    }

    void take_damage(int damage)
    {
        hp -= damage;
    }

private:
    float x_speed = ENEMY_X_SPEED;
    float y_speed = ENEMY_Y_SPEED;
};
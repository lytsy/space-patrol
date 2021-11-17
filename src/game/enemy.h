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

    Enemy(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Bullet_list *list) : Character(sdl_renderer, sdl_window, list, ENEMY_BASE_CONFIG)
    {
        init_position();
        dx = rand() % 6 - 3;
        dy = rand() % 2 + 1;
    }

    void init_position()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        SDL_Rect dest;
        image->get_dest(&dest);
        x = rand() % (window_width - dest.w) + dest.w * 0.5;
        y = rand() % window_height * 0.3 * -1;
        image->set_dest_position(x, y);
    }

    void refresh(long dt)
    {
        y += dy * dt * y_speed;
        x += dx * dt * x_speed;
        image->set_dest_position(x, y);
        fire(dt);
    }

    void check_collision(Bullet_list *bullet_list)
    {
        Bullet *current = bullet_list->head;
        while (current != NULL)
        {
            SDL_Rect bullet, enemy;
            current->image->get_dest(&bullet);
            image->get_dest(&enemy);
            bool is_left_top_collision = is_point_in_box(bullet.x, bullet.y,
                                                         enemy.x, enemy.y, enemy.w, enemy.h);
            bool is_right_top_collision = is_point_in_box(bullet.x + bullet.w, bullet.y,
                                                          enemy.x, enemy.y, enemy.w, enemy.h);

            if (is_left_top_collision || is_right_top_collision)
            {
                take_damage(current->damage);
                current->take_damage(current->damage);
            }

            current = current->next;
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
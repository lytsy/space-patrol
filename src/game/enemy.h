#include "character.h"

#define ENEMY_TYPES 3

Character_config enemy_configs[ENEMY_TYPES] = {
    {
        .file = "assets/images/enemys/enemy_0.png",
        .type = "npc",
        .relative_width = 0.07,
        .reload = 700,
        .bullet_dy = 1,
        .hp = 2,
        .x_speed = 0.00004,
        .y_speed = 0.00030,
    },
    {
        .file = "assets/images/enemys/enemy_1.png",
        .type = "npc",
        .relative_width = 0.035,
        .reload = 600,
        .bullet_dy = 1,
        .hp = 1,
        .x_speed = 0.00004,
        .y_speed = 0.00030,
    },
    {
        .file = "assets/images/enemys/enemy_2.png",
        .type = "npc",
        .relative_width = 0.08,
        .reload = 20000,
        .bullet_dy = 1,
        .hp = 3,
        .x_speed = 0.00002,
        .y_speed = 0.00025,
    },
};

class Enemy : public Character
{
public:
    Enemy *next;

    Enemy(Window_State window_state, Bullet_list *list, Character_config cfg) : Character(window_state, list, cfg)
    {
        _init_position();
        dx = rand() % 7 - 3;
        dy = rand() % 2 + 1;
    }

    void refresh(long dt)
    {
        on_resize();
        y += dy * dt * y_speed * screen->h;
        x += dx * dt * x_speed * screen->w;
        refresh_reload(dt);
        fire();
    }

private:
    void _init_position()
    {
        x = rand() % (screen->w - w) + w * 0.5;
        y = rand() % screen->h * 0.3 * -1;
    }
};
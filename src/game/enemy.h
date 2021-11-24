#include "character.h"

// Base class config
#define ENEMY_SPRITE_FILE "assets/images/enemys/enemy_0.png"
#define ENEMY_RELATIVE_WIDTH 0.07
#define ENEMY_RELOAD_TIME 500
#define ENEMY_BULLET_DY 1
#define ENEMY_PLAYER_TYPE "npc"

Character_config ENEMY_BASE_CONFIG = {
    ENEMY_SPRITE_FILE,
    ENEMY_PLAYER_TYPE,
    ENEMY_RELATIVE_WIDTH,
    ENEMY_RELOAD_TIME,
    ENEMY_BULLET_DY};

//  Enemy config
#define ENEMY_X_SPEED 0.00004
#define ENEMY_Y_SPEED 0.00030
#define ENEMY_HP 2

class Enemy : public Character
{
public:
    Enemy *next;

    Enemy(Window_State window_state, Bullet_list *list) : Character(window_state, list, ENEMY_BASE_CONFIG)
    {
        init_position();
        dx = rand() % 6 - 3;
        dy = rand() % 2 + 1;
        hp = ENEMY_HP;
    }

    void init_position()
    {
        x = rand() % (screen->w - w) + w * 0.5;
        y = rand() % screen->h * 0.3 * -1;
    }

    void refresh(long dt)
    {
        on_resize();
        y += dy * dt * y_speed * screen->h;
        x += dx * dt * x_speed * screen->w;
        fire(dt);
    }

private:
    float x_speed = ENEMY_X_SPEED;
    float y_speed = ENEMY_Y_SPEED;
};
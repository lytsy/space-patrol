#pragma once
#include "../engine/engine.h"
#include "../media_types/image.h"
#include "bullet_list.h"
#include "../engine/collider.h"

typedef struct
{
    const char *file;
    const char *type;
    float relative_width;
    int reload;
    int bullet_dy;
    int hp;
    float x_speed;
    float y_speed;
} Character_config;

class Character
{
public:
    int x, y, w, h;
    int dx, dy;
    int hp, initial_hp, damage;
    float x_speed;
    float y_speed;
    Image *image;
    Screen *screen;
    SDL_Renderer *renderer;
    const char *type;

    Character(Window_State win_state, Bullet_list *list, Character_config config)
    {
        window_state = win_state;
        window = win_state.window;
        renderer = win_state.renderer;
        screen = win_state.screen;
        bullet_list = list;
        image = new Image(config.file, win_state.renderer);
        type = config.type;
        relative_width = config.relative_width;
        reload_time = config.reload;
        current_reload_time = reload_time;
        bullet_dy = config.bullet_dy;
        hp = config.hp;
        initial_hp = config.hp;
        x_speed = config.x_speed;
        y_speed = config.y_speed;
        _init_size();
    }

    void refresh_reload(long dt)
    {
        current_reload_time += dt;
    }

    bool can_strike()
    {
        return current_reload_time >= reload_time;
    }

    void fire()
    {
        if (can_strike())
        {
            current_reload_time = 0;
            _create_bullet();
        }
    }

    void on_resize()
    {
        screen->on_resize_scale(&x, &y, &w, &h);
    }

    void draw()
    {
        image->draw(x, y, w, h);
    }

    bool is_colllided(Bullet *bullet)
    {
        if (strcmp(type, bullet->owner_type) == 0)
        {
            return false;
        }
        return Collider::is_collision(bullet->x, bullet->y, bullet->w, bullet->h, x, y, w, h);
    }

    void on_collide(Bullet *bullet)
    {
        hp -= bullet->damage;
    }

    bool is_damage_was_lethal(Bullet *bullet)
    {
        return hp <= 0 && hp + bullet->damage > 0;
    }

    bool is_need_destroy()
    {
        return y > screen->h || hp <= 0;
    }

    void destroy()
    {
        image->destroy();
    }

private:
    Window_State window_state;
    SDL_Window *window;
    Bullet_list *bullet_list;
    long current_reload_time;
    int reload_time;
    int speed;
    int bullet_dy;
    float relative_width;

    void _init_size()
    {
        image->scale_to_relative_size(&w, &h, window_state.window, relative_width);
    }

    void _create_bullet()
    {
        int bullet_y;
        int bullet_x = x + w * 0.5;

        if (bullet_dy < 0)
        {
            bullet_y = y - h * 0.55;
        }

        if (bullet_dy > 0)
        {
            bullet_y = y + h * 1.1;
        }

        Bullet *bullet = new Bullet(window_state, bullet_x, bullet_y, bullet_dy, type);

        bullet_list->add(bullet);
    }
};
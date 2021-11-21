#pragma once
#include "../engine/engine.h"
#include "../media_types/image.h"
#include "bullet_list.h"
#include "../engine/collider.h"

class Character_config
{
public:
    const char *file;
    const char *type;
    float relative_width;
    int reload;
    int bullet_dy;
};

class Character
{
public:
    int x, y, w, h;
    int dx, dy;
    int hp, damage;
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
        init_size();
    }

    void init_size()
    {
        image->scale_to_relative_size(&w, &h, window_state.window, relative_width);
    }

    void draw()
    {
        image->draw(x, y, w, h);
    }

    void fire(long dt)
    {
        current_reload_time += dt;
        if (current_reload_time >= reload_time)
        {
            current_reload_time -= reload_time;
            create_bullet();
        }
    }

    void create_bullet()
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

        bullet_list->add_bullet(window_state, bullet_x, bullet_y, bullet_dy, type);
    }

    void on_resize()
    {
        if (screen->w_scale != 1.0 || screen->h_scale != 1.0)
        {
            x *= screen->w_scale;
            w *= screen->w_scale;
            y *= screen->h_scale;
            h *= screen->h_scale;
            speed *= screen->w_scale * screen->h_scale;
        }
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
    int bullet_dy;
    float relative_width;
    int reload_time;
    int speed;
    long current_reload_time;
};
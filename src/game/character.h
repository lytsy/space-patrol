#pragma once
#include "../engine/engine.h"
#include "../media_types/image.h"
#include "bullet_list.h"

class Character_config
{
public:
    const char *file;
    float relative_width;
    int reload;
    int bullet_dy;
};

class Character
{
public:
    int x, y, w, h;
    int dx, dy;
    Image *image;
    Screen *screen;

    Character(Window_State win_state, Bullet_list *list, Character_config config)
    {
        window_state = win_state;
        window = win_state.window;
        screen = win_state.screen;
        bullet_list = list;
        image = new Image(config.file, win_state.renderer);
        relative_width = config.relative_width;
        reload_time = config.reload;
        current_reload_time = reload_time;
        bullet_dy = config.bullet_dy;
        init_size();
    }

    void draw()
    {
        image->draw(x, y, w, h);
    }

    void init_size()
    {
        image->scale_to_relative_size(&w, &h, window_state.window, relative_width);
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
        int bullet_offset_y = 5;
        int bullet_x = x + w * 0.5;

        if (bullet_dy < 0)
        {
            bullet_y = y - bullet_offset_y;
        }

        if (bullet_dy > 0)
        {
            bullet_y = y + h + bullet_offset_y;
        }

        bullet_list->add_bullet(window_state, bullet_x, bullet_y, bullet_dy);
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
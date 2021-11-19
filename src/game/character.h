#pragma once
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
    SDL_Window *window;
    Image *image;

    Character(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Bullet_list *list, Character_config config)
    {
        window = sdl_window;
        renderer = sdl_renderer;
        bullet_list = list;
        image = new Image(config.file, sdl_renderer);
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
        image->scale_to_width(&w, &h, window, relative_width);
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

        bullet_list->add_bullet(bullet_x, bullet_y, bullet_dy, renderer, window);
    }

    void destroy()
    {
        image->destroy();
    }

private:
    SDL_Renderer *renderer;
    Bullet_list *bullet_list;
    int bullet_dy;
    float relative_width;
    int reload_time;
    long current_reload_time;
};
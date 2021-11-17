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
    int x;
    int y;
    int dx;
    int dy;
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
        image->draw();
    }

    void init_size()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        int width = window_width * relative_width;
        image->scale_dest_to_width(width);
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
        int bullet_x, bullet_y;
        int bullet_offset_y = 5;
        SDL_Rect player_texture;
        image->get_dest(&player_texture);

        bullet_x = player_texture.x + player_texture.w * 0.5;

        if (bullet_dy < 0)
        {
            bullet_y = player_texture.y - bullet_offset_y;
        }

        if (bullet_dy > 0)
        {
            bullet_y = player_texture.y + player_texture.h + bullet_offset_y;
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
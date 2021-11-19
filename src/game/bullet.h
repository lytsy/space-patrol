#pragma once
#include "../media_types/image.h"

class Bullet
{
public:
    Bullet *next;
    int x, y, w, h;
    int dy;
    float speed = 0.4;
    Image *image;
    int hp = 1;
    int damage = 1;

    Bullet(int nx, int ny, int ndy, SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file_name, sdl_renderer);

        init_src_size();
        init_dest_size();
        x = nx - w * 0.5;
        y = ny;

        dy = ndy;
    }

    void init_src_size()
    {
        image->src.w = frame_size;
        image->src.h = frame_size;
    }

    void init_dest_size()
    {
        image->scale_to_width(&w, &h, window, relative_width);
    }

    void refresh(long dt)
    {
        y += dy * dt * speed;
        init_dest_size();
    }

    void draw()
    {
        image->draw(x, y, w, h);
    }

    void take_damage(int damage)
    {
        hp -= damage;
    }

private:
    SDL_Window *window;
    const char *file_name = "assets/images/bullets/player_bullet.png";
    float relative_width = 0.03;
    int frame_size = 64;
};
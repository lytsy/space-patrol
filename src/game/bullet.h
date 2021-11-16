#pragma once
#include "../media_types/image.h"

class Bullet
{
public:
    Bullet *next;
    int x, y;
    int dy;
    float speed = 0.4;
    Image *image;
    int hp = 1;
    int damage = 1;

    Bullet(int nx, int ny, int ndy, SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        dy = ndy;
        image = new Image(file_name, sdl_renderer);

        set_src_frame();
        init_size();
        SDL_Rect bullet_texture;
        image->get_dest(&bullet_texture);
        set_position(nx - bullet_texture.w * 0.5, ny);
    }

    void set_position(int nx, int ny)
    {
        x = nx;
        y = ny;
        image->set_dest_position(x, y);
    }

    void set_src_frame()
    {
        image->set_src(0, 0, frame_size, frame_size);
    }

    void refresh(long dt)
    {
        y += dy * dt * speed;
        image->set_dest_position(x, y);
    }

    void init_size()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        int width = window_width * width_koef_to_screen;
        image->scale_dest_to_width(width);
    }

    void draw()
    {
        image->draw();
    }

    void take_damage(int damage)
    {
        hp -= damage;
    }

private:
    SDL_Window *window;
    const char *file_name = "assets/images/bullets/player_bullet.png";
    float width_koef_to_screen = 0.03;
    int frame_size = 64;
};
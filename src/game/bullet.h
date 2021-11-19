#pragma once
#include "../media_types/image.h"

class Bullet
{
public:
    Bullet *next;
    Image *image;
    Screen *screen;
    int x, y, w, h;
    int dy;
    int damage = 1;
    int hp = 1;

    Bullet(Window_State window_state, int nx, int ny, int ndy)
    {
        window = window_state.window;
        screen = window_state.screen;
        image = new Image(file_name, window_state.renderer);

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
        image->scale_to_relative_size(&w, &h, window, relative_width);
    }

    void refresh(long dt)
    {
        on_resize();
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
    SDL_Window *window;
    float speed = 0.4;
    const char *file_name = "assets/images/bullets/player_bullet.png";
    float relative_width = 0.03;
    int frame_size = 64;
};
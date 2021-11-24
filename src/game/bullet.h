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
    const char *owner_type;
    double rotation = 180.0;

    Bullet(Window_State window_state, int nx, int ny, int ndy, const char *owner)
    {
        window = window_state.window;
        screen = window_state.screen;
        image = new Image(file_name, window_state.renderer);

        init_src_size();
        init_dest_size();
        x = nx - w * 0.5;
        y = ny;
        dy = ndy;
        owner_type = owner;
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
        y += dy * dt * speed * screen->h;
        screen->on_resize_scale(&x, &y, &w, &h);
        init_dest_size();
    }

    void draw()
    {
        if (strcmp(owner_type, "npc") == 0)
        {
            image->draw(x, y, w, h, rotation);
            return;
        }
        image->draw(x, y, w, h);
    }

    void on_collide()
    {
        hp -= damage;
    }

    bool is_need_destroy()
    {
        return y < 0 || y > screen->h || x < 0 || x > screen->w || hp <= 0;
    }

    void destroy()
    {
        image->destroy();
    }

private:
    SDL_Window *window;
    float speed = 0.0008;
    const char *file_name = "assets/images/bullets/player_bullet.png";
    float relative_width = 0.03;
    int frame_size = 64;
};
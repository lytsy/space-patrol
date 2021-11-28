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

        if (strcmp(owner, "player") == 0)
        {
            image = new Image(player_bullet_sprite, window_state.renderer);
        }
        else
        {
            image = new Image(enemy_bullet_sprite, window_state.renderer);
        }

        _init_src_size();
        _init_dest_size();
        x = nx - w * 0.5;
        y = ny;
        dy = ndy;
        owner_type = owner;
    }

    void refresh(long dt)
    {
        y += dy * dt * speed * screen->h;
        screen->on_resize_scale(&x, &y, &w, &h);
        _init_dest_size();
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
    const char *player_bullet_sprite = "assets/images/bullets/player_bullet.png";
    const char *enemy_bullet_sprite = "assets/images/bullets/enemy_bullet.png";
    float relative_width = 0.03;
    int frame_size = 64;

    void _init_src_size()
    {
        image->src.w = frame_size;
        image->src.h = frame_size;
    }

    void _init_dest_size()
    {
        image->scale_to_relative_size(&w, &h, window, relative_width);
    }
};
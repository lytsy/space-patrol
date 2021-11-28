#pragma once
#include "../media_types/image.h"
#include "../engine/engine.h"

class Effect
{
public:
    Effect *next;
    bool done = false;

    Effect(Window_State window_state, Image *explode_image, int nx, int ny, int ndy)
    {
        window = window_state.window;
        screen = window_state.screen;
        image = explode_image;

        relative_width = (rand() % 3 + 8) * 0.01;
        _init_src_size();
        _init_dest_size();
        x = nx;
        y = ny - h * 0.5;
        dy = ndy;
    }

    void refresh(long dt)
    {
        screen->on_resize_scale(&x, &y, &w, &h);
        y += dy * dt * speed * screen->h;
        _refresh_animation_state(dt);
        _init_dest_size();
    }

    bool is_need_destroy()
    {
        return done;
    }

    void draw()
    {
        _select_animation_frame();
        image->draw(x, y, w, h);
    }

    void destroy() {}

private:
    SDL_Window *window;
    Image *image;
    Screen *screen;
    const char *file_name = "assets/images/effects/effect.png";
    const int sprites_in_line = 3;
    int x, y, w, h;
    int dy;
    float speed = 0.0002;
    float relative_width;
    int frame_size = 341;
    long time = 0;
    int animation_step_time = 50;
    int animation_step = 0;
    int max_animation_step = 8;

    void _init_src_size()
    {
        image->src.w = frame_size;
        image->src.h = frame_size;
    }

    void _init_dest_size()
    {
        image->scale_to_relative_size(&w, &h, window, relative_width);
    }

    void _select_animation_frame()
    {
        image->src.x = (animation_step % sprites_in_line) * frame_size;
        image->src.y = ceil((float)animation_step / sprites_in_line) * frame_size;
    }

    void _refresh_animation_state(long dt)
    {
        time += dt;
        if (time > animation_step_time)
        {
            animation_step++;
            time -= animation_step_time;
            if (animation_step > max_animation_step)
            {
                animation_step = 0;
                done = true;
            }
        }
    }
};
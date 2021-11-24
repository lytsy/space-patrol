#pragma once
#include "../media_types/image.h"
#include "../engine/engine.h"

class Effect
{
public:
    Effect *next;
    bool done = false;

    Effect(Window_State window_state, int nx, int ny, int ndy)
    {
        window = window_state.window;
        screen = window_state.screen;
        image = new Image(file_name, window_state.renderer);

        init_src_size();
        init_dest_size();
        x = nx;
        y = ny - h * 0.5;
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
        screen->on_resize_scale(&x, &y, &w, &h);
        y += dy * dt * speed * screen->h;
        refresh_animation_state(dt);
        init_dest_size();
    }

    void refresh_animation_state(long dt)
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

    void draw()
    {
        select_animation_frame();
        image->draw(x, y, w, h);
    }

    void select_animation_frame()
    {
        image->src.x = (animation_step % 3) * frame_size;
        image->src.y = ceil((float)animation_step / 3) * frame_size;
    }

    void destroy()
    {
        image->destroy();
    }

private:
    SDL_Window *window;
    float speed = 0.0002;
    const char *file_name = "assets/images/effects/effect.png";
    float relative_width = 0.1;
    int frame_size = 341;
    int animation_step_time = 50;
    int animation_step = 0;
    int max_animation_step = 8;
    long time = 0;
    Image *image;
    Screen *screen;
    int x, y, w, h;
    int dy;
};
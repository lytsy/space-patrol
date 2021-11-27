
/* Draw infinite background repeated by X and Y. */
#pragma once
#include "../media_types/image.h"
#include <math.h>

class Background
{
public:
    float speed = 0.1;

    Background(Window_State window_state, const char *file)
    {
        window = window_state.window;
        screen = window_state.screen;
        image = new Image(file, window_state.renderer);
        x = 0;
        y = 0;
        w = image->src.w;
        h = image->src.h;
    }

    void draw()
    {
        int draw_area_width = screen->w;
        int repeat_x_steps = ceil((float)draw_area_width / w);

        int draw_area_height = screen->h + h;
        int repeat_y_steps = ceil((float)draw_area_height / h);

        for (int i = 0; i < repeat_x_steps; i++)
        {
            for (int j = 0; j < repeat_y_steps; j++)
            {
                image->draw(x + (i * w), y - (j * h), w, h);
            }
        }
    }

    void refresh(long dt)
    {
        y += dt * speed;
        if (y >= h)
        {
            y -= h;
        }
    }

    void destroy()
    {
        image->destroy();
    }

private:
    Image *image;
    SDL_Window *window;
    Screen *screen;
    int x, y, w, h;
};
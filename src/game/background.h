
/* Draw infinite background repeated by X and Y. */
#include "../media_types/image.h"
#include <math.h>

class Background
{
public:
    Image *image;
    SDL_Window *window;
    float speed = 0.1;
    int x, y, w, h;

    Background(const char *file, SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file, sdl_renderer);
        x = 0;
        y = 0;
        w = image->src.w;
        h = image->src.h;
    }

    void draw()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);

        int draw_area_width = window_width;
        int repeat_x_steps = ceil((float)draw_area_width / w);

        int draw_area_height = window_height + h;
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
};
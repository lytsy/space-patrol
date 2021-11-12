
/* Draw infinite background repeated by X and Y. */
#include "../media_types/image.h"
#include <math.h>

class Background
{
public:
    Image *image;
    SDL_Window *window;

    Background(const char *file, SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file, sdl_renderer);
    }

    void draw()
    {
        SDL_Rect dest;
        image->get_dest(&dest);

        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);

        int draw_area_width = window_width;
        int repeat_x_steps = ceil((float)draw_area_width / dest.w);

        int draw_area_height = window_height + dest.h;
        int repeat_y_steps = ceil((float)draw_area_height / dest.h);

        for (int x = 0; x < repeat_x_steps; x++)
        {
            for (int y = 0; y < repeat_y_steps; y++)
            {
                image->set_dest(dest.x + (x * dest.w), dest.y - (y * dest.h), dest.w, dest.h);
                image->draw();
            }
        }

        image->set_dest(dest.x, dest.y, dest.w, dest.h);
    }

    void refresh()
    {
        SDL_Rect dest;
        image->get_dest(&dest);

        dest.y += 1;
        if (dest.y >= dest.h)
        {
            dest.y -= dest.h;
        }

        image->set_dest(dest.x, dest.y, dest.w, dest.h);
    }

    void destroy()
    {
        image->destroy();
    }
};
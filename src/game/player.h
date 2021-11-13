#include "../media_types/image.h"

class Player
{
public:
    int x;
    int y;
    int w;
    int h;

    Image *image;
    Player(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file_name, sdl_renderer);
        init_position();
    }

    void draw()
    {
        image->set_dest_position(x, y);
        image->draw();
    }

    void set_position(int nx, int ny)
    {
        x = nx;
        y = ny;
    }

    void init_position()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);

        SDL_Rect src;
        image->get_src(&src);

        int start_x = (window_width / 2) - src.w / 2;
        int start_y = window_height - src.h;
        set_position(start_x, start_y);
    }

    void destroy()
    {
        image->destroy();
    }

private:
    const char *file_name = "assets/test_img.png";
    SDL_Window *window;
};
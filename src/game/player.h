#include "../media_types/image.h"

class Player
{
public:
    int x;
    int y;
    int dx;
    int dy;
    float speed = 0.2;
    int reload_time = 400;
    long current_reload_time = reload_time;

    Image *image;
    Player(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file_name, sdl_renderer);
        init_size();
        init_position();
    }

    void draw()
    {
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

        SDL_Rect dest;
        image->get_dest(&dest);

        int start_x = (window_width / 2) - dest.w / 2;
        int start_y = (1 - start_y_offset_koef) * window_height - dest.h;
        set_position(start_x, start_y);
    }

    void init_size()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        int width = window_width * width_koef_to_screen;
        image->scale_dest_to_width(width);
    }

    void handle_keypress(int *keyboard, long dt)
    {
        dx = 0;
        dy = 0;

        if (keyboard[SDL_SCANCODE_RIGHT] == 1)
        {
            dx = 1;
        }
        if (keyboard[SDL_SCANCODE_LEFT] == 1)
        {
            dx = -1;
        }
        if (keyboard[SDL_SCANCODE_DOWN] == 1)
        {
            dy = 1;
        }
        if (keyboard[SDL_SCANCODE_UP] == 1)
        {
            dy = -1;
        }
        if (keyboard[SDL_SCANCODE_SPACE] == 1)
        {
            fire(dt);
        }
    }

    void refresh(long dt)
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        SDL_Rect player_texture;
        image->get_dest(&player_texture);

        int new_x = x + dx * dt * speed;
        if (new_x > 0 && new_x < window_width - player_texture.w)
        {
            x = new_x;
        }

        int new_y = y + dy * dt * speed;
        if (new_y > 0 && new_y < window_height - player_texture.h)
        {
            y = new_y;
        }

        image->set_dest_position(x, y);
    }

    void destroy()
    {
        image->destroy();
    }

    void fire(long dt)
    {
        current_reload_time += dt;
        if (current_reload_time >= reload_time)
        {
            current_reload_time -= reload_time;
            printf("fire\n");
        }
    }

private:
    const char *file_name = "assets/images/player/player.png";
    SDL_Window *window;
    float width_koef_to_screen = 0.1;
    float start_y_offset_koef = 0.05;
};
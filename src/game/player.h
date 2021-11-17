
#include "character.h"

// Base class config
#define PLAYER_SPRITE_FILE "assets/images/player/player.png"
#define PLAYER_RELATIVE_WIDTH 0.1
#define PLAYER_RELOAD_TIME 300
#define PLAYER_BULLET_DY -1

Character_config PLAYER_BASE_CONFIG = {
    PLAYER_SPRITE_FILE,
    PLAYER_RELATIVE_WIDTH,
    PLAYER_RELOAD_TIME,
    PLAYER_BULLET_DY};

// Player config
#define PLAYER_X_SPEED 0.2
#define PLAYER_Y_SPEED 0.2
#define PLAYER_Y_OFFSET_RELATIVE 0.05

class Player : public Character
{
public:
    Player(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Bullet_list *list) : Character(sdl_renderer, sdl_window, list, PLAYER_BASE_CONFIG)
    {
        init_position();
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
        int start_y = (1 - y_offset_relative) * window_height - dest.h;
        set_position(start_x, start_y);
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

        int new_x = x + dx * dt * x_speed;
        if (new_x > 0 && new_x < window_width - player_texture.w)
        {
            x = new_x;
        }

        int new_y = y + dy * dt * y_speed;
        if (new_y > 0 && new_y < window_height - player_texture.h)
        {
            y = new_y;
        }

        image->set_dest_position(x, y);
    }

private:
    float y_offset_relative = PLAYER_Y_OFFSET_RELATIVE;
    float x_speed = PLAYER_X_SPEED;
    float y_speed = PLAYER_Y_SPEED;
};
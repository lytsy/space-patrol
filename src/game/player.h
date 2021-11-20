
#pragma once
#include "character.h"

// Base class config
#define PLAYER_SPRITE_FILE "assets/images/player/player.png"
#define PLAYER_RELATIVE_WIDTH 0.1
#define PLAYER_RELOAD_TIME 300
#define PLAYER_BULLET_DY -1
#define PLAYER_TYPE "player"

Character_config PLAYER_BASE_CONFIG = {
    PLAYER_SPRITE_FILE,
    PLAYER_TYPE,
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
    Player(Window_State window_state, Bullet_list *list) : Character(window_state, list, PLAYER_BASE_CONFIG)
    {
        init_position();
    }

    void init_position()
    {
        x = (screen->w / 2) - w / 2;
        y = (1 - y_offset_relative) * screen->h - h;
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
        on_resize();

        int new_x = x + dx * dt * x_speed;
        if (new_x > 0 && new_x < screen->w - w)
        {
            x = new_x;
        }

        int new_y = y + dy * dt * y_speed;
        if (new_y > 0 && new_y < screen->h - h)
        {
            y = new_y;
        }
    }

private:
    float y_offset_relative = PLAYER_Y_OFFSET_RELATIVE;
    float x_speed = PLAYER_X_SPEED;
    float y_speed = PLAYER_Y_SPEED;
};
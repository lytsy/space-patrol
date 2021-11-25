
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
#define PLAYER_X_SPEED 0.0003
#define PLAYER_Y_SPEED 0.0003
#define PLAYER_Y_OFFSET_RELATIVE 0.05
#define PLAYER_START_HP 20
#define HP_BARS_IN_LINE 10

class Player : public Character
{
public:
    Player(Window_State window_state, Bullet_list *list) : Character(window_state, list, PLAYER_BASE_CONFIG)
    {
        init();
    }

    void init()
    {
        _init_position();
        hp = PLAYER_START_HP;
    }

    void handle_keypress(int *keyboard, long dt)
    {
        dx = 0;
        dy = 0;

        if (keyboard[SDL_SCANCODE_RIGHT] == 1 || keyboard[SDL_SCANCODE_D] == 1)
        {
            dx = 1;
        }
        if (keyboard[SDL_SCANCODE_LEFT] == 1 || keyboard[SDL_SCANCODE_A] == 1)
        {
            dx = -1;
        }
        if (keyboard[SDL_SCANCODE_DOWN] == 1 || keyboard[SDL_SCANCODE_S] == 1)
        {
            dy = 1;
        }
        if (keyboard[SDL_SCANCODE_UP] == 1 || keyboard[SDL_SCANCODE_W] == 1)
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

        int new_x = x + dx * dt * x_speed * screen->w;
        if (new_x > 0 && new_x < screen->w - w)
        {
            x = new_x;
        }

        int new_y = y + dy * dt * y_speed * screen->h;
        if (new_y > 0 && new_y < screen->h - h)
        {
            y = new_y;
        }
    }

    void draw()
    {
        Character::draw();
        _draw_hp();
    }

private:
    float y_offset_relative = PLAYER_Y_OFFSET_RELATIVE;
    float x_speed = PLAYER_X_SPEED;
    float y_speed = PLAYER_Y_SPEED;
    int max_hp = 20;
    float hp_bar_size_relative = 0.1;
    SDL_Color hp_full = {0, 255, 200};
    SDL_Color hp_empty = {122, 122, 122};

    void _init_position()
    {
        x = (screen->w - w) / 2;
        y = (1 - y_offset_relative) * screen->h - h;
    }

    void _draw_hp()
    {
        SDL_Rect dest;
        float size = w * hp_bar_size_relative;
        float offset = size * hp_bar_size_relative;
        float offset_from_player = h * hp_bar_size_relative;

        for (int i = 0; i < max_hp; i++)
        {
            dest.x = x + (i % HP_BARS_IN_LINE) * size + offset;
            dest.y = y + h + ceil(i / HP_BARS_IN_LINE) * size + offset + offset_from_player;
            dest.w = size - offset;
            dest.h = size - offset;

            if (hp >= i)
            {
                SDL_SetRenderDrawColor(renderer, hp_full.r, hp_full.g, hp_full.b, hp_full.a);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, hp_empty.r, hp_empty.g, hp_empty.b, hp_empty.a);
            }

            SDL_RenderFillRect(renderer, &dest);
        }
    }
};

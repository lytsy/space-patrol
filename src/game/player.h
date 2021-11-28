
#pragma once
#include "../media_types/sound.h"
#include "character.h"

Character_config player_config =
    {
        .file = "assets/images/player/player.png",
        .type = "player",
        .relative_width = 0.1,
        .reload = 300,
        .bullet_dy = -1,
        .hp = 20,
        .x_speed = 0.0003,
        .y_speed = 0.0003,
};

class Player : public Character
{
public:
    Player(Window_State window_state, Bullet_list *list, Character_config cfg) : Character(window_state, list, cfg)
    {
        strike_sound = new Sound(strike_sound_file_name);
        init();
    }

    void init()
    {
        _init_position();
        hp = initial_hp;
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
            fire();
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

        refresh_reload(dt);
    }

    void draw()
    {
        Character::draw();
        _draw_hp();
    }

    void fire()
    {
        if (can_strike())
        {
            Character::fire();
            strike_sound->play();
        }
    }

    void destroy()
    {
        Character::destroy();
        strike_sound->destroy();
    }

private:
    const char *strike_sound_file_name = "assets/sounds/strike.mp3";
    SDL_Color hp_full = {0, 255, 200};
    SDL_Color hp_empty = {122, 122, 122};
    Sound *strike_sound;
    float intitial_y_offset_relative = 0.05;
    float hp_bar_size_relative = 0.1;
    int hp_bars_in_line = 10;
    int max_hp = 20;

    void _init_position()
    {
        x = (screen->w - w) / 2;
        y = (1 - intitial_y_offset_relative) * screen->h - h;
    }

    void _draw_hp()
    {
        SDL_Rect dest;
        float size = w * hp_bar_size_relative;
        float offset = size * hp_bar_size_relative;
        float offset_from_player = h * hp_bar_size_relative;

        for (int i = 0; i < max_hp; i++)
        {
            dest.x = x + (i % hp_bars_in_line) * size + offset;
            dest.y = y + h + ceil(i / hp_bars_in_line) * size + offset + offset_from_player;
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

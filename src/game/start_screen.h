
#pragma once
#include "../engine/engine.h"
#include "../engine/collider.h"
#include "background.h"

#define START_SCREEN_BACKGROUND_FILE "assets/images/backgrounds/bg_1.jpg"

class Start_Screen
{
public:
    Start_Screen(Window_State window_state, TTF_Font *engine_font)
    {
        renderer = window_state.renderer;
        font = engine_font;
        screen = window_state.screen;

        background = new Background(window_state, START_SCREEN_BACKGROUND_FILE);
        background->speed = 0.0;

        button_text = new Text(start_button_message, renderer, font);
        button_text->set_color(220, 200, 224, 0);
    }

    void draw()
    {
        background->draw();

        _init_button_background();
        _draw_rect(button, bg_color);

        _init_button_border();
        _draw_rect(border, border_color);

        _draw_button_text();
    }

    void handle_events(int *keyboard, Mouse *mouse, bool *start_screen_on)
    {
        bool is_button_clicked = Collider::is_point_in_box(mouse->x, mouse->y, button.x, button.y, button.w, button.h);

        if (mouse->buttons[1] == 1 && is_button_clicked)
        {
            *start_screen_on = false;
            mouse->buttons[1] == 0;
            return;
        }

        if (keyboard[SDL_SCANCODE_RETURN] == 1)
        {
            *start_screen_on = false;
            keyboard[SDL_SCANCODE_RETURN] == 0;
        }
    }

private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    Screen *screen;
    Background *background;
    Text *button_text;
    SDL_Rect button;
    SDL_Rect border;
    SDL_Color bg_color = {110, 13, 130};
    SDL_Color border_color = {73, 4, 87};
    float scale = 2.4;
    int border_width = 3;
    const char *start_button_message = "Start Game";

    void _init_button_background()
    {
        int width = button_text->dest.w * scale;
        int height = button_text->dest.h * scale;
        button.x = button_text->dest.x - (width - button_text->dest.w) * 0.5;
        button.y = button_text->dest.y - (height - button_text->dest.h) * 0.5;
        button.w = width;
        button.h = height;
    }

    void _init_button_border()
    {
        border.x = button.x + border_width;
        border.y = button.y + border_width;
        border.w = button.w - border_width * 2;
        border.h = button.h - border_width * 2;
    }

    void _draw_rect(SDL_Rect dest, SDL_Color button_color)
    {
        SDL_SetRenderDrawColor(renderer, button_color.r, button_color.g, button_color.b, button_color.a);
        SDL_RenderFillRect(renderer, &dest);
    }

    void _draw_button_text()
    {
        int x = (screen->w - button_text->dest.w) * 0.5;
        int y = screen->h * 0.4;
        button_text->draw(x, y);
    }
};
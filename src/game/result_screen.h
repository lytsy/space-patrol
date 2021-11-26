
#pragma once
#include "../engine/engine.h"
#include "background.h"

class Result_Screen
{

public:
    Result_Screen(Window_State window_state, TTF_Font *engine_font)
    {
        renderer = window_state.renderer;
        font = engine_font;
        screen = window_state.screen;

        background = new Background(window_state);
        background->speed = 0.0;

        header = new Text("_", renderer, font);
        header->set_color(0, 255, 50, 0);

        score_msg = new Text("_", renderer, font);
        score_msg->set_color(0, 150, 150, 0);

        hint = new Text("_", renderer, font);
        hint->set_color(0, 150, 150, 0);
    }

    void refresh(const char *header_msg, int score, const char *hint_msg)
    {
        header->set_message(header_msg);

        const char *pattern = "Your score: %d";
        int length = snprintf(NULL, 0, pattern, score);
        char *str = (char *)malloc(length + 1);
        snprintf(str, length + 1, pattern, score);
        score_msg->set_color(0, 150, 150, 0);
        score_msg->set_message(str);
        free(str);

        hint->set_message(hint_msg);
    }

    void draw()
    {
        background->draw();
        _draw_shadow();
        _draw_messages();
    }

private:
    SDL_Renderer *renderer;
    Text *header;
    Text *score_msg;
    Text *hint;
    TTF_Font *font;
    Screen *screen;
    Background *background;
    float text_x_offset_relative = 0.07;
    float text_y_offset_relative = 0.4;

    void _draw_shadow()
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 121, 67, 87, 80);
        SDL_RenderFillRect(renderer, NULL);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

    void _draw_messages()
    {
        int size, x, y;
        size = (screen->w + screen->h) * text_x_offset_relative;

        header->scale_dest_to_width(size);
        x = _x_aligned_to_center(header);
        y = screen->h * text_y_offset_relative - header->dest.h * 0.5;
        header->draw(x, y);

        x = _x_aligned_to_center(score_msg);
        y += header->dest.h;
        score_msg->draw(x, y);

        x = _x_aligned_to_center(hint);
        y += score_msg->dest.h;
        hint->draw(x, y);
    }

    int _x_aligned_to_center(Text *text)
    {
        return (screen->w * 0.5 - text->dest.w * 0.5);
    }
};
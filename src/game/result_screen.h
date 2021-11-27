
#pragma once
#include "../engine/engine.h"
#include "background.h"

#define TOTAL_SCORE_PATTERN "Total score: %d"
#define LEVEL_SCORE_PATTERN "Level score: %d"

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

        _init_text(&header, "_", header_color);
        _init_text(&score_msg, "_", text_color);
        _init_text(&total_score_msg, "_", text_color);
        _init_text(&hint, "_", text_color);
    }

    void refresh(const char *header_msg, int score, int total_score, const char *hint_msg)
    {
        header->set_message(header_msg);

        _create_text_from_pattern(total_score_msg, TOTAL_SCORE_PATTERN, total_score);
        _create_text_from_pattern(score_msg, LEVEL_SCORE_PATTERN, score);

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
    Text *total_score_msg;
    Text *hint;
    TTF_Font *font;
    Screen *screen;
    Background *background;
    SDL_Color header_color = {0, 255, 50, 0};
    SDL_Color text_color = {0, 150, 150, 0};
    float text_x_offset_relative = 0.07;
    float text_y_offset_relative = 0.3;

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
        y = screen->h * text_y_offset_relative;
        header->draw(x, y);

        x = _x_aligned_to_center(total_score_msg);
        y += header->dest.h;
        total_score_msg->draw(x, y);

        x = _x_aligned_to_center(score_msg);
        y += total_score_msg->dest.h;
        score_msg->draw(x, y);

        x = _x_aligned_to_center(hint);
        y += score_msg->dest.h;
        hint->draw(x, y);
    }

    int _x_aligned_to_center(Text *text)
    {
        return (screen->w * 0.5 - text->dest.w * 0.5);
    }

    void _init_text(Text **text, const char *msg, SDL_Color color)
    {
        *text = new Text(msg, renderer, font);
        Text *tmp = *text;
        tmp->set_color(color.r, color.g, color.b, color.a);
    }

    void _create_text_from_pattern(Text *text, const char *pattern, int number)
    {
        int length = snprintf(NULL, 0, pattern, number);
        char *str = (char *)malloc(length + 1);
        snprintf(str, length + 1, pattern, number);

        text->set_message(str);
        free(str);
    }
};
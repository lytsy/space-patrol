
#include "../engine/engine.h"

#define MESSAGES_LEFT_OFFSET_RELATIVE 0.01
#define HINTS_MESSAGE "move(arrows) fire(space) "

class Info_Vidget
{
public:
    Info_Vidget(Window_State win_state, TTF_Font *engine_font)
    {
        font = engine_font;
        renderer = win_state.renderer;
        screen = win_state.screen;

        _init_text(&score_message, "_", text_color);
        _init_text(&total_score_message, "_", text_color);
        _init_text(&level_message, "_", text_color);
        _init_text(&hints, HINTS_MESSAGE, hints_color);
        _refresh_hints_position();
    }

    void refresh(int level, int total_score, int score)
    {
        _create_text_from_pattern(total_score_message, "total score: %d", total_score);
        _create_text_from_pattern(level_message, "level: %d", level);
        _create_text_from_pattern(score_message, "level score: %d", score);
        _refresh_hints_position();
    }

    void draw()
    {
        hints->draw();
        _draw_line(total_score_message, 0);
        _draw_line(score_message, 1);
        _draw_line(level_message, 2);
    }

private:
    SDL_Renderer *renderer;
    Screen *screen;
    TTF_Font *font;
    Text *score_message;
    Text *total_score_message;
    Text *level_message;
    Text *hints;
    SDL_Color text_color = {70, 255, 70, 0};
    SDL_Color hints_color = {100, 200, 100, 0};

    void _init_text(Text **text, const char *msg, SDL_Color color)
    {
        *text = new Text(msg, renderer, font);
        Text *tmp = *text;
        tmp->set_color(color.r, color.g, color.b, color.a);
    }

    void _refresh_hints_position()
    {
        hints->dest.y = screen->h - hints->dest.h * 1.2;
        hints->dest.x = screen->w - hints->dest.w;
    }

    void _create_text_from_pattern(Text *text, const char *pattern, int number)
    {
        int length = snprintf(NULL, 0, pattern, number);
        char *str = (char *)malloc(length + 1);
        snprintf(str, length + 1, pattern, number);

        text->set_message(str);
        free(str);
    }

    void _draw_line(Text *text, int line)
    {
        int message_x = (1 - MESSAGES_LEFT_OFFSET_RELATIVE) * screen->w - text->dest.w;
        int message_y = text->dest.h * line;
        text->draw(message_x, message_y);
    }
};
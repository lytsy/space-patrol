
#pragma once
#define SDL_MAIN_HANDLED
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_ttf/include/SDL2/SDL_ttf.h"
#include <stdio.h>

class Text
{
public:
    SDL_Color color = {255, 0, 0, 0};
    SDL_Rect dest;

    Text(const char *msg, SDL_Renderer *sdl_renderer, TTF_Font *ttf_font)
    {
        renderer = sdl_renderer;
        font = ttf_font;
        message = (char *)msg;
        _init_texture();
        _init_dest();
    }

    void set_message(const char *msg)
    {
        message = (char *)msg;
        _init_texture();
        _init_dest();
    }

    void set_dest(int x, int y, int w, int h)
    {
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
    };

    void get_dest(SDL_Rect *rect)
    {
        *rect = dest;
    };

    void draw()
    {
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    };

    void destroy()
    {
        SDL_DestroyTexture(texture);
    }

private:
    char *message;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *texture;

    void _init_texture()
    {
        SDL_Surface *surface = TTF_RenderText_Blended(font, message, color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            printf("Failed CreateTexture: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    };

    void _init_dest()
    {
        dest.x = 0;
        dest.y = 0;
        if (TTF_SizeText(font, message, &dest.w, &dest.h))
        {
            printf("Failed TTF_SizeText: %s\n", SDL_GetError());
        }
    }
};

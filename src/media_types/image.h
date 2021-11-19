
#pragma once
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_image/include/SDL2/SDL_image.h"
#include <stdio.h>

class Image
{
public:
    SDL_Rect src;

    Image(const char *file, SDL_Renderer *sdl_renderer)
    {
        renderer = sdl_renderer;
        _loadtexture(file);
        _init_rect(&src);
        _init_rect(&dest);
    }

    void scale_to_width(int *w, int *h, SDL_Window *window, float relative_width)
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        float proportion = (float)src.h / src.w;
        *w = window_width * relative_width;
        *h = *w * proportion;
    }

    void draw(int x, int y, int w, int h)
    {
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
        SDL_RenderCopy(renderer, texture, &src, &dest);
    };

    void destroy()
    {
        SDL_DestroyTexture(texture);
    }

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect dest;

    void _loadtexture(const char *file)
    {
        SDL_Surface *surface = IMG_Load(file);
        if (!surface)
        {
            printf("Failed IMG_Load: %s\n", SDL_GetError());
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            printf("Failed CreateTexture: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    };

    void _init_rect(SDL_Rect *rect)
    {
        rect->x = 0;
        rect->y = 0;
        SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    }
};


#pragma once
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_image/include/SDL2/SDL_image.h"
#include <stdio.h>

class Image
{
public:
    Image(const char *file, SDL_Renderer *sdl_renderer)
    {
        filename = (char *)file;
        renderer = sdl_renderer;
        _load_texture();
        _init_src();
        _init_dest();
    }

    void set_src(int x, int y, int w, int h)
    {
        src.x = x;
        src.y = y;
        src.w = w;
        src.h = h;
        p_src = &src;
    };

    void reset_src()
    {
        p_src = NULL;
    };

    void set_dest(int x, int y, int w, int h)
    {
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
        p_dest = &dest;
    };

    void get_dest(SDL_Rect *rect)
    {
        *rect = dest;
    };

    void reset_dest()
    {
        p_dest = NULL;
    };

    void draw()
    {
        SDL_RenderCopy(renderer, texture, p_src, p_dest);
    };

    void destroy()
    {
        SDL_DestroyTexture(texture);
    }

private:
    char *filename;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Rect *p_src;
    SDL_Rect *p_dest;

    void _load_texture()
    {
        SDL_Surface *surface = IMG_Load(filename);
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

    void _init_src()
    {
        src.x = 0;
        src.y = 0;
        SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
        p_src = NULL;
    }

    void _init_dest()
    {
        dest.x = 0;
        dest.y = 0;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        p_dest = &dest;
    }
};

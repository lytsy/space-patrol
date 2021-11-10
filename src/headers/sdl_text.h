
#define SDL_MAIN_HANDLED
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_ttf/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include "config.h"

class SDL_Text
{
public:
    SDL_Text(const char *msg, SDL_Renderer *sdl_renderer, TTF_Font *ttf_font)
    {
        message = (char *)msg;
        renderer = sdl_renderer;
        font = ttf_font;
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
    TTF_Font *fffont;
    TTF_Font *font;
    SDL_Color color = {255, 0, 0, 0};
    SDL_Texture *texture;
    SDL_Rect dest;

    void _init_texture()
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, message, color);
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

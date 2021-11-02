#define SDL_MAIN_HANDLED
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_image/include/SDL2/SDL_image.h"
#include "../../vendor/sdl_mixer/include/SDL2/SDL_mixer.h"
#include "../../vendor/sdl_ttf/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include "config.h"

class SDL_Controller
{
public:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Surface *icon_surface;
    void init()
    {
        _init_sdl();
        _init_sdl_window();
        _init_sdl_renderer();
        _init_sdl_image();
        _init_sdl_mixer();
        _init_sdl_ttf();
        _init_sdl_window_icon();
        load_font(font);
    };
    void destroy()
    {
        _destroy_sdl_image();
        _destroy_sdl_mixer();
        _destroy_sdl_ttf();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        _destroy_sdl_window_icon();
        destroy_font(font);
    };
    void load_font(TTF_Font *font)
    {
        font = TTF_OpenFont(WINDOW_FONT, WINDOW_FONT_SIZE);
        if (!font)
        {
            printf("Failed TTF_OpenFont: %s\n", TTF_GetError());
        }
    }
    void destroy_font(TTF_Font *font)
    {
        TTF_CloseFont(font);
    };

private:
    void _init_sdl(void)
    {

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("Failed SDL_Init.\nSDL Error: '%s'\n", SDL_GetError());
            exit(1);
        }
    }
    void _init_sdl_window()
    {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
        if (!window)
        {
            printf("Failed SDL_CreateWindow.\nSDL Error: '%s'\n", SDL_GetError());
            exit(1);
        }
    };
    void _init_sdl_renderer()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!renderer)
        {
            printf("Failed SDL_CreateRenderer.\nSDL Error: '%s'\n", SDL_GetError());
            exit(1);
        }
    };
    void _init_sdl_image()
    {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    }
    void _init_sdl_mixer()
    {
        int flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;
        int initted = Mix_Init(flags);
        if (initted & flags != flags)
        {
            printf("Failed Mix_Init.\nSDL Error: '%s'\n", Mix_GetError());
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        {
            printf("Couldn't initialize SDL Mixer\n");
            exit(1);
        }

        Mix_AllocateChannels(8);
        Mix_VolumeMusic(MIX_MAX_VOLUME * WINDOW_VOLUME);
    }
    void _init_sdl_window_icon()
    {
        icon_surface = IMG_Load(WINDOW_ICON);
        SDL_SetWindowIcon(window, icon_surface);
    }
    void _init_sdl_ttf()
    {
        if (TTF_Init() == -1)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(1);
        }
    }
    void _destroy_sdl_image()
    {
        IMG_Quit();
    }
    void _destroy_sdl_mixer()
    {
        Mix_CloseAudio();
        Mix_Quit();
    }
    void _destroy_sdl_ttf()
    {
        TTF_Quit();
    }
    void _destroy_sdl_window_icon()
    {
        SDL_FreeSurface(icon_surface);
    }
};
SDL_Controller sdl;

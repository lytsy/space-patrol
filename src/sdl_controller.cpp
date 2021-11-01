
#include "headers/sdl_controller.h"
#include <stdio.h>
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "MyApp"
void sdl_init_image(void);
void sdl_destroy_image(void);
void sdl_destroy(void);
SDL_Renderer *renderer;
SDL_Window *window;
void init_sdl_mixer();
void sdl_destroy_mixer();
void sdl_ttf_init();
void sdl_ttf_destroy();

int sdl_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    sdl_init_image();
    init_sdl_mixer();
    sdl_ttf_init();
    return 0;
}

void sdl_destroy()
{
    sdl_destroy_image();
    sdl_destroy_mixer();
    sdl_ttf_destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void sdl_init_image()
{
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void sdl_destroy_image()
{
    IMG_Quit();
}

void init_sdl_mixer()
{
    int flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;
    int initted = Mix_Init(flags);
    if (initted & flags != flags)
    {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(8);
}

void sdl_destroy_mixer()
{
    Mix_CloseAudio();
    Mix_Quit();
}

void sdl_ttf_init()
{
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
}

void sdl_ttf_destroy()
{
    TTF_Quit();
}
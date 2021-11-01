
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
    return 0;
}

void sdl_destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    sdl_destroy_image();
}

void sdl_init_image()
{
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void sdl_destroy_image()
{
    IMG_Quit();
}

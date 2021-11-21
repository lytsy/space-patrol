#pragma once
#define SDL_MAIN_HANDLED
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_image/include/SDL2/SDL_image.h"
#include "../../vendor/sdl_mixer/include/SDL2/SDL_mixer.h"
#include "../../vendor/sdl_ttf/include/SDL2/SDL_ttf.h"
#include <stdio.h>

#include "../media_types/text.h"
#include "config.h"
#include "console.h"
#include "events.h"

#define FPS_MESSAGE_LINE_POSITION 1
#define MESSAGES_OFFSET_RELATIVE 0.01

class Screen
{
public:
    int w;
    int h;
    float w_scale;
    float h_scale;
};

class Window_State
{
public:
    Screen *screen;
    SDL_Renderer *renderer;
    SDL_Window *window;
};

class Engine
{
public:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Surface *icon_surface;
    bool running;
    long dt = 0;
    int fps = 0;
    Text *fps_message;
    int keyboard[SDL_NUM_SCANCODES] = {0};
    Screen screen;
    Window_State window_state;

    void init()
    {
        running = true;
        hide_console();
        _init_sdl();
        _init_sdl_window();
        _init_sdl_renderer();
        _init_sdl_image();
        _init_sdl_mixer();
        _init_sdl_ttf();
        _init_sdl_window_icon();
        _load_font();
        _init_fps_message();
        _init_screen();
        _init_window_state();
    }

    void destroy()
    {
        _destroy_font();
        _destroy_sdl_window_icon();
        _destroy_sdl_ttf();
        _destroy_sdl_mixer();
        _destroy_sdl_image();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    void handle_events()
    {
        SDL_events(&running, keyboard);
    }

    void render_clear()
    {
        SDL_RenderClear(renderer);
    }

    void render_present()
    {
        SDL_RenderPresent(renderer);
    }

    void check_errors()
    {
        error = (char *)SDL_GetError();
        if (strlen(error) != 0)
        {
            printf("SDL Error: %s\n", error);
            SDL_ClearError();
        }
    }

    void count_delta_time()
    {
        long now = SDL_GetTicks();
        dt = now - _then;
        _then = now;
    }

    void count_fps()
    {
        _past_time += dt;
        _frames += 1;
        if (_past_time > 1000)
        {
            fps = _frames;
            _frames = 0;
            _past_time -= 1000;
        }
    }

    void draw_fps()
    {
        _refresh_fps_message_text();
        _refresh_fps_message_position();
        fps_message->draw();
    }

    void refresh_screen()
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        screen.w_scale = (float)w / screen.w;
        screen.h_scale = (float)h / screen.h;

        screen.w = w;
        screen.h = h;
    }

private:
    char *error;
    long _then = 0;
    long _past_time = 0;
    int _frames = 0;

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
    }

    void _init_sdl_renderer()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!renderer)
        {
            printf("Failed SDL_CreateRenderer.\nSDL Error: '%s'\n", SDL_GetError());
            exit(1);
        }
    }

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

    void _load_font()
    {
        font = TTF_OpenFont(WINDOW_FONT, WINDOW_FONT_SIZE);
        if (!font)
        {
            printf("Failed TTF_OpenFont: %s\n", TTF_GetError());
        }
    }

    void _init_fps_message()
    {
        fps_message = new Text("fps", renderer, font);
        fps_message->color = {255, 255, 0, 0};
    }

    void _init_screen()
    {
        SDL_GetWindowSize(window, &screen.w, &screen.h);
        screen.w_scale = 1.0;
        screen.h_scale = 1.0;
    }

    void _init_window_state()
    {
        window_state.renderer = renderer;
        window_state.window = window;
        window_state.screen = &screen;
    }

    void _refresh_fps_message_text()
    {
        char fps_text[20];
        sprintf(fps_text, "fps %d", fps);
        fps_message->set_message(fps_text);
    }

    void _refresh_fps_message_position()
    {
        fps_message->dest.x = (1 - MESSAGES_OFFSET_RELATIVE) * screen.w - fps_message->dest.w;
        fps_message->dest.y = FPS_MESSAGE_LINE_POSITION * fps_message->dest.h;
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

    void _destroy_font()
    {
        TTF_CloseFont(font);
    };

    void _destroy_sdl_window_icon()
    {
        SDL_FreeSurface(icon_surface);
    }
};

Engine engine;

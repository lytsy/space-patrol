
#define SDL_MAIN_HANDLED
#include "../../vendor/sdl/include/SDL2/SDL.h"
#include "../../vendor/sdl_mixer/include/SDL2/SDL_mixer.h"
#include <stdio.h>

class Sound
{
public:
    Sound(const char *file)
    {
        filename = (char *)file;
        load();
    }
    void play()
    {
        if (Mix_PlayMusic(music, 1) == -1)
        {
            printf("Failed Mix_PlayMusic: %s\n", Mix_GetError());
        }
    };
    void destroy()
    {
        Mix_FreeMusic(music);
    }

private:
    char *filename;
    Mix_Music *music;
    void load()
    {
        music = Mix_LoadMUS(filename);
        if (!music)
        {
            printf("Failed Mix_LoadMUS(%s): %s\n", filename, Mix_GetError());
        }
    };
};
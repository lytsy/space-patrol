
src=src/main.cpp src/sdl_controller.cpp 
sdl=-Ivendor/sdl/include/SDL2 -Lvendor/sdl/lib -lSDL2main -lSDL2
sdl_image=-Ivendor/sdl_image/include/SDL2 -Lvendor/sdl_image/lib -lSDL2_image
sdl_mixer=-Ivendor/sdl_mixer/include/SDL2 -Lvendor/sdl_mixer/lib -lSDL2_mixer
sdl_ttf=-Ivendor/sdl_ttf/include/SDL2 -Lvendor/sdl_ttf/lib -lSDL2_ttf
all:
	g++ -o Main ${src} -lmingw32  ${sdl} ${sdl_image} ${sdl_mixer} ${sdl_ttf}
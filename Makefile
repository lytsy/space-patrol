
src=src/main.cpp src/sdl_controller.cpp 
sdl=-Ivendor/sdl/include/SDL2 -Lvendor/sdl/lib -lSDL2main -lSDL2
sdl_image=-Ivendor/sdl_image/include/SDL2 -Lvendor/sdl_image/lib -lSDL2_image
all:
	g++ -o Main ${src} -lmingw32  ${sdl} ${sdl_image}
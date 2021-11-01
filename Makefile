
src=src/main.cpp src/sdl_controller.cpp 
sdl=-Ivendor/sdl/include/SDL2 -Lvendor/sdl/lib -lSDL2main -lSDL2
all:
	g++ -o Main ${src} -lmingw32  ${sdl}
#include "../include/debug.h"
#include "../include/sdl_manager.h"

int main(int argc, char** argv)
{
    if (argc < 1 || !argv || sdl_init())
        return 1;
    
    SDL_Window* window = create_window(WIDTH, HEIGHT);
    SDL_Renderer* renderer = create_renderer(window);

    sdl_quit(renderer, window);

    return 0;
}

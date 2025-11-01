#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 500
#define HEIGHT 500

int sdl_init();
void sdl_quit(SDL_Renderer* renderer, SDL_Window* window);
SDL_Window* create_window(int w, int h);
SDL_Renderer* create_renderer(SDL_Window* window);

#endif /* ! SDL_MANAGER_H */

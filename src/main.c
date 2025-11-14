#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIN_TITLE "sorender"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include "render/pixel_buffer.h"

int main(void)
{
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                fprintf(stderr, "ERROR: failed to initialize SDL_INIT_VIDEO: %s\n", SDL_GetError());
                return 1;
        }

        SDL_Window *window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
        if (window == NULL) {
                fprintf(stderr, "ERROR: failed to create SDL_Window: %s\n", SDL_GetError());
                return 1;
        }

        SDL_Surface *surface = SDL_GetWindowSurface(window);
        SDL_PixelFormat *surface_fmt = surface->format;

        PixelBuffer *pixelbuf = malloc(sizeof(PixelBuffer));

        bool is_running = true; 

        while (is_running) {
                clear_pixel_buffer(pixelbuf, surface_fmt, 255, 0, 0);

                putpixel(pixelbuf, surface_fmt, 400, 300, 255, 255, 255);
                draw_pixel_buffer(surface, pixelbuf);

                SDL_UpdateWindowSurface(window);

                SDL_Event e;
                while (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                                is_running = false;
                        }
                }
        }

        free(pixelbuf);

        SDL_Quit();

        return 0;
}


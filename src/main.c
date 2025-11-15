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

#include "render/render_context.h"
#include "render/pixel_buffer.h"
#include "render/triangle.h"
#include "render/vertex.h"

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
        if (!pixelbuf) {
                fprintf(stderr, "ERROR: failed to allocate memory\n"); 
                return 1;
        }

        Context ctx = {
                .pixelbuf = pixelbuf,
                .surface = surface,
                .window = window,
                .pixel_fmt = surface_fmt,
                .width = WIN_WIDTH,
                .height = WIN_HEIGHT
        };

        bool is_running = true; 
        Vertex a = {
                .x = 100,
                .y = 100,
                .r = 0,
                .g = 0,
                .b = 255 
        };

        Vertex b = {
                .x = 700,
                .y = 100,
                .r = 0,
                .g = 255,
                .b = 0 
        };

        Vertex c = {
                .x = 1000,
                .y = 500,
                .r = 255,
                .g = 0,
                .b = 0 
        };

        while (is_running) {
                clear_pixel_buffer(&ctx, 100, 100, 100);

                draw_triangle(&ctx, a, b, c);
                draw_pixel_buffer(&ctx);

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


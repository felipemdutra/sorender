#include "pixel_buffer.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <string.h>

void putpixel(PixelBuffer *pixelbuf, SDL_PixelFormat *fmt, u32 x, u32 y, u8 r, u8 g, u8 b) {
        if (pixelbuf == NULL || x >= PIXEL_BUFFER_WIDTH || y >= PIXEL_BUFFER_HEIGHT) {
                return;
        }

        pixelbuf->pixels[y][x] = SDL_MapRGB(fmt, r, g, b);
}

void draw_pixel_buffer(SDL_Surface *surface, PixelBuffer *pixelbuf) {
        /* 
         * SDL_Surface is not a tightly packed WIDTH * HEIGHT * byte_per_pixel 
         * array. And for that reason, we need to copy pixelbuf into surface's
         * pixels by row, using the correct padding.
         */

        u8 *dst = (u8*)surface->pixels;
        u32 *src = &pixelbuf->pixels[0][0];

        SDL_LockSurface(surface);

        for (size_t y = 0; y < PIXEL_BUFFER_HEIGHT; ++y) {
                memcpy(
                        dst + y * surface->pitch,
                        src + y * PIXEL_BUFFER_WIDTH,
                        PIXEL_BUFFER_WIDTH * sizeof(u32) 
                        );
        }

        SDL_UnlockSurface(surface);
}

void clear_pixel_buffer(PixelBuffer *pixelbuf, SDL_PixelFormat *fmt, u8 r, u8 g, u8 b) {
        for (size_t y = 0; y < PIXEL_BUFFER_HEIGHT; ++y) {
                for (size_t x = 0; x < PIXEL_BUFFER_WIDTH; ++x) {
                        putpixel(pixelbuf, fmt, x, y, r, g, b);
                }
        }
}


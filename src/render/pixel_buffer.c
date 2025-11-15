#include "pixel_buffer.h"
#include "render_context.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void putpixel(Context *ctx, u32 x, u32 y, u8 r, u8 g, u8 b) {
        if (!ctx || !ctx->pixel_fmt || x >= PIXEL_BUFFER_WIDTH || y >= PIXEL_BUFFER_HEIGHT) {
                return;
        }

        ctx->pixelbuf->pixels[y][x] = SDL_MapRGB(ctx->pixel_fmt, r, g, b);
}

void draw_pixel_buffer(Context *ctx) {
        /* 
         * SDL_Surface is not a tightly packed WIDTH * HEIGHT * byte_per_pixel 
         * array. And for that reason, we need to copy pixelbuf into surface's
         * pixels by row, using the correct padding.
         */
        assert(ctx && ctx->surface && ctx->pixelbuf);
        u8 *dst = (u8*)ctx->surface->pixels;
        u32 *src = &ctx->pixelbuf->pixels[0][0];

        SDL_LockSurface(ctx->surface);

        for (size_t y = 0; y < PIXEL_BUFFER_HEIGHT; ++y) {
                memcpy(
                        dst + y * ctx->surface->pitch,
                        src + y * PIXEL_BUFFER_WIDTH,
                        PIXEL_BUFFER_WIDTH * sizeof(u32) 
                        );
        }

        SDL_UnlockSurface(ctx->surface);
}

void clear_pixel_buffer(Context *ctx, u8 r, u8 g, u8 b) {
        for (size_t y = 0; y < PIXEL_BUFFER_HEIGHT; ++y) {
                for (size_t x = 0; x < PIXEL_BUFFER_WIDTH; ++x) {
                        putpixel(ctx, x, y, r, g, b);
                }
        }
}


#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <SDL2/SDL.h>
#include "../defs.h"

#define PIXEL_BUFFER_WIDTH 800
#define PIXEL_BUFFER_HEIGHT 600

typedef struct PixelBuffer {
        u32 pixels[PIXEL_BUFFER_HEIGHT][PIXEL_BUFFER_WIDTH];
} PixelBuffer;

void putpixel(PixelBuffer *pixelbuf, SDL_PixelFormat *fmt, u32 x, u32 y, u8 r, u8 g, u8 b);

/**
 * @brief Draws the pixel buffer to the SDL surface.
 *
 * @param surface - A pointer to an SDL surface to draw on.
 * @param pixelbuf - The pixel buffer to draw.
 */
void draw_pixel_buffer(SDL_Surface *surface, PixelBuffer *pixelbuf);

/**
 * @brief Clears the pixel buffer with the specified RGB value.
 *
 * @param pixelbuf - The pixel buffer to clear.
 * @param rgb - The RGB value to clear the screen with.
 */
void clear_pixel_buffer(PixelBuffer *pixelbuf, SDL_PixelFormat *fmt, u8 r, u8 g, u8 b);

#endif


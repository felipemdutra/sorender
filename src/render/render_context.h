#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <SDL2/SDL.h>

#include "pixel_buffer.h"

typedef struct Context {
        PixelBuffer *pixelbuf;

        SDL_Window *window;
        SDL_Surface *surface;
        SDL_PixelFormat *pixel_fmt;

        int width, height;
} Context ;

#endif


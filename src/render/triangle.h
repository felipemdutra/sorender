#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "render_context.h"
#include <stddef.h>

#define STRIDE 5

#include "vertex.h"

/**
 *
 */
void draw_triangle(Context *ctx, Vertex a, Vertex b, Vertex c);

#endif


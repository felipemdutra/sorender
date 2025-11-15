#include <assert.h>
#include <fcmath/vector.h>
#include <math.h>
#include <stdio.h>
#include "triangle.h"
#include "pixel_buffer.h"
#include "render_context.h"
#include "render_context.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b));

enum VertexIndices {
        X_INDEX = 0,
        Y_INDEX,
        R_INDEX,
        G_INDEX,
        B_INDEX
};

struct BoundingBox {
        vec2 bottom_left;
        vec2 top_right;
};

static struct BoundingBox get_triangle_bounding_box(Vertex a, Vertex b, Vertex c)
{
        struct BoundingBox bb;

        u32 min_x = MIN(a.x, b.x);
        bb.bottom_left.x = MIN(min_x, c.x);

        u32 min_y = MIN(a.y, b.y);
        bb.bottom_left.y = MIN(min_y, c.y);

        u32 max_x = MAX(a.x, b.x);
        bb.top_right.x = MAX(max_x, c.x);

        u32 max_y = MAX(a.y, b.y);
        bb.top_right.y = MAX(max_y, c.y);

        return bb;
}

static float calculate_area(vec2 a, vec2 b, vec2 c)
{
        return fabs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0f;
}


void draw_triangle(Context *ctx, Vertex a, Vertex b, Vertex c)
{
        // Find the triangle's bounding box.
        struct BoundingBox bb = get_triangle_bounding_box(a, b, c);

        // For each pixel inside the bounding box, check if it's inside the
        // triangle. We can do that with some cross product math.
        for (size_t x = bb.bottom_left.x; x < bb.top_right.x; ++x) {
                for (size_t y = bb.bottom_left.y; y < bb.top_right.y; ++y) {
                        vec2 ab = vec2_create(b.x - a.x, b.y - a.y);
                        vec2 ca = vec2_create(a.x - c.x, a.y - c.y);
                        vec2 bc = vec2_create(c.x - b.x, c.y - b.y);
                        // p is the pixel's coordinates
                        vec2 ap = vec2_create(x - a.x, y - a.y);
                        vec2 bp = vec2_create(x - b.x, y - b.y);
                        vec2 cp = vec2_create(x - c.x, y - c.y);

                        float cross1 = vec2_cross(ab, ap);
                        float cross2 = vec2_cross(bc, bp);
                        float cross3 = vec2_cross(ca, cp);

                        if (!(cross1 >= 0 && cross2 >= 0 && cross3 >= 0) && !(cross1 < 0 && cross2 < 0 && cross3 < 0)) { 
                                continue;
                        }

                        vec2 a_vec = vec2_create(a.x, a.y);
                        vec2 b_vec = vec2_create(b.x, b.y);
                        vec2 c_vec = vec2_create(c.x, c.y);
                        vec2 p_vec = vec2_create(x, y);

                        const float AREA_ABC = calculate_area(a_vec, b_vec, c_vec);
                        const float AREA_PAB = calculate_area(p_vec, a_vec, b_vec);
                        const float AREA_PBC = calculate_area(p_vec, b_vec, c_vec);
                        const float AREA_PCA = calculate_area(p_vec, c_vec, a_vec);

                        const float alpha = AREA_PBC / AREA_ABC;
                        const float beta = AREA_PCA / AREA_ABC;
                        const float gamma = AREA_PAB / AREA_ABC;

                        // Red
                        int pr = alpha * a.r + beta * b.r + gamma * c.r;

                        // Green
                        int pg = alpha * a.g + beta * b.g + gamma * c.g;

                        // Blue
                        int pb = alpha * a.b + beta * b.b + gamma * c.b;

                        putpixel(ctx, x, y, pr, pg, pb);
                }
        }
}


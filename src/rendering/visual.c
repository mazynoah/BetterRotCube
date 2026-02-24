#include "rendering/visual.h"

#include <SDL2/SDL_render.h>
#include <stdlib.h>

#include "geometry/point.h"
#include "geometry/triangle.h"
#include "geometry/vector.h"
#include "rendering/camera.h"

void draw_links(SDL_Renderer *renderer, Vertex *vertex_a)
{
    Links *links = vertex_a->links;
    Point *projection_a = project(vertex_a->position);
    if (!projection_a)
        return;

    while (links)
    {
        Vertex *vertex_b = links->vertex;
        Point *projection_b = project(vertex_b->position);

        if (!projection_b)
        {
            free(projection_a);
            return;
        }

        SDL_RenderDrawLine(renderer, projection_a->x, projection_a->y,
                           projection_b->x, projection_b->y);

        free(projection_b);
        links = links->next;
    }
    free(projection_a);
}

void draw_triangle(SDL_Renderer *renderer, Triangle *triangle)
{
    Point *projection_a = project(triangle->points[0]);
    Point *projection_b = project(triangle->points[1]);
    Point *projection_c = project(triangle->points[2]);
    if (!projection_a || !projection_b || !projection_c)
        goto exit;

    SDL_Vertex vertices[3] = {
        { { projection_a->x, projection_a->y }, { RED, 255 }, { 0.0f, 0.0f } },
        { { projection_b->x, projection_b->y }, { RED, 255 }, { 0.0f, 0.0f } },
        { { projection_c->x, projection_c->y }, { RED, 255 }, { 0.0f, 0.0f } },
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

exit:
    free(projection_a);
    free(projection_b);
    free(projection_c);
}

void draw_cube(SDL_Renderer *renderer, Cube *cube)
{
    int triangles[36] = { 0, 1, 2, 0, 2, 3,

                          5, 4, 7, 5, 7, 6,

                          4, 0, 3, 4, 3, 7,

                          1, 5, 6, 1, 6, 2,

                          3, 2, 6, 3, 6, 7,

                          4, 5, 1, 4, 1, 0 };

    for (size_t i = 0; i < 35; i += 3)
    {
        Triangle *t =
            create_triangle(cube->vertices[triangles[i]]->position,
                            cube->vertices[triangles[i + 1]]->position,
                            cube->vertices[triangles[i + 2]]->position);
        Point cp = *camera->position;
        sub_point(&cp, t->points[0]);
        if (dot_product(&cp, t->normal) < 0)
        {
            draw_triangle(renderer, t);
        }
        destroy_triangle(t);
    }

    SDL_SetRenderDrawColor(renderer, BLACK, 255);
    for (int i = 0; i < 8; i++)
    {
        draw_links(renderer, cube->vertices[i]);
    }
}

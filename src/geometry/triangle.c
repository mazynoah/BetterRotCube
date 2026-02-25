#include "geometry/triangle.h"

#include <stdlib.h>

#include "geometry/point.h"
#include "geometry/vector.h"

Triangle *create_triangle(Point *a, Point *b, Point *c)
{
    Triangle *triangle = malloc(sizeof(Triangle));

    if (!triangle)
        return NULL;

    triangle->points[0] = dup_point(a);
    triangle->points[1] = dup_point(b);
    triangle->points[2] = dup_point(c);
    triangle->normal = get_normal(triangle);

    return triangle;
}

void destroy_triangle(Triangle *triangle)
{
    free(triangle->points[0]);
    free(triangle->points[1]);
    free(triangle->points[2]);
    free(triangle->normal);
    free(triangle);
}

Point *get_normal(Triangle *t)
{
    Point a = *t->points[1];
    Point b = *t->points[2];
    sub_point(&a, t->points[0]);
    sub_point(&b, t->points[0]);

    Point normal = vector_cross(&a, &b);
    normal = vector_normalize(&normal);
    return create_point(normal.x, normal.y, normal.z);
}

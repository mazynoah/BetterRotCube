#include "geometry/triangle.h"

#include <stdlib.h>

#include "geometry/point.h"

Triangle *create_triangle(Point *a, Point *b, Point *c)
{
    Triangle *triangle = malloc(sizeof(Triangle));

    if (!triangle)
        return NULL;

    triangle->points[0] = dup_point(a);
    triangle->points[1] = dup_point(b);
    triangle->points[2] = dup_point(c);

    return triangle;
}

void destroy_triangle(Triangle *triangle)
{
    free(triangle->points[0]);
    free(triangle->points[1]);
    free(triangle->points[2]);
    free(triangle);
}

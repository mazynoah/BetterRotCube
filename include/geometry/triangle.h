#ifndef TRIANGE_H
#define TRIANGE_H

#include "geometry/point.h"

typedef struct triangle
{
    Point *points[3];
} Triangle;

Triangle *create_triangle(Point *a, Point *b, Point *c);
void destroy_triangle(Triangle *triangle);

#endif /* TRIANGE_H */

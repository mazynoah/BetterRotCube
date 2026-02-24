#ifndef TRIANGE_H
#define TRIANGE_H

#include "geometry/point.h"

typedef struct triangle
{
    Point *points[3];
    Point *normal;
} Triangle;

Triangle *create_triangle(Point *a, Point *b, Point *c);
void destroy_triangle(Triangle *triangle);
Point *get_normal(Triangle *t);

#endif /* TRIANGE_H */

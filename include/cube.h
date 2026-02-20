#ifndef CUBE_H
#define CUBE_H

#include "../include/vertex.h"

typedef struct cube
{
    Vertex **vertices;
    Vertex *center;
} Cube;

Cube *create_cube(int size, Vertex *origin);
void rot_cube_x(Cube *cube, Vertex *origin, double alpha);
void destroy_cube(Cube *cube);

#endif /* ! CUBE_H */

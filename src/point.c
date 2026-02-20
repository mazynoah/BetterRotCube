#include "point.h"
#include "debug.h"

#include <stdlib.h>

Point *create_point(double x, double y, double z)
{
  Point *point = malloc(sizeof(Point));
  if (!point)
    return ERROR("Could not create point->"), NULL;

  point->x = x;
  point->y = y;
  point->z = z;

  return point;
}

Point *add_point(Point *a, Point *b)
{
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;

  return a;
}

Point *sub_point(Point *a, Point *b)
{
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;

  return a;
}

Point *add_dir(Point *p, Direction d, double delta)
{
  switch (d)
  {
    case RIGHT:
      p->x += delta;
      break;
    case LEFT:
      p->x -= delta;
      break;
    case UP:
      p->y += delta;
      break;
    case DOWN:
      p->y -= delta;
      break;
    case FRONT:
      p->z += delta;
      break;
    case BACK:
      p->z -= delta;
      break;
  }

  return p;
}


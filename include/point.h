typedef enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  FRONT,
  BACK,
} Direction;

typedef struct point
{
  double x, y, z;
} Point;

Point *create_point(double x, double y, double z);
Point *add_point(Point *a, Point *b);
Point *sub_point(Point *a, Point *b);
Point *add_dir(Point *p, Direction d, double delta);


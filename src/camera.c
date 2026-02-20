#include "camera.h"
#include "debug.h"

#include <stdlib.h>
#include <math.h>

Camera *camera = NULL;

Point* init_camera(double x, double y, double z)
{
  camera = malloc(sizeof(Camera));
  if (!camera)
    return ERROR("Camera initialization failed."), NULL;

  camera->position = create_point(x, y, z);
  camera->look_ahead = create_point(x, y, z+1);
  camera->yaw = 0.0;
  camera->pitch = 0.0;

  return camera->position;
}

Point *move_camera(Direction d, double delta)
{
  add_dir(camera->look_ahead, d, delta);
  return add_dir(camera->position, d, delta);
}

Point *rotate_camera_x(double alpha, double delta)
{
  camera->pitch += alpha*delta;

  camera->pitch = camera->pitch > M_PI/2 - 0.01 ? M_PI/2 + 0.01 : camera->pitch;
  camera->pitch = camera->pitch < -M_PI/2 + 0.01 ? -M_PI/2 + 0.01 : camera->pitch;

  Point forward;

  forward.x = cos(camera->pitch) * sin(camera->yaw);
  forward.y = sin(camera->pitch);
  forward.z = cos(camera->pitch) * cos(camera->yaw);

  camera->look_ahead->x = camera->position->x + forward.x;
  camera->look_ahead->y = camera->position->y + forward.y;
  camera->look_ahead->z = camera->position->z + forward.z;

  return camera->look_ahead;
}

Point *rotate_camera_y(double alpha, double delta)
{
  camera->yaw += alpha*delta;

  Point forward;

  forward.x = cos(camera->pitch) * sin(camera->yaw);
  forward.y = sin(camera->pitch);
  forward.z = cos(camera->pitch) * cos(camera->yaw);

  camera->look_ahead->x = camera->position->x + forward.x;
  camera->look_ahead->y = camera->position->y + forward.y;
  camera->look_ahead->z = camera->position->z + forward.z;

  return camera->look_ahead;
}


#include "camera.h"

#include <math.h>
#include <stdlib.h>

#include "debug.h"
#include "vector.h"

Camera *camera = NULL;

Point *init_camera(double x, double y, double z) {
    camera = malloc(sizeof(Camera));
    if (!camera)
        return ERROR("Camera initialization failed."), NULL;

    camera->position = create_point(x, y, z);
    camera->look_ahead = create_point(x, y, z + 1);
    camera->yaw = 0.0;
    camera->pitch = 0.0;

    return camera->position;
}

Point get_forward() {
    Point forward;

    forward.x = cos(camera->pitch) * sin(camera->yaw);
    forward.y = sin(camera->pitch);
    forward.z = cos(camera->pitch) * cos(camera->yaw);

    return forward;
}

void move_camera(Direction dir, double delta) {
    Point forward = get_forward();
    forward = *vector_normalize(&forward);
    Point world_up = {0, 1, 0};
    Point right = *vector_normalize(vector_cross(&world_up, &forward));
    Point move;

    switch (dir) {
        case LEFT:
            move = *scalar_product(&right, -delta);
            break;
        case RIGHT:
            move = *scalar_product(&right, delta);
            break;
        case DOWN: case UP:
            add_dir(camera->look_ahead, dir, delta);
            add_dir(camera->position, dir, delta);
            return;
        case FRONT:
            move = *scalar_product(&forward, delta);
            break;
        case BACK:
            move = *scalar_product(&forward, -delta);
            break;
        default: 
            WARN("Received invalid camera direction.");
            return;
    }

    add_point(camera->position, &move);
    add_point(camera->look_ahead, &move);
}

Point *rotate_camera_x(double alpha, double delta) {
    camera->pitch += alpha * delta;

    camera->pitch =
            camera->pitch > M_PI / 2 - 0.01 ? M_PI / 2 + 0.01 : camera->pitch;
    camera->pitch =
            camera->pitch < -M_PI / 2 + 0.01 ? -M_PI / 2 + 0.01 : camera->pitch;

    Point forward = get_forward();

    camera->look_ahead->x = camera->position->x + forward.x;
    camera->look_ahead->y = camera->position->y + forward.y;
    camera->look_ahead->z = camera->position->z + forward.z;

    return camera->look_ahead;
}

Point *rotate_camera_y(double alpha, double delta) {
    camera->yaw += alpha * delta;

    Point forward = get_forward();

    camera->look_ahead->x = camera->position->x + forward.x;
    camera->look_ahead->y = camera->position->y + forward.y;
    camera->look_ahead->z = camera->position->z + forward.z;

    return camera->look_ahead;
}

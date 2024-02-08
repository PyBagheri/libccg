#ifndef DRAWING_GENERAL_H
#define DRAWING_GENERAL_H

#include <cvector/cvector.h>

Vector project_point(Vector p, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle, double zoom_factor);

#endif // DRAWING_GENERAL_H

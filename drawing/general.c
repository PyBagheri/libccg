#include <cvector/cvector.h>

Vector project_point(Vector p, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle, double zoom_factor) {
    // first move the vector relative to the camera,
    // then project it on the camera's plane normal.
    Vector proj = v_project(v_diff(p, camera_loc), camera_plane_normal);

    // the farther the vector is relative to the normal,
    // the less its 2D magnitude will be.
    double zoom_coeff = zoom_factor / v_abs(proj);

    return v_const_prod(v_project_on_plane(p, camera_plane_normal, camera_loc, camera_xy_angle), zoom_coeff);
}


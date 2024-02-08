#include <cvector/cvector.h>
#include <screen/charscreen.h>
#include <drawing/drawing.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 70
#define HEIGHT 30
#define EMPTY_FILL_CHAR ' '
#define FILL_CHAR 'W'
#define CENTER_CHAR '+'

#define ZOOM_FACTOR 50.0

#define PI 3.141592


void square(double side, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle);

CharScreen screen;


int main(void) {
    // prepare the screen
    screen = cscreen_init(WIDTH, HEIGHT, EMPTY_FILL_CHAR);

    Vector camera_plane_normal = v_unitize(v3d(-5, 0, -5));
    Vector camera_loc = v3d(5, 0, 5);
    double camera_xy_angle = .1;  // in radians

    square(2, camera_plane_normal, camera_loc, camera_xy_angle);

    cscreen_print(screen);

    // free the char 2d array
    cscreen_dealloc(screen);

    return 0;
}


void square(double side, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle) {
    Vector p1 = v3d(-side, side, 0);
    Vector p2 = v3d(side, -side, 0);
    Vector p3 = v3d(-side, -side, 0);
    Vector p4 = v3d(side, side, 0);

    Vector v1 = project_point(p1, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v2 = project_point(p2, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v3 = project_point(p3, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v4 = project_point(p4, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);

    // to show the center of the 'screen'.
    cscreen_putchar(screen, 0, 0, CENTER_CHAR);

    cscreen_putchar(screen, v1.vals[0], v1.vals[1], FILL_CHAR);
    cscreen_putchar(screen, v2.vals[0], v2.vals[1], FILL_CHAR);
    cscreen_putchar(screen, v3.vals[0], v3.vals[1], FILL_CHAR);
    cscreen_putchar(screen, v4.vals[0], v4.vals[1], FILL_CHAR);
}

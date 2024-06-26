#include <cvector/cvector.h>
#include <screen/pixelscreen.h>
#include <drawing/general.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 100
#define HEIGHT 70

#define EMPTY_FILL_R 255
#define EMPTY_FILL_G 255
#define EMPTY_FILL_B 255

#define FILL_R 30
#define FILL_G 100
#define FILL_B 150

#define ZOOM_FACTOR 50.0

#define PI 3.141592

void square(double side, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle);

PixelScreen screen;


int main(void) {
    // prepare the screen
    Pixel empty_fill_pixel = {.r = EMPTY_FILL_R, .g = EMPTY_FILL_G, .b = EMPTY_FILL_B};
    screen = ps_init(WIDTH, HEIGHT, empty_fill_pixel);

    Vector camera_plane_normal = v_unitize(v3d(-5, 0, -2));
    Vector camera_loc = v3d(5, 0, 1.5);
    double camera_xy_angle = 0;  // in radians

    square(3, camera_plane_normal, camera_loc, camera_xy_angle);

    ps_print(screen);

    // free the char 2d array
    ps_dealloc(screen);

    return 0;
}


void square(double side, Vector camera_plane_normal, Vector camera_loc, double camera_xy_angle) {
    Pixel fill_char = {.r = FILL_R, .g = FILL_G, .b = FILL_B};

    Vector p1 = v3d(-side, side, 0);
    Vector p2 = v3d(side, -side, 0);
    Vector p3 = v3d(-side, -side, 0);
    Vector p4 = v3d(side, side, 0);

    Vector v1 = project_point(p1, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v2 = project_point(p2, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v3 = project_point(p3, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);
    Vector v4 = project_point(p4, camera_plane_normal, camera_loc, camera_xy_angle, ZOOM_FACTOR);

    // to show the center of the 'screen'.
    // pscreen_putpixel(screen, 0, 0, fill_char);

    ps_putpixel(screen, v1.vals[0], v1.vals[1], fill_char);
    ps_putpixel(screen, v2.vals[0], v2.vals[1], fill_char);
    ps_putpixel(screen, v3.vals[0], v3.vals[1], fill_char);
    ps_putpixel(screen, v4.vals[0], v4.vals[1], fill_char);
}


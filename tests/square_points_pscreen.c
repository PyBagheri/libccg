#include <cvector/cvector.h>
#include <screen/pixelscreen.h>
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

#define PI 3.141592


Vector project_point(Vector p, Vector camera_loc, double camera_xy_angle);
void square(double side, Vector camera_loc, double camera_xy_angle);

PixelScreen screen;


int main(void) {
    // prepare the screen
    Pixel empty_fill_char = { .r=EMPTY_FILL_R, .g=EMPTY_FILL_G, .b=EMPTY_FILL_B };
    screen = pscreen_init(WIDTH, HEIGHT, empty_fill_char);

    Vector camera_loc = v3d(5, 0, 5);
    double camera_xy_angle = 0;  // in radians
    square(3, camera_loc, camera_xy_angle);

    pscreen_print(screen);

    // free the char 2d array
    pscreen_dealloc(screen);

    return 0;
}


void square(double side, Vector camera_loc, double camera_xy_angle) {
    Pixel fill_char = { .r=FILL_R, .g=FILL_G, .b=FILL_B };

    Vector p1 = v3d(-side, side, 0);
    Vector p2 = v3d(side, -side, 0);
    Vector p3 = v3d(-side, -side, 0);
    Vector p4 = v3d(side, side, 0);

    Vector v1 = project_point(p1, camera_loc, camera_xy_angle);
    Vector v2 = project_point(p2, camera_loc, camera_xy_angle);
    Vector v3 = project_point(p3, camera_loc, camera_xy_angle);
    Vector v4 = project_point(p4, camera_loc, camera_xy_angle);

    // to show the center of the 'screen'.
    pscreen_putpixel(screen, 0, 0, fill_char);


    pscreen_putpixel(screen, v1.vals[0], v1.vals[1], fill_char);
    pscreen_putpixel(screen, v2.vals[0], v2.vals[1], fill_char);
    pscreen_putpixel(screen, v3.vals[0], v3.vals[1], fill_char);
    pscreen_putpixel(screen, v4.vals[0], v4.vals[1], fill_char);
}


// camera will always look at the origin. If you want to change
// this behavior, you should change the 'plane_origin' parameter
// to something else (currently it's parallel to 'plane_normal').
Vector project_point(Vector p, Vector camera_loc, double camera_xy_angle) {
    double zoom_factor = 50.0;

    Vector plane_normal = v_neg(v_unitize(camera_loc));
    Vector proj = v_project(p, camera_loc);

    Vector proj_distance_vector = v_diff(camera_loc, proj);
    double zoom_coeff = zoom_factor / v_abs(proj_distance_vector);

    return v_const_prod(v_3d_to_2d(p, plane_normal, camera_loc, camera_xy_angle), zoom_coeff);
}

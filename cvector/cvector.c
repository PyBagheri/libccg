#include <cvector/cvector.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>


Vector vNd(unsigned int dim) {
    num* vals = malloc(sizeof(num) * dim);
    Vector v = { .dim=dim, .vals=vals };

    return v;
}

// 'na' stands for 'no allocate'.
// In this case, the 'vals' will contain
// garbage until it's assigned a pointer
// to the 'num's array.
Vector vNd_na(unsigned int dim) {
    Vector v = { .dim=dim };

    return v;
}

Vector v2d(num x, num y) {
    Vector v = vNd(2);
    v.vals[0] = x;
    v.vals[1] = y;

    return v;
}

Vector v3d(num x, num y, num z) {
    Vector v = vNd(3);
    v.vals[0] = x;
    v.vals[1] = y;
    v.vals[2] = z;

    return v;
}

Vector v_from_array(unsigned int dim, num* arr) {
    Vector v = vNd(dim);
    for (int i = 0; i < dim; i++) {
        v.vals[i] = arr[i];
    }

    return v;
}

// This will just use the pointer to the arr
// as the 'vals' array for the vector. 'na'
// stands for 'no allocate'.
Vector v_from_array_na(unsigned int dim, num* arr) {
    Vector v = vNd_na(dim);
    v.vals = arr;

    return v;
}

Vector v_copy(Vector v) {
    Vector copy = vNd(v.dim);

    for (int i = 0; i < v.dim; i++) {
        copy.vals[i] = v.vals[i];
    }

    return copy;
}

void v_dealloc(Vector v) {
    free(v.vals);
}

num x(Vector v) { return v.vals[0]; }
num y(Vector v) { return v.vals[1]; }
num z(Vector v) { return v.vals[2]; }

Vector v_sum(Vector v1, Vector v2) {
    Vector res = vNd(v1.dim);

    for (int i = 0; i < v1.dim; i++) {
        res.vals[i] = v1.vals[i] + v2.vals[i];
    }

    return res;
}

Vector v_diff(Vector v1, Vector v2) {
    Vector res = vNd(v1.dim);

    for (int i = 0; i < v1.dim; i++) {
        res.vals[i] = v1.vals[i] - v2.vals[i];
    }

    return res;
}

Vector v_neg(Vector v) {
    Vector res = vNd(v.dim);

    for (int i = 0; i < v.dim; i++) {
        res.vals[i] = -v.vals[i];
    }

    return res;
}

Vector v_const_prod(Vector v, num c) {
    Vector res = vNd(v.dim);

    for (int i = 0; i < v.dim; i++) {
        res.vals[i] = c * v.vals[i];
    }

    return res;
}

Vector v_const_div(Vector v, num c) {
    return v_const_prod(v, 1/c);
}

num v_abs(Vector v) {
    num sum = 0;

    for (int i = 0; i < v.dim; i++) {
        sum += pow(v.vals[i], 2.0);
    }

    return sqrt(sum);
}

Vector v_unitize(Vector v) {
    Vector res = v_copy(v);
    num mag = v_abs(v);

    return v_const_div(v, mag);
}

num v_dot(Vector v1, Vector v2) {
    num sum = 0;

    for (int i = 0; i < v1.dim; i++) {
        sum += v1.vals[i] * v2.vals[i];
    }

    return sum;
}

num v_project_value(Vector v1, Vector v2) {
    return v_dot(v1, v2) / v_abs(v2);
}

Vector v_project(Vector v1, Vector v2) {
    Vector unitized = v_unitize(v2);
    return v_const_prod(unitized, v_project_value(v1, v2));
}

Vector v_cross(Vector v1, Vector v2) {
    return v3d(
        v1.vals[1]*v2.vals[2] - v1.vals[2]*v2.vals[1],
        v1.vals[2]*v2.vals[0] - v1.vals[0]*v2.vals[2],
        v1.vals[0]*v2.vals[1] - v1.vals[1]*v2.vals[0]
    );
}


// For non-horizontal planes, 'xy_angle' is the angle of
// the x axis on the plane from the xy-plane of the 3d space.
// For horizontal planes, it's the angle from the +x axis of
// the 3d space. It can be between -pi and pi radians.
//
// The plane normal vector must be toward the inside of
// the plane. This is crucial to not take the -x axis as
// the +x.
Vector v_3d_to_2d(Vector v, Vector plane_normal, Vector plane_origin, num xy_angle) {
    // project v on the plane.
    v = v_diff(v, v_project(v, plane_normal));

    // horizontal here means in the xy-plane.
    Vector horiz_x = v2d(plane_normal.vals[1], -plane_normal.vals[0]);
    Vector horiz_x_unit;
    if (horiz_x.vals[0] == 0.0 && horiz_x.vals[1] == 0.0) {
        horiz_x_unit = v2d(1, 0);
    } else {
        horiz_x_unit = v_unitize(horiz_x);
    }

    Vector x_plus_unit = v3d(cos(xy_angle)*(horiz_x_unit.vals[0]),
                             cos(xy_angle)*(horiz_x_unit.vals[1]),
                             sin(xy_angle));

    Vector y_plus_unit = v_cross(x_plus_unit, plane_normal);

    return v2d(v_project_value(v, x_plus_unit), v_project_value(v, y_plus_unit));
}

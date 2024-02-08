#ifndef CVECTOR_H
#define CVECTOR_H

typedef double num;

typedef struct Vector {
    unsigned int dim;
    num* vals;
} Vector;

Vector vNd(unsigned int dim);

// 'na' stands for 'no allocate'.
// In this case, the 'vals' will contain
// garbage until it's assigned a pointer
// to the 'num's array.
Vector vNd_na(unsigned int dim);

Vector v2d(num x, num y);
Vector v3d(num x, num y, num z);

Vector v_from_array(unsigned int dim, num* arr);

// This will just use the pointer to the arr
// as the 'vals' array for the vector. 'na'
// stands for 'no allocate'.
Vector v_from_array_na(unsigned int dim, num* arr);

void v_dealloc(Vector v);

num x(Vector v);
num y(Vector v);
num z(Vector v);

Vector v_sum(Vector v1, Vector v2);
Vector v_diff(Vector v1, Vector v2);
Vector v_neg(Vector v);
Vector v_const_prod(Vector v, num c);
Vector v_const_div(Vector v, num c);
num v_abs(Vector v);

Vector v_unitize(Vector v);

num v_dot(Vector v1, Vector v2);

num v_project_value(Vector v1, Vector v2);
Vector v_project(Vector v1, Vector v2);

Vector v_cross(Vector v1, Vector v2);

Vector v_project_on_plane(Vector v, Vector plane_normal, Vector plane_origin, num xy_angle);

#endif // CVECTOR_H

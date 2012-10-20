/*
 * vector.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Vector and point handling implementations for use with 
 * OpenGL.
 */

#include "vector.h"

/* Computes the vector sum of two vectors, v1 and v2. Stores the 
   resultant vector in t. */
void vec_sum(const vec_t *v1, const vec_t *v2, vec_t *t) {
    vec_t v;
    v.x = v1->x + v2->x;
    v.y = v1->y + v2->y;
    v.z = v1->z + v2->z;
    *t = v;
}

/* Computes the vector difference of two vectors, v1 and v2. Stores 
   the resultant vector in t. */
void vec_diff(const vec_t *v1, const vec_t *v2, vec_t *t) {
    vec_t v;
    v.x = v1->x - v2->x;
    v.y = v1->y - v2->y;
    v.z = v1->z - v2->z;
    *t = v;
}

/* Multiplies the vector v1 by the scalar a. Stores the resultant 
   vector in t. */
void svec_prod(const vec_t *v1, double a, vec_t *t) {
    vec_t v;
    v.x = v1->x * a;
    v.y = v1->y * a;
    v.z = v1->z * a;
    *t = v;
}

/* Takes the cross product of v1 and v2 (v1 x v2). Stores the result 
   in t. */
void vec_cross(const vec_t *v1, const vec_t *v2, vec_t *t) {
    /* v = v1 x v2
       v = [vx,vy,vz] where,
       vx = v1y * v2z - v1z * v2y
       vy = v1z * v2x - v1x * v2z
       vz = v1x * v2y - v1y * v2x */
    vec_t v;
    v.x = v1->y * v2->z - v1->z * v2->y;
    v.y = v1->z * v2->x - v1->x * v2->z;
    v.z = v1->x * v2->y - v1->y * v2->x;
    *t = v;
}

/* 
 * Computes the dot product of vectors v1 and v2, treating v1 as a row 
 * vector and v2 as a column vector.
 */
GLfloat vec_rcdot(const vec_t *v1, const vec_t *v2) {
    GLfloat sum = 0;
    sum += v1->x * v2->x;
    sum += v1->y * v2->y;
    sum += v1->z * v2->z;
    return sum;
}


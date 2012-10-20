/*
    vector.h
    George Lesica
    CSCI 441
    Vector convenience library header.
*/

#pragma once

#include "GL/glut.h"

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec_t;

void vec_sum(const vec_t *v1, const vec_t *v2, vec_t *t);
void vec_diff(const vec_t *v1, const vec_t *v2, vec_t *t);
void svec_prod(const vec_t *v1, const double a, vec_t *t);
void vec_cross(const vec_t *v1, const vec_t *v2, vec_t *t);
GLfloat vec_rcdot(const vec_t *v1, const vec_t *v2);


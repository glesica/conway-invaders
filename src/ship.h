/*
 * ship.h
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Definitions related to the ship.
 */

#pragma once

#ifdef __APPLE__
    #include "GLUT/glut.h"
#else
    #include "GL/glut.h"
#endif
#include "vector.h"

typedef enum {
    gun,
    dgun
} weap_t;

typedef struct {
    vec_t position;
    weap_t weapon;
    int health;
    int width;
    int length;
} ship_t;

void init_ship(ship_t *s, GLfloat x, GLfloat y);
void move_ship(ship_t *s, const vec_t *dir, const double scale);
void draw_ship(ship_t *s);
void print_ship(ship_t *s);


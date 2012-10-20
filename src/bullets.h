/*
 * bullets.h
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Declarations relating to game weapons.
 */

#pragma once

#include "GL/glut.h"
#include "vector.h"
#include "ship.h"

typedef struct {
    vec_t position;
    vec_t velocity;
    weap_t weapon;
    int active;
} bul_t;

typedef struct {
    bul_t *bullets;
    int count;
    int capacity;
} blist_t;

void init_bullet(bul_t *b, const weap_t w, const vec_t *pos, const vec_t *vel);
void add_bullet(blist_t *bs, const weap_t w, const vec_t *pos, const vec_t *vel);
void move_bullet(bul_t *b, const double scale);
void move_bullets(blist_t *bs, const double scale);
void draw_bullet(bul_t *b);
void draw_bullets(blist_t *bs);
void print_bullet(bul_t *b);


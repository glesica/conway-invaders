/*
 * bullets.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Bullet handling implementations.
 */

#include <stdio.h>
#include <assert.h>
#ifdef __APPLE__
    #include "GLUT/glut.h"
#else
    #include "GL/glut.h"
#endif
#include "bullets.h"
#include "ship.h"
#include "vector.h"
#include "config.h"

void init_bullet(bul_t *b, const weap_t w, const vec_t *pos, const vec_t *vel) {
    /* Set the weapon this bullet came from */
    b->weapon = w;
    /* Initial position of the bullet */
    b->position.x = pos->x;
    b->position.y = pos->y;
    b->position.z = pos->z;
    /* Set the velocity for the bullet */
    b->velocity.x = vel->x;
    b->velocity.y = vel->y;
    b->velocity.z = vel->z;
    /* Set the bullet to active */
    b->active = 1;
}

/* Removes inactive bullets from the list. */
void trim_bullets(blist_t *bs) {
    /* Remove inactive or offscreen bullets */
    int valid_count = 0;
    for (int i = 0; i < bs->count; i++) {
        if (bs->bullets[i].active && bs->bullets[i].position.y < MAX_Y) {
            valid_count += 1;
        }
    }
    bul_t *buf = calloc(valid_count, sizeof(bul_t));
    int j = 0;
    for (int i = 0; i < bs->count; i++) {
        if (bs->bullets[i].active && bs->bullets[i].position.y < MAX_Y) {
            buf[j] = bs->bullets[i];
            j += 1;
        }
    }
    free(bs->bullets);
    bs->bullets = buf;
    bs->count = valid_count;
    // DEBUG
    for (int i = 0; i < bs->count; i++) {
        assert(bs->bullets[i].position.y < MAX_Y);
    }
}

void add_bullet(blist_t *bs, const weap_t w, const vec_t *pos, const vec_t *vel) {
    trim_bullets(bs);
    bs->count += 1;
    bs->bullets = (bul_t *) realloc(bs->bullets, bs->count * sizeof(bul_t));
    init_bullet(&(bs->bullets[bs->count - 1]), w, pos, vel);
}

void move_bullet(bul_t *b, const double scale) {
    vec_t delta;
    svec_prod(&(b->velocity), scale, &delta);
    vec_sum(&(b->position), &delta, &(b->position));
}

void move_bullets(blist_t *bs, const double scale) {
    /* Loop through and move each bullet */
    for (int i = 0; i < bs->count; i++) {
        if (bs->bullets[i].active) {
            move_bullet(&(bs->bullets[i]), scale);
            if (bs->bullets[i].position.y >= MAX_Y || 
                bs->bullets[i].position.x <= MIN_X || 
                bs->bullets[i].position.x >= MAX_X)
            {
                bs->bullets[i].active = 0;
            }
        }
    }
    trim_bullets(bs);
}

void draw_bullet(bul_t *b) {
    /* Set the bullet color */
    GLfloat *prev_color = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    glGetFloatv(GL_CURRENT_COLOR, prev_color);
    switch (b->weapon) {
        case gun:
            glColor3f(GUN_BULLETS_COLOR);
            break;
        case dgun:
            glColor3f(DGUN_BULLETS_COLOR);
            break;
    }
    /* Grab the position and draw */
    // TODO: Make this more flexible
    GLfloat x = b->position.x - 0.5;
    GLfloat y = b->position.y - 0.5;
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 0.5, y + 1.0);
        glVertex2f(x + 1.0, y);
    glEnd();
    /* Restore previous color */
    glColor3fv(prev_color);
    free(prev_color);
}

void draw_bullets(blist_t *bs) {
    for (int i = 0; i < bs->count; i++) {
        if (bs->bullets[i].active) {
            draw_bullet(&(bs->bullets[i]));
        }
    }
}

void print_bullet(bul_t *b) {
    printf("B (%f, %f)\n", b->position.x, b->position.y);
}


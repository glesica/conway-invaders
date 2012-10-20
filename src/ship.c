/*
 * ship.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Ship implementation.
 */

#include <stdio.h>
#include "GL/glut.h"
#include "config.h"
#include "ship.h"
#include "vector.h"

void init_ship(ship_t *s, GLfloat x, GLfloat y) {
    s->position.x = x;
    s->position.y = y;
    s->position.z = 0;
    s->width = SHIP_WIDTH;
    s->length = SHIP_LENGTH;
    s->weapon = SHIP_DEFAULT_WEAPON;
    s->health = SHIP_MAX_HEALTH;
}

/* Move the given ship in the direction given by the vector dir. This will
 * normally be a unit vector, with signs set accordingly to indicate "left or
 * right", etc. The movement will be scaled using scale, set this to 1 if no
 * scaling is needed and the ship position can be updated using dir along. */
void move_ship(ship_t *s, const vec_t *dir, const double scale) {
    vec_t vel;
    svec_prod(dir, scale, &vel);
    /* For now we can only move along the x axis, but we leave
     * open the possibility of changing that later by using full
     * vectors for the position and velocity. */
    GLfloat newx = s->position.x + vel.x;
    if (newx >= MAX_X) {
        s->position.x = MAX_X - 0.1;
    } else if (newx <= MIN_X) {
        s->position.x = MIN_X + 0.1;
    } else {
        s->position.x = newx;
    }
}

void draw_ship(ship_t *s) {
    /* Save the current color */
    GLfloat *prev_color = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    glGetFloatv(GL_CURRENT_COLOR, prev_color);
    /* Set the ship color */
    glColor3f(SHIP_COLOR);
    /* Get the position info */
    GLfloat x1 = s->position.x - (s->width / 2.0);
    GLfloat y1 = s->position.y;
    GLfloat w = s->width * 1.0;
    GLfloat l = s->length * 1.0;
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x1 + 0.5 * w, y1 + l);
        glVertex2f(x1 + w, y1);
    glEnd();
    /* Restore the old color */
    glColor3fv(prev_color);
    free(prev_color);
}

void print_ship(ship_t *s) {
    printf("SHIP x: %f y: %f z: %f health: %d\n", s->position.x, s->position.y, s->position.z, s->health);
}


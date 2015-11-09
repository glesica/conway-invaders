/*
 * lfdraw.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Functions to handle drawing the Conway simulation.
 */

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
    #include "GLUT/glut.h"
#else
    #include "GL/glut.h"
#endif
#include "vector.h"
#include "lfdraw.h"
#include "config.h"

/*
 * Draws the current game at the given location.
 */
void draw_lifeform(const lf_t *lf, const vec_t *ul, const vec_t *lr) {
    /* Save the current color */
    GLfloat *prev_color = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    glGetFloatv(GL_CURRENT_COLOR, prev_color);

    GLfloat width = abs(lr->x - ul->x);
    GLfloat height = abs(lr->y - ul->y);

    GLfloat cell_width = width / lf->width;
    GLfloat cell_height = height / lf->height;

    for (int row = 0; row < lf->height; row++) {
        for (int col = 0; col < lf->width; col++) {
            int cell_i = lf->width * row + col;
            int cell_v = lf->board[cell_i];
            if (cell_v > 0) {
                GLfloat x1 = col * cell_width;
                GLfloat y1 = ul->y - (row * cell_height);
                GLfloat x2 = (col + 1) * cell_width;
                GLfloat y2 = ul->y - ((row + 1) * cell_height);
                glColor3f(LIFEFORM_COLOR);
                glBegin(GL_QUADS);
                    glVertex2f(x1, y1);
                    glVertex2f(x2, y1);
                    glVertex2f(x2, y2);
                    glVertex2f(x1, y2);
                glEnd();
            }
        }
    }
    /* Restore the old color */
    glColor3fv(prev_color);
    free(prev_color);
}


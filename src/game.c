/*
 * game.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Implementation of game control functions.
 */

#include <stdio.h>
#ifdef __APPLE__
    #include "GLUT/glut.h"
#else
    #include "GL/glut.h"
#endif
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lifeform.h"
#include "bullets.h"
#include "config.h"

/* Updates the state of game play. This includes interactions between bullets,
 * the life form and the environment. */
void update_game(lf_t *lf, const blist_t *bs, int *score) {
    for (int i = 0; i < bs->count; i++) {
        /* Position of bullet */
        GLfloat bx = bs->bullets[i].position.x;
        GLfloat by = bs->bullets[i].position.y;
        /* Skip bullets outside active area */
        if (by >= MAX_Y) {
            continue;
        }
        /* Game board dimensions */
        GLfloat brd_w = MAX_X - MIN_X;
        GLfloat brd_h = MAX_Y - MIN_Y;
        /* Cell dimensions */
        GLfloat cell_w = brd_w / lf->width;
        GLfloat cell_h = brd_h / lf->height;
        //DEBUG
        assert(by >= 0.0);
        assert(by <= brd_h);
        assert(bx >= 0.0);
        assert(bx <= brd_w);
        /* Get the cell index from all that junk */
        int col = (int) (bx / cell_w);
        int row = (int) ((brd_h - by) / cell_h);
        int cell_i = CELL_INDEX(lf, row, col);
        // DEBUG
        assert(cell_i >= 0);
        assert(cell_i < LF_SIZE(lf));
        /* Adjust the cell accordingly */
        if (lf->board[cell_i] == 1) {
            /* Bullet hit a live cell, kill it and drop the bullet */
            toggle_cell(lf, row, col);
            bs->bullets[i].active = 0;
            /* Increment the score */
            *score += 1;
        }
    }
}

/* Check to see if the ship has collided with the life form. */
int ship_collision(ship_t *s, lf_t *lf) {
    GLfloat brd_w = MAX_X - MIN_X;
    GLfloat brd_h = MAX_Y - MIN_Y;
    GLfloat cell_w = brd_w / lf->width;
    GLfloat cell_h = brd_h / lf->height;
    int col = (int) (s->position.x / cell_w);
    int row = (int) ((brd_h - s->position.y) / cell_h);
    int cell_i = CELL_INDEX(lf, row, col);
    /* DEBUG */
    assert(cell_i >= 0);
    assert(cell_i < LF_SIZE(lf));
    if (lf->board[cell_i] == 1) {
        return 1;
    } else {
        return 0;
    }
}

void show_help() {
    char *movement = "Move with the arrow keys or mouse\0";
    char *mouse = "Press 'm' to toggle mouse movement\0";
    char *gun = "Fire the main gun with 'z'\0";
    char *dgun = "Fire the super gun with 'x'\0";
    char *pause = "Press 'p' to pause/unpause the game\0";
    char *help = "Press 'h' to show/hide this help\0";
    char *quit = "Press 'q' to quit the game\0";

    glPushMatrix();
        glTranslatef(20.0, 60.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(movement); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, movement[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 55.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(mouse); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, mouse[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 50.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(gun); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, gun[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 45.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(dgun); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, dgun[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 40.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(help); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, help[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 35.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(quit); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, quit[i]);
        }
    glPopMatrix();
    glPushMatrix();
        glTranslatef(20.0, 30.0, 0.0);
        glScalef(0.02, 0.02, 0.0);
        for (int i = 0; i < strlen(pause); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, pause[i]);
        }
    glPopMatrix();
}

void draw_score(int *score) {
    char s[32];
    sprintf(s, "Score: %d", *score);
    glPushMatrix();
        glTranslatef(0.0, 98.0, 0.0);
        glScalef(0.03, 0.03, 1.0);
        for (int i = 0; i < strlen(s); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}

void draw_dgun_ammo(int *ammo) {
    char s[64];
    sprintf(s, "Ammo: %d", *ammo);
    glPushMatrix();
        glTranslatef(70, 98.0, 0.0);
        glScalef(0.03, 0.03, 1.0);
        for (int i = 0; i < strlen(s); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}

void draw_level(int *level) {
    char s[64];
    sprintf(s, "Level: %d", *level);
    glPushMatrix();
        glTranslatef(0.0, 94.0, 0.0);
        glScalef(0.03, 0.03, 1.0);
        for (int i = 0; i < strlen(s); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}

void game_over() {
    char *s = "GAME OVER\0";
    glPushMatrix();
        glTranslatef(10.0, 50.0, 0.0);
        glScalef(0.1, 0.1, 1.0);
        for (int i = 0; i < strlen(s); i++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
    glPopMatrix();
}


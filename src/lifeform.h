/*
 * lifeform.h
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Declarations for the Conway life form.
 */

#pragma once

#define CELL_INDEX(lf,r,c) lf->width * r + c
#define LF_SIZE(lf) lf->width * lf->height

typedef struct {
    int width;
    int height;
    int *board;
} lf_t;

void init_lifeform(lf_t *lf, int w, int h);
void toggle_cell(lf_t *lf, int row, int col);
void kill_cell(lf_t *lf, const int row, const int col);
void respawn_cell(lf_t *lf, const int row, const int col);
void random_spawn(lf_t *lf, const int n);
void advance_lifeform(lf_t *lf);
void print_board(const lf_t *lf);
    

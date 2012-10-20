/*
 * lifeform.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Implementation of Conway's Game of Life.
 */

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "lifeform.h"
#include "config.h"

void init_lifeform(lf_t *lf, const int w, const int h) {
    /* Set the width and height of the lf */
    lf->width = w;
    lf->height = h;
    /* Add a board of the correct size and zero it */
    int lf_size = LF_SIZE(lf);
    lf->board = (int *) calloc(lf_size, sizeof(int));
}

/* Toggle the given cell. Live cells become dead, dead cells become live. */
void toggle_cell(lf_t *lf, const int row, const int col) {
    int w = lf->width;
    int h = lf->height;
    /* Validity check */
    if (row < 0 || row >= h || col < 0 || col >= w) {
        return;
    }
    /* Toggle the cell at (row, col) in the lf */
    int cell_i = CELL_INDEX(lf, row, col);
    lf->board[cell_i] = abs(lf->board[cell_i] - 1);
}

/* Kill the specified cell. Take no action if it is already dead. Fails
 * silently if the row and/or column are invalid. */
void kill_cell(lf_t *lf, const int row, const int col) {
    int w = lf->width;
    int h = lf->height;
    /* Validity check */
    if (row < 0 || row >= h || col < 0 || col >= w) {
        return;
    }
    int cell_i = CELL_INDEX(lf, row, col);
    lf->board[cell_i] = 0;
}

/* Bring the specified cell to life. Take no action if it is already alive.
 * Fails silently if the row and/or column are invalid. */
void respawn_cell(lf_t *lf, const int row, const int col) {
    int w = lf->width;
    int h = lf->height;
    /* Validity check */
    if (row < 0 || row >= h || col < 0 || col >= w) {
        return;
    }
    int cell_i = CELL_INDEX(lf, row, col);
    lf->board[cell_i] = LF_CELL_ALIVE;
}

/* Randomly spawns n clusters of life form cells. */
void random_spawn(lf_t *lf, const int n) {
    int row, col;
    for (int i = 0; i < n; i++) {
        row = rand() % MAX_SPAWN_ROW;
        col = rand() % (lf->width);
        /* DEBUG */
        assert(row <= MAX_SPAWN_ROW);
        /* Respawn a little pattern of cells around the chosen cell */
        // TODO: Be nice if we had some saved patterns...
        respawn_cell(lf, row, col);
        respawn_cell(lf, row + 1, col + 1);
        respawn_cell(lf, row - 1, col - 1);
        respawn_cell(lf, row + 1, col - 1);
        respawn_cell(lf, row - 1, col + 1);
    }
}

void advance_lifeform(lf_t *lf) {
    /* Find the total size of the lf */
    int lf_size = LF_SIZE(lf);
    /* Create a fake board to update */
    int *buffer = (int *) calloc(lf_size, sizeof(int));
    /* Count live neighbors for all cells */
    for (int cell_i = 0; cell_i < lf_size; cell_i++) {
        /* Find the row and column for convenience */
        int row = cell_i / lf->width;
        int col = cell_i % lf->width;
        /* Start the living neighbors count for this cell */
        int alive_n = 0;
        /* Check N, NW, NE */
        if (row > 0) {
            alive_n += lf->board[cell_i - lf->width];
            if (col > 0) {
                alive_n += lf->board[cell_i - lf->width - 1];
            }
            if (col < lf->width - 1) {
                alive_n += lf->board[cell_i - lf->width + 1];
            }
        }
        /* Check S, SW, SE */
        if (row < lf->height - 1) {
            alive_n += lf->board[cell_i + lf->width];
            if (col > 0) {
                alive_n += lf->board[cell_i + lf->width - 1];
            }
            if (col < lf->width - 1) {
                alive_n += lf->board[cell_i + lf->width + 1];
            }
        }
        /* Check W, E */
        if (col > 0) {
            alive_n += lf->board[cell_i - 1];
        }
        if (col < lf->width - 1) {
            alive_n += lf->board[cell_i + 1];
        }
        /* Now we determine the fate of the current cell... */
        int cell = lf->board[cell_i];
        if (cell == 1) {
            /* Cell is alive, it might die now. So sad. */
            if (alive_n < LF_LIVE_MIN || alive_n > LF_LIVE_MAX) {
                buffer[cell_i] = 0;
            } else {
                buffer[cell_i] = 1;
            }
        } else {
            /* Cell is dead, but there's still hope! */
            if (alive_n == LF_RESPAWN_N) {
                buffer[cell_i] = 1;
            }
        }
    }
    /* Buffer now contains the new version of the board */
    free(lf->board);
    lf->board = buffer;
}

/* 
 * Pretty-prints (sort of) a lf board to stdout. This is 
 * primarily for debugging.
 */
void print_board(const lf_t *lf) {
    int brd_width = lf->width;
    int brd_height = lf->height;
    int lf_size = brd_width * brd_height;
    for (int i = 0; i < lf_size; i++) {
        if (i % brd_width == 0) {
            printf("\n");
        }
        printf(" %d", lf->board[i]);
    }
    printf("\n");
}


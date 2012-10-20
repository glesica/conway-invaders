/*
 * game.h
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Overall game related declarations.
 */

#pragma once

#include "lifeform.h"
#include "bullets.h"
#include "ship.h"

void update_game(lf_t *lf, const blist_t *bs, int *score);
int ship_collision(ship_t *s, lf_t *lf);
void show_help();
void draw_score(int *score);
void draw_dgun_ammo(int *ammo);
void draw_level(int *level);
void game_over();


/*
 * config.h
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Configuration definitions all in one place.
 */

#pragma once

/* Enemy crap */
#define LF_CELL_ALIVE 1
#define LF_CELL_DEAD 0
#define LF_LIVE_MAX 5
#define LF_LIVE_MIN 1
#define LF_RESPAWN_N 3
#define LIFEFORM_COLOR 0.0, 1.0, 0.0
#define SPAWN_COUNT 1
#define SPAWN_DELTA 10.0
#define LF_ROWS 40
#define LF_COLUMNS 40

/* Ship crap */
#define SHIP_COLOR 0.5, 0.5, 0.8
#define SHIP_DEFAULT_WEAPON gun
#define SHIP_LENGTH 4
#define SHIP_MAX_HEALTH 10
#define SHIP_START_X 50
#define SHIP_WIDTH 4

/* Weapons crap */
#define DGUN_BULLETS_COLOR 1.0, 0.0, 0.0
#define GUN_BULLETS_COLOR 1.0, 1.0, 0.0
#define DGUN_SHOTS_INITIAL 25
#define DGUN_SHOTS_DELTA 5
#define DGUN_SHOTS_ANGLE 0.15
#define DGUN_DELTA 5.0

/* Technical crap */
#define DIFFICULTY_DELTA 60.0
#define DIFFICULTY_RATIO 99.0 / 100.0
#define GAME_FPS 60.0
#define MAX_X 100.0
#define MAX_Y 100.0
#define MIN_X 0.0
#define MIN_Y 0.0
#define MAX_SPAWN_ROW 35
#define MOVEMENT_SCALE 30
#define MOVEMENT_SCALE_BULLET 60


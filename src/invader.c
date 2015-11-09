/*
 * invader.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Main application file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#ifdef __APPLE__
    #include "GLUT/glut.h"
#else
    #include "GL/glut.h"
#endif
#include "config.h"
#include "lfdraw.h"
#include "lifeform.h"
#include "ship.h"
#include "util.h"
#include "vector.h"
#include "bullets.h"
#include "game.h"

/* Running */
static int running = 1;
static int gameover = 0;
static int help = 1;

/* Score */
static int score = 0;

/* Mouse control */
static int use_mouse = 0;

/* This is used to ramp up the difficulty as
 * time goes on. */
static double difficulty_previous;
static double difficulty_delta = DIFFICULTY_DELTA;

/* Current timestamp shared by various deltas. */
static double time_current;

/* Frame rate previous timestamp and delta for the program as a whole. */
static double fps_previous;
static double fps_delta = 1.0 / GAME_FPS;

/* Time delta between GOL simulation updates. The update rate can be adjusted
 * in-game to change the difficulty. */
static double lf_previous;
static double lf_delta = 1.5;

/* Time delta between life form expansions. This can get smaller to make the
 * game harder. */
static double spawn_previous;
static double spawn_delta = SPAWN_DELTA;
static int spawn_count = SPAWN_COUNT;
static int level = 1;

/* Game of life simulation. */
static lf_t lifeform;
static vec_t ul = {MIN_X, MAX_Y, 0.0};
static vec_t lr = {MAX_X, MIN_Y, 0.0};
 
/* Ship */
static ship_t ship;
static vec_t ship_vel = {1, 0, 0};
static double ship_delta;

/* Bullets and such */
static blist_t bullets;
static double bullet_delta;
static vec_t bullet_vel = {0.0, 1.0, 0.0};
static int dgun_shots = DGUN_SHOTS_INITIAL;
static int dgun_shots_delta = DGUN_SHOTS_DELTA;
static double dgun_previous;
static double dgun_delta = DGUN_DELTA;

void teardown() {
    free(lifeform.board);
    free(bullets.bullets);
}

static int win_x() {return glutGet(GLUT_WINDOW_X);}

void game_tick() {
    /* Short circuit */
    if (! running) {
        return;
    }
    /* Move the ship around */
    move_ship(&ship, &ship_vel, ship_delta);
    /* See if ship collided with the life from */
    if (ship_collision(&ship, &lifeform)) {
        gameover = 1;
        running = 0;
    }
    /* Update bullet positions */
    move_bullets(&bullets, bullet_delta);
    /* Check to see if any aliens died */
    update_game(&lifeform, &bullets, &score);
    /* Advance the GOL simulation */
    if ((time_current - lf_previous) > lf_delta) {
        lf_previous = time_current;
        advance_lifeform(&lifeform);
    }
    /* Spawn new monster dudes */
    if ((time_current - spawn_previous) > spawn_delta) {
        spawn_previous = time_current;
        random_spawn(&lifeform, spawn_count);
    }
    /* Increase difficulty. */
    if ((time_current - difficulty_previous) > difficulty_delta) {
        difficulty_previous = time_current;
        spawn_delta *= (DIFFICULTY_RATIO);
        spawn_count += 1;
        level += 1;
    }
    /* Award new bullets. */
    if ((time_current - dgun_previous) > dgun_delta) {
        dgun_previous = time_current;
        dgun_shots += dgun_shots_delta;
    }
}

void display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    draw_lifeform(&lifeform, &ul, &lr);
    draw_bullets(&bullets);
    draw_ship(&ship);
    draw_score(&score);
    draw_dgun_ammo(&dgun_shots);
    draw_level(&level);

    if (help) {
        show_help();
    }

    if (gameover) {
        game_over();
    }

    glutSwapBuffers();
}

void idle() {
    time_current = current_time();
    if ((time_current - fps_previous) > fps_delta) {
        fps_previous = time_current;
        game_tick();
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    vec_t lt = {-DGUN_SHOTS_ANGLE, bullet_vel.y, 0};
    vec_t lmt = {-DGUN_SHOTS_ANGLE + 0.075, bullet_vel.y, 0};
    vec_t rt = {DGUN_SHOTS_ANGLE, bullet_vel.y, 0};
    vec_t rmt = {DGUN_SHOTS_ANGLE - 0.075, bullet_vel.y, 0};
    switch (key) {
        // Quite
        case 'q':
            exit(0);
            break;
        // Pause
        case 'p':
            running = !running;
            break;
        // Show help
        case 'h':
            help = !help;
            break;
        case 'm':
            use_mouse = !use_mouse;
            break;
        // Fire gun
        case 'z':
            add_bullet(&bullets, gun, &(ship.position), &bullet_vel);
            break;
        // Fire dgun (special weapon)
        case 'x':
            if (dgun_shots > 0) {
                dgun_shots -= 1;
                add_bullet(&bullets, dgun, &(ship.position), &lt);
                add_bullet(&bullets, dgun, &(ship.position), &lmt);
                add_bullet(&bullets, dgun, &(ship.position), &rt);
                add_bullet(&bullets, dgun, &(ship.position), &rmt);
                add_bullet(&bullets, dgun, &(ship.position), &bullet_vel);
            }
            break;
    }
}

void special(int key, int x, int y) {
    if (! use_mouse) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                ship_vel.x = abs(ship_vel.x);
                break;
            case GLUT_KEY_LEFT:
                ship_vel.x = - abs(ship_vel.x);
                break;
        }
    }
}

void mouse(int button, int state, int x, int y) {
    
}

void passive_motion(int x, int y) {
    /* Ugly magic numbers here because I didn't have time to make the window size and such flexible. */
    if (x - win_x() <= 0 || x - win_x() >= 1000) {
        return;
    }
    if (use_mouse) {
        if (x / 10.0 > ship.position.x) {
            ship_vel.x = abs(ship_vel.x);
        } else {
            ship_vel.x = - abs(ship_vel.x);
        }
    }
}

void set_projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat l = -5.0;
    GLfloat r = 105.0;
    GLfloat b = -5.0;
    GLfloat t = 105.0;
    GLfloat n = -1.0;
    GLfloat f = 1.0;
    glOrtho(l, r, b, t, n, f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    /* Create a new gol game board */
    init_lifeform(&lifeform, LF_COLUMNS, LF_ROWS);

    /* Create the ship */
    init_ship(&ship, SHIP_START_X, 0.1);
    ship_delta = fps_delta * MOVEMENT_SCALE;

    /* Set up the bullet handling */
    bullet_delta = fps_delta * MOVEMENT_SCALE_BULLET;

    /* Set up the graphics crap */
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Conway's Game of Death");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(passive_motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    /* Get the current time */
    fps_previous = current_time();
    lf_previous = fps_previous;
    spawn_previous = fps_previous;
    difficulty_previous = fps_previous;
    dgun_previous = fps_previous;
    
    /* Reset the PRNG */
    srand(current_time());

    /* Display some graphics and shit */
    set_projection();
    glutMainLoop();

    /* Another successful day at the bit factory */
    teardown();
    return 0;
}


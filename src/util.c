/*
 * util.c
 * George Lesica
 * CSCI 441 - FA 2012
 * Project 1 - Arcade Game
 * Utility type and function implementations.
 */

#include <stdlib.h>
#include "sys/time.h"

/*
 * Returns the current epoch-style time in seconds.
 */
double current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec + t.tv_usec * 1e-6);
}


#ifndef UTIL_H
#define UTIL_H

#include "game.h"

typedef enum input_key{
    INPUT_KEY_INVALID = -1,
    INPUT_KEY_UP = 0,
    INPUT_KEY_DOWN = 1,
    INPUT_KEY_LEFT = 2,
    INPUT_KEY_RIGHT = 3,
    INPUT_KEY_SUBMIT = 4
} input_key_t;

void goto_xy(const size_t x, const size_t y);

input_key_t key_control(void);

#endif /* UTIL_H */

#ifndef UTIL_H
#define UTIL_H

#include "game.h"

typedef enum input_key{
    INPUT_KEY_INVALID = -1,
    INPUT_KEY_UP = 0,
    INPUT_KEY_DOWN = 1,
    INPUT_KEY_LEFT = 2,
    INPUT_KEY_RIGHT = 3,
    INPUT_KEY_PAUSE = 4,
    INPUT_KEY_SUBMIT = 5
} input_key_t;

enum color {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE
};

void goto_xy_print(const size_t x, const size_t y, const char* str, ...);

input_key_t key_control(void);

void set_color(const int fore_ground, const int back_ground);

direction_t control_direction(const input_key_t input);

void set_direction(direction_t* direction, const input_key_t input);

#endif /* UTIL_H */

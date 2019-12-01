#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>

#define MAP_HEIGHT (23)
#define MAP_WITDH (56)

typedef enum menu {
    MENU_INVALID = -1,
    MENU_START = 0,
    MENU_GAME_INFO = 1,
    MENU_EXIT = 2
} menu_t;

typedef enum element {
    ELEMENT_EMPTY = 0,
    ELEMENT_SNAKE_BODY = 79,
    ELEMENT_SNAKE_HEAD = 64,
    ELEMENT_FOOD = 42
} element_t;

void init(void);

void draw_title(void);

menu_t draw_menu(void);

void draw_info(void);

void draw_map(void);

void set_color(const int fore_ground, const int back_ground);

#endif /* GAME_H */

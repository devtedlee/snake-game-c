#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <process.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>
#include <time.h>

#define MAP_HEIGHT (23)
#define MAP_WIDTH (46)
#define MAP_X (1)
#define MAP_Y (1)
#define ITEM_X (MAP_X + 1)
#define ITEM_Y (MAP_Y + 1)

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

typedef enum direction {
    NORTH = 0,
    SOUTH = 1,
    WEST = 2,
    EAST = 3
} direction_t;

typedef struct snake {
    int x;
    int y;
} snake_t;

typedef enum game_status {
    GAME_OVER = 0,
    GAME_RESUME = 1
} game_status_t;

void init(void);

void draw_title(void);

menu_t draw_menu(void);

void draw_info(void);

void reset(void);

void draw_map(void);

game_status_t move(const direction_t direction, size_t* game_speed_millie_p);

void set_element(const element_t element);

#endif /* GAME_H */

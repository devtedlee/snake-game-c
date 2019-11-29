#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>

typedef enum menu{
    MENU_INVALID = -1,
    MENU_START = 0,
    MENU_GAME_INFO = 1,
    MENU_EXIT = 2
} menu_t;

void init(void);

void title_draw(void);

menu_t menu_draw(void);

void info_draw(void);

#endif /* GAME_H */

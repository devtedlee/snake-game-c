#include "util.h"

void goto_xy(const size_t x, const size_t y)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;

    SetConsoleCursorPosition(console_handle, pos);
}

input_key_t key_control(void)
{
    char pressed_key = _getch();

    switch (pressed_key)
    {
    case 'w':
        /* intentional fallthrough */
    case 'W':
        return INPUT_KEY_UP;

    case 's':
        /* intentional fallthrough */
    case 'S':
        return INPUT_KEY_DOWN;

    case 'a':
        /* intentional fallthrough */
    case 'A':
        return INPUT_KEY_LEFT;

    case 'd':
        /* intentional fallthrough */
    case 'D':
        return INPUT_KEY_RIGHT;

    case ' ':
        return INPUT_KEY_SUBMIT;
    
    default:
        return INPUT_KEY_INVALID;
    }
}

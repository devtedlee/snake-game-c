#include "util.h"

void goto_xy_print(const size_t x, const size_t y, const char* str, ...)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    va_list list;
    size_t count = 0;
    char* str_copy = (char*)str;

    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;

    SetConsoleCursorPosition(console_handle, pos);

    while (*str_copy != '\0') {
        if (*str_copy == '%') {
            ++count;
        }
        ++str_copy;
    }

    str_copy = (char*)str;
    va_start(list, count);
    while (*str_copy != '\0') {
        char print = *str_copy;
        if (*str_copy == '%') {
            ++str_copy;
            print = va_arg(list, char);
        }

        putchar(print);
        ++str_copy;
    }
    va_end(list);
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

    case 'p':
        /* intentional fallthrough */
    case 'P':
        return INPUT_KEY_PAUSE;

    case ' ':
        return INPUT_KEY_SUBMIT;
    
    default:
        return INPUT_KEY_INVALID;
    }
}

void set_color(const int fore_ground, const int back_ground)
{
    int code = fore_ground + back_ground * 16;
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, code);
}

void set_direction(direction_t* direction, const input_key_t input) {
    if ((*direction == NORTH && input != INPUT_KEY_DOWN)
        || (*direction == SOUTH && input != INPUT_KEY_UP)
        || (*direction == WEST && input != INPUT_KEY_RIGHT)
        || (*direction == EAST && input != INPUT_KEY_LEFT))
    {
        *direction = (direction_t)input;
    }
}

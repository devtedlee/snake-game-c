#include "game.h"
#include "util.h"

void init(void)
{
    HANDLE console_handle;
    CONSOLE_CURSOR_INFO console_cursor;

    system("mode con cols=56 lines=23 | title SNAKE GAME");

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor.bVisible = 0;
    console_cursor.dwSize = 1;
    SetConsoleCursorInfo(console_handle, &console_cursor);
}

void title_draw(void)
{
    printf("\n\n\n\n");
    printf("         ###    #   #     #     #  #   #####     \n");
    printf("        #       ##  #    # #    # #    #         \n");
    printf("        ####    # # #   #####   ##     #####     \n");
    printf("            #   #  ##   #   #   # #    #         \n");
    printf("        ####    #   #   #   #   #  #   #####     \n");
}

menu_t menu_draw(void)
{
    size_t x = 24;
    size_t y = 12;

    goto_xy(x - 2, y);
    printf("> GAME START");

    goto_xy(x, y + 1);
    printf("GAME INFO");

    goto_xy(x, y + 2);
    printf("   EXIT   ");

    goto_xy(x, y);

    while (1) {
        input_key_t entered_key = key_control();

        switch (entered_key)
        {
        case INPUT_KEY_UP:
            if (y > 12) {
                goto_xy(x - 2, y);
                printf(" ");
                goto_xy(x - 2, --y);
                printf(">");
            }
            break;
        
        case INPUT_KEY_DOWN:
            if (y < 14) {
                goto_xy(x - 2, y);
                printf(" ");
                goto_xy(x - 2, ++y);
                printf(">");
            }
            break;

        case INPUT_KEY_SUBMIT:
            return y - 12;
        
        default:
            continue;
        }
    }
}

void info_draw(void)
{
    system("cls");
    printf("\n\n");
    printf("                    [ Interface ]\n\n");
    printf("                  MOVE: W, A, S, D \n");
    printf("                  SELECT: SPACEBAR \n\n\n\n\n\n\n");
    printf("                  DEVELOPER: tedlee\n\n");
    printf("  When you click SPACEBAR, you can go to main page.");

    while (1) {
        if (key_control() == INPUT_KEY_SUBMIT) {
            break;
        }
    }
}

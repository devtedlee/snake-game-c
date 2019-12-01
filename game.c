#include "game.h"
#include "util.h"

static element_t s_map[MAP_HEIGHT][MAP_WITDH] = { { 0, } };

void init(void)
{
    HANDLE console_handle;
    CONSOLE_CURSOR_INFO console_cursor;

    system("mode con cols=56 lines=27 | title SNAKE GAME");

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor.bVisible = 0;
    console_cursor.dwSize = 1;
    SetConsoleCursorInfo(console_handle, &console_cursor);

    s_map[12][23] = ELEMENT_SNAKE_HEAD;
}

void draw_title(void)
{
    printf("\n\n\n\n");
    printf("         ###    #   #     #     #  #   #####     \n");
    printf("        #       ##  #    # #    # #    #         \n");
    printf("        ####    # # #   #####   ##     #####     \n");
    printf("            #   #  ##   #   #   # #    #         \n");
    printf("        ####    #   #   #   #   #  #   #####     \n");
}

menu_t draw_menu(void)
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

void draw_info(void)
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

void draw_map(void)
{
    static int s_head_color = 0;
    size_t y;
    size_t x;

    system("cls");
    
    set_color(COLOR_WHITE, COLOR_WHITE);
    printf("--------------------------------------------------------");

    for (y = 0; y < MAP_HEIGHT; ++y) {
        for (x = 0; x < MAP_WITDH; ++x) {
            switch (s_map[y][x])
            {
            case ELEMENT_EMPTY:
                set_color(COLOR_BLACK, COLOR_BLACK);
                printf(" ");
                continue;
            case ELEMENT_SNAKE_BODY:
                set_color(COLOR_GREEN, COLOR_BLACK);
                break;
            case ELEMENT_SNAKE_HEAD:
                if (s_head_color == 0) {
                    s_head_color = 1;
                    set_color(COLOR_RED, COLOR_BLACK);
                } else {
                    s_head_color = 0;
                    set_color(COLOR_LIGHT_RED, COLOR_BLACK);
                }
                break;
            case ELEMENT_FOOD:
                set_color(COLOR_YELLOW, COLOR_BLACK);
                break;
            default:
                continue;
            }

            printf("%c", s_map[y][x]);
        }
        printf("\n");
    }
    set_color(COLOR_WHITE, COLOR_WHITE);
    printf("--------------------------------------------------------");
    set_color(COLOR_WHITE, COLOR_BLACK);
    printf("                                     Remaining Time:    ");

    Sleep(3000);
}

void set_color(const int fore_ground, const int back_ground)
{
    int code = fore_ground + back_ground * 16;
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, code);
}

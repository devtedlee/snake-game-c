#include "game.h"
#include "util.h"

static element_t s_map[MAP_HEIGHT][MAP_WITDH] = { { 0, } };
static int s_head_x = 23;
static int s_head_y = 12;
static int s_tail_length = 0;

void init(void)
{
    HANDLE console_handle;
    CONSOLE_CURSOR_INFO console_cursor;

    system("mode con cols=66 lines=30 | title SNAKE GAME");

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor.bVisible = 0;
    console_cursor.dwSize = 1;
    SetConsoleCursorInfo(console_handle, &console_cursor);

    s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_HEAD;
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
        Sleep(100);
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
    size_t x;
    size_t y;

    system("cls");

    set_color(COLOR_WHITE, COLOR_WHITE);
    for(x = MAP_X; x < MAP_WITDH + MAP_X + 1; ++x){
        goto_xy(x, MAP_Y);
        printf("O");
        goto_xy(x, MAP_HEIGHT + MAP_Y + 1);
        printf("O");
    }
    
    for(y = MAP_Y; y < MAP_HEIGHT + MAP_Y + 1; ++y){
        goto_xy(MAP_X, y);
        printf("O");
        goto_xy(MAP_WITDH + MAP_X + 1, y);
        printf("O");
    }

    for (y = 0; y < MAP_HEIGHT; ++y) {
        for (x = 0; x < MAP_WITDH; ++x) {
            switch (s_map[y][x])
            {
            case ELEMENT_EMPTY:
                set_color(COLOR_BLACK, COLOR_BLACK);
                goto_xy(x + ITEM_X, y + ITEM_Y);
                printf(" ");
                continue;
            case ELEMENT_SNAKE_BODY:
                set_color(COLOR_GREEN, COLOR_BLACK);
                break;
            case ELEMENT_SNAKE_HEAD:
                set_color(COLOR_RED, COLOR_BLACK);
                break;
            case ELEMENT_FOOD:
                set_color(COLOR_YELLOW, COLOR_BLACK);
                break;
            default:
                continue;
            }

            goto_xy(x + ITEM_X, y + ITEM_Y);
            printf("%c", s_map[y][x]);
        }
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
    goto_xy(MAP_X, MAP_HEIGHT + MAP_Y + 4);
    printf("                                     Remaining Time:    ");
}

void move(const direction_t direction)
{
    /*
    set_color(COLOR_GREEN, COLOR_BLACK);
    goto_xy(s_head_x + ITEM_X, s_head_y + ITEM_Y);
    printf("%c", (char)ELEMENT_SNAKE_BODY);
    set_color(COLOR_WHITE, COLOR_BLACK);
    s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_BODY;
    */
    switch (direction)
    {
    case NORTH:
        --s_head_y;
        break;
    case SOUTH:
        ++s_head_y;
        break;
    case WEST:
        --s_head_x;
        break;
    case EAST:
        ++s_head_x;
        break;
    default:
        break;
    }

    if (s_head_x < 0 || s_head_y < 0 || s_head_x >= MAP_WITDH || s_head_y >= MAP_HEIGHT) {
        /* TODO: GAME_OVER */
        assert(0);
    }

    switch (s_map[s_head_y][s_head_x])
    {
    case ELEMENT_EMPTY:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy(s_head_x + ITEM_X, s_head_y + ITEM_Y);
        printf("%c", (char)ELEMENT_SNAKE_HEAD);

        /* 
        set_color(COLOR_BLACK, COLOR_BLACK);
        goto_xy(s_tail_x + ITEM_X, s_tail_y + ITEM_Y);
        printf(" ");
        s_map[s_tail_x][s_tail_y] = ELEMENT_EMPTY;
        */
        break;
    case ELEMENT_SNAKE_BODY:
        /* TODO: GAME_OVER */
        assert(0);
        break;
    case ELEMENT_FOOD:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy(s_head_x + ITEM_X, s_head_y + ITEM_Y);
        printf("%c", (char)ELEMENT_SNAKE_HEAD);
        /* TODO: MAKE FOOD */
        break;
    default:
        assert(0);
        break;
    }

    s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_HEAD;
    set_color(COLOR_WHITE, COLOR_BLACK);
}

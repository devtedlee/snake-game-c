#include "game.h"
#include "util.h"

static element_t s_map[MAP_HEIGHT][MAP_WITDH] = { { 0, } };
static int s_head_x;
static int s_head_y;
static int s_tail_x;
static int s_tail_y;

void init(void)
{
    HANDLE console_handle;
    CONSOLE_CURSOR_INFO console_cursor;

    system("mode con cols=66 lines=30 | title SNAKE GAME");

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor.bVisible = 0;
    console_cursor.dwSize = 1;
    SetConsoleCursorInfo(console_handle, &console_cursor);
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

    goto_xy_print(x - 2, y, "> GAME START");

    goto_xy_print(x, y + 1, "GAME INFO");

    goto_xy_print(x, y + 2, "   EXIT   ");

    while (true) {
        input_key_t entered_key = key_control();
        switch (entered_key)
        {
        case INPUT_KEY_UP:
            if (y > 12) {
                goto_xy_print(x - 2, y, " ");
                goto_xy_print(x - 2, --y, ">");
            }
            break;
        
        case INPUT_KEY_DOWN:
            if (y < 14) {
                goto_xy_print(x - 2, y, " ");
                goto_xy_print(x - 2, ++y, ">");
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
    for(x = MAP_X; x < MAP_WITDH + MAP_X + 2; ++x){
        goto_xy_print(x, MAP_Y, "-");
        goto_xy_print(x, MAP_HEIGHT + MAP_Y + 1, "-");
    }
    
    for(y = MAP_Y; y < MAP_HEIGHT + MAP_Y + 1; ++y){
        goto_xy_print(MAP_X, y, "-");
        goto_xy_print(MAP_WITDH + MAP_X + 1, y, "-");
    }

    set_element(ELEMENT_SNAKE_HEAD);
    set_element(ELEMENT_FOOD);

    for (y = 0; y < MAP_HEIGHT; ++y) {
        for (x = 0; x < MAP_WITDH; ++x) {
            switch (s_map[y][x])
            {
            case ELEMENT_EMPTY:
                goto_xy_print(x + ITEM_X, y + ITEM_Y, " ");
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
            
            goto_xy_print(x + ITEM_X, y + ITEM_Y, "%c", s_map[y][x]);
        }
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
    goto_xy_print(MAP_X, MAP_HEIGHT + MAP_Y + 4, "                                     Remaining Time:    ");
}

void move(const direction_t direction)
{
    set_color(COLOR_GREEN, COLOR_BLACK);
    goto_xy_print(s_head_x + ITEM_X, s_head_y + ITEM_Y, "%c", (char)ELEMENT_SNAKE_BODY);
    s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_BODY;
    set_color(COLOR_WHITE, COLOR_BLACK);

    set_position(direction, true);

    if (s_head_x < 0 || s_head_y < 0 || s_head_x >= MAP_WITDH || s_head_y >= MAP_HEIGHT) {
        /* TODO: GAME_OVER */
        assert(0);
    }

    switch (s_map[s_head_y][s_head_x])
    {
    case ELEMENT_EMPTY:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy_print(s_head_x + ITEM_X, s_head_y + ITEM_Y, "%c", ELEMENT_SNAKE_HEAD);
        s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_HEAD;

        goto_xy_print(s_tail_x + ITEM_X, s_tail_y + ITEM_Y, "%c", ' ');
        s_map[s_tail_y][s_tail_x] = ELEMENT_EMPTY;
        /* 
            몸 추가되고나서부터 버그
            아래로 내려오면 정상작동
            왼쪽으로는 무한 몸 증식
            오른쪽도 무한 몸 증식
            위는 머리가 사라지며 무한 몸 증식
            꼬리 위치 선정이 잘못된듯.
        */
        set_position(direction, false);
        break;
    case ELEMENT_SNAKE_BODY:
        /* TODO: GAME_OVER */
        assert(0);
        break;
    case ELEMENT_FOOD:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy_print(s_head_x + ITEM_X, s_head_y + ITEM_Y, "%c", (char)ELEMENT_SNAKE_HEAD);
        s_map[s_head_y][s_head_x] = ELEMENT_SNAKE_HEAD;

        set_element(ELEMENT_FOOD);
        break;
    default:
        assert(0);
        break;
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
}

void set_position(const direction_t direction, const bool is_head) {
    int* x;
    int* y;

    if (is_head) {
        x = &s_head_x;
        y = &s_head_y;
    } else {
        x = &s_tail_x;
        y = &s_tail_y;
    }

    switch (direction)
    {
    case NORTH:
        --(*y);
        break;
    case SOUTH:
        ++(*y);
        break;
    case WEST:
        --(*x);
        break;
    case EAST:
        ++(*x);
        break;
    default:
        assert(0);
        break;
    }
}

void set_element(const element_t element) 
{
    int x;
    int y;

    do {
        srand((unsigned int)time(NULL));
        x = rand() % MAP_WITDH;
        y = rand() % MAP_HEIGHT;
    } while (s_map[y][x] != ELEMENT_EMPTY);
    
    if (element == ELEMENT_SNAKE_HEAD) {
        s_head_x = x;
        s_tail_x = x;
        s_head_y = y;
        s_tail_y = y;
    } else if (element == ELEMENT_FOOD){
        set_color(COLOR_YELLOW, COLOR_BLACK);
        goto_xy_print(x, y, "%c", element);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }

    s_map[y][x] = element;
}

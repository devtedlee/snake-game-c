#include "game.h"
#include "util.h"

static element_t s_map[MAP_HEIGHT][MAP_WIDTH] = { { 0, } };
static snake_t s_snake[MAP_HEIGHT * MAP_WIDTH] = { 0, };
static size_t s_tail_index = 0;
static size_t s_score = 0;

void init(void)
{
    HANDLE console_handle;
    CONSOLE_CURSOR_INFO console_cursor;

    system("mode con cols=51 lines=30 | title SNAKE GAME");

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor.bVisible = 0;
    console_cursor.dwSize = 1;
    SetConsoleCursorInfo(console_handle, &console_cursor);
}

void draw_title(void)
{
    printf("\n\n\n\n\n\n\n");
    printf("         ###    #   #     #     #  #   #####        \n");
    printf("        #       ##  #    # #    # #    #            \n");
    printf("        ####    # # #   #####   ##     #####        \n");
    printf("            #   #  ##   #   #   # #    #            \n");
    printf("        ####    #   #   #   #   #  #   #####        \n");
}

menu_t draw_menu(void)
{
    const size_t MENU_Y = 20;
    size_t x = 22;
    size_t y = (size_t)MENU_Y;

    goto_xy_print(x - 2, y, "> GAME START");

    goto_xy_print(x, y + 1, "GAME INFO");

    goto_xy_print(x, y + 2, "   EXIT   ");

    while (true) {
        input_key_t entered_key = key_control();
        switch (entered_key)
        {
        case INPUT_KEY_UP:
            if (y > MENU_Y) {
                goto_xy_print(x - 2, y, " ");
                goto_xy_print(x - 2, --y, ">");
            }
            break;
        
        case INPUT_KEY_DOWN:
            if (y < MENU_Y + 2) {
                goto_xy_print(x - 2, y, " ");
                goto_xy_print(x - 2, ++y, ">");
            }
            break;

        case INPUT_KEY_SUBMIT:
            return y - MENU_Y;
        
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
    printf("                  PAUSE: P \n");
    printf("                  SELECT: SPACEBAR \n\n\n\n\n\n\n");
    printf("                  DEVELOPER: tedlee\n\n");
    printf("  When you click SPACEBAR, you can go to main page.");

    while (true) {
        if (key_control() == INPUT_KEY_SUBMIT) {
            break;
        }
    }
}

void reset(void)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
        s_snake[i].x = 0;
        s_snake[i].y = 0;
    }

    for (i = 0; i < MAP_HEIGHT; ++i) {
        for (j = 0; j < MAP_WIDTH; ++j) {
            s_map[i][j] = 0;
        }
    }

    s_tail_index = 0;

    set_element(ELEMENT_SNAKE_HEAD);
    set_element(ELEMENT_FOOD);
}

void draw_map(void)
{
    size_t x;
    size_t y;

    system("cls");

    set_color(COLOR_WHITE, COLOR_WHITE);
    for(x = MAP_X; x < MAP_WIDTH + MAP_X + 2; ++x){
        goto_xy_print(x, MAP_Y, "-");
        goto_xy_print(x, MAP_HEIGHT + MAP_Y + 1, "-");
    }
    
    for(y = MAP_Y; y < MAP_HEIGHT + MAP_Y + 1; ++y){
        goto_xy_print(MAP_X, y, "-");
        goto_xy_print(MAP_WIDTH + MAP_X + 1, y, "-");
    }

    for (y = 0; y < MAP_HEIGHT; ++y) {
        for (x = 0; x < MAP_WIDTH; ++x) {
            switch (s_map[y][x])
            {
            case ELEMENT_EMPTY:
                set_color(COLOR_WHITE, COLOR_BLACK);
                goto_xy_print(x + ITEM_X, y + ITEM_Y, " ");
                continue;
            case ELEMENT_SNAKE_BODY:
                set_color(COLOR_GREEN, COLOR_BLACK);
                break;
            case ELEMENT_SNAKE_HEAD:
                set_color(COLOR_RED, COLOR_BLACK);
                break;
            case ELEMENT_FOOD:
                set_color(COLOR_LIGHT_BLUE, COLOR_BLACK);
                break;
            default:
                continue;
            }
            
            goto_xy_print(x + ITEM_X, y + ITEM_Y, "%c", s_map[y][x]);
        }
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
    goto_xy_print(MAP_X, MAP_HEIGHT + MAP_Y + 4, "                                     Score:0");
}

game_status_t move(const direction_t direction, size_t* game_speed_millie_p)
{
    int head_x = s_snake[0].x;
    int head_y = s_snake[0].y;

    set_color(COLOR_GREEN, COLOR_BLACK);
    goto_xy_print(head_x + ITEM_X, head_y + ITEM_Y, "%c", ELEMENT_SNAKE_BODY);
    s_map[head_y][head_x] = ELEMENT_SNAKE_BODY;
    set_color(COLOR_WHITE, COLOR_BLACK);

    switch (direction)
    {
    case NORTH:
        --head_y;
        break;
    case SOUTH:
        ++head_y;
        break;
    case WEST:
        --head_x;
        break;
    case EAST:
        ++head_x;
        break;
    default:
        assert(0);
        break;
    }

    if (head_x < 0 || head_y < 0 || head_x >= MAP_WIDTH || head_y >= MAP_HEIGHT) {
        return GAME_OVER;
    }

    switch (s_map[head_y][head_x])
    {
        size_t i;
    case ELEMENT_EMPTY:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy_print(head_x + ITEM_X, head_y + ITEM_Y, "%c", ELEMENT_SNAKE_HEAD);
        s_map[head_y][head_x] = ELEMENT_SNAKE_HEAD;

        goto_xy_print(s_snake[s_tail_index].x + ITEM_X, s_snake[s_tail_index].y + ITEM_Y, "%c", ' ');
        s_map[s_snake[s_tail_index].y][s_snake[s_tail_index].x] = ELEMENT_EMPTY;

        for (i = s_tail_index; i > 0; --i) {
            s_snake[i].x = s_snake[i - 1].x;
            s_snake[i].y = s_snake[i - 1].y;
        }
        s_snake[0].x = head_x;
        s_snake[0].y = head_y;
        break;
    case ELEMENT_SNAKE_BODY:
        return GAME_OVER;
    case ELEMENT_FOOD:
        set_color(COLOR_RED, COLOR_BLACK);
        goto_xy_print(head_x + ITEM_X, head_y + ITEM_Y, "%c", ELEMENT_SNAKE_HEAD);
        s_map[head_y][head_x] = ELEMENT_SNAKE_HEAD;

        ++s_tail_index;
        for (i = s_tail_index; i > 0; --i) {
            s_snake[i].x = s_snake[i - 1].x;
            s_snake[i].y = s_snake[i - 1].y;
        }
        s_snake[0].x = head_x;
        s_snake[0].y = head_y;
        set_element(ELEMENT_FOOD);
        s_score += 100;
        goto_xy_print(44, MAP_HEIGHT + MAP_Y + 4, "%d", s_score);
        if (*game_speed_millie_p > 100) {
            *game_speed_millie_p -= 50;
        }
        break;
    default:
        assert(0);
        break;
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
    return GAME_RESUME;
}

void set_element(const element_t element) 
{
    int x;
    int y;

    do {
        srand((unsigned int)time(NULL));
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    } while (s_map[y][x] != ELEMENT_EMPTY);
    
    if (element == ELEMENT_SNAKE_HEAD) {
        s_snake[0].x = x;
        s_snake[0].y = y;
    } else if (element == ELEMENT_FOOD){
        set_color(COLOR_LIGHT_BLUE, COLOR_BLACK);
        goto_xy_print(x + ITEM_X, y + ITEM_Y, "%c", element);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }

    s_map[y][x] = element;
}

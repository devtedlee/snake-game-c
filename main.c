#include "game.h"
#include "util.h"

int main(void)
{
    size_t game_speed_millie = 500;

    init();

    while (true) {
        menu_t menu_code;

        draw_title();

        menu_code = draw_menu();

        switch (menu_code)
        {
        case MENU_START: {
            direction_t head_direction = EAST;
            input_key_t entered_key = -1;

            reset();
            draw_map();

            /* GAME LOOP START */
            while (true) {
                game_status_t game_status;                
                if (_kbhit()) {
                    entered_key = key_control();
                    switch (entered_key)
                    {
                        case INPUT_KEY_UP:
                            /* intentional fallthrough */
                        case INPUT_KEY_DOWN:
                            /* intentional fallthrough */
                        case INPUT_KEY_LEFT:
                            /* intentional fallthrough */
                        case INPUT_KEY_RIGHT:                        
                            set_direction(&head_direction, entered_key);
                            entered_key = -1;
                            break;
                        case INPUT_KEY_PAUSE:
                            while (true) {
                                if(entered_key == INPUT_KEY_PAUSE){
                                goto_xy_print(MAP_WIDTH / 2 - 15, MAP_HEIGHT + ITEM_Y / 2,"< PAUSE : PRESS ANY KEY TO RESUME > ");
                                Sleep(400);
                                goto_xy_print(MAP_WIDTH / 2 - 15, MAP_HEIGHT + ITEM_Y / 2,"                                    ");
                                Sleep(400);
                                } else {
                                    draw_map();
                                }
                                if(_kbhit()){
                                    draw_map();
                                    goto resume_game_loop;
                                }
                            }
                            break;
                        case INPUT_KEY_SUBMIT:
                            goto end_game_loop;
                        default:
                            continue;
                    }
                }
resume_game_loop:
                Sleep(game_speed_millie);
                game_status = move(head_direction, &game_speed_millie);
                
                if (game_status == GAME_OVER) {
                    goto_xy_print(MAP_WIDTH / 2 - 11, MAP_HEIGHT / 2 , "+----------------------+");
                    goto_xy_print(MAP_WIDTH / 2 - 11, MAP_HEIGHT / 2 + 1, "|      GAME OVER..     |");
                    goto_xy_print(MAP_WIDTH / 2 - 11, MAP_HEIGHT / 2 + 2, "+----------------------+");
                    Sleep(2000);
                    goto end_game_loop;
                }
            }/* GAME LOOP END */
end_game_loop:
            break;
        }
        case MENU_GAME_INFO: {
            draw_info();
            break;
        }
        case MENU_EXIT: {
            return 0;
        }
        default: {
            assert(0);
            break;
        }
        }

        system("cls");
    }

    return 0;
}

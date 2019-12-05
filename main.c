#include "game.h"
#include "util.h"

int main(void)
{
    size_t game_speed_millie = 500;

    init();

    while (1) {
        menu_t menu_code;

        draw_title();

        menu_code = draw_menu();

        switch (menu_code)
        {
        case MENU_START: {
            direction_t head_direction = EAST;
            input_key_t entered_key = -1;

            draw_map();

            /* GAME LOOP START */
            while (1) {                
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
                            /* add pause() */
                            assert(0);
                            break;
                        case INPUT_KEY_SUBMIT:
                            goto end_game_loop;
                        default:
                            continue;
                    }
                }
                Sleep(game_speed_millie);
                move(head_direction);
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

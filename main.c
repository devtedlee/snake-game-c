#include "game.h"

int main(void)
{
    init();

    while (1) {
        menu_t menu_code;

        draw_title();

        menu_code = draw_menu();

        switch (menu_code)
        {
        case MENU_START:
            draw_map();
            break;
        case MENU_GAME_INFO:
            draw_info();
            break;
        case MENU_EXIT:
            return 0;
        default:
            assert(0);
            break;
        }

        system("cls");
    }

    return 0;
}

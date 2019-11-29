#include "game.h"

int main(void)
{
    init();

    while (1) {
        menu_t menu_code;

        title_draw();

        menu_code = menu_draw();

        switch (menu_code)
        {
        case MENU_START:
            /* code */
            break;
        case MENU_GAME_INFO:
            info_draw();
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

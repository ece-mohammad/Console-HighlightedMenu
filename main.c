#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "key.h"
#include "program.h"
#include "dlinkedlist.h"
#include "highlightmenu.h"
#include "handlers.h"

#define NULL    ((void *)0)


int main(void)
{
    /*  Initialize menus    */
    Menu_t * menu_list = (Menu_t *)calloc(sizeof(Menu_t), NUMBER_OF_MENUS);

    MENU_AttrinutesSet(&menu_list[MENU_NEW],
                       MENU_NEW_NAME,
                       MENU_NEW_TEXT,
                       1,
                       HLM_NewWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_INSERT],
                       MENU_INSERT_NAME,
                       MENU_INSERT_TEXT,
                       2,
                       HLM_InsertWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_SEARCH],
                       MENU_SEARCH_NAME,
                       MENU_SEARCH_TEXT,
                       3,
                       HLM_SearchWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DELETE],
                       MENU_DELETE_NAME,
                       MENU_DELETE_TEXT,
                       4,
                       HLM_DeletWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DISPLAY_ALL],
                       MENU_DISP_ALL_NAME,
                       MENU_DISP_ALL_TEXT,
                       5,
                       HLM_DisplayAllWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DISPLAY],
                       MENU_DISP_NAME,
                       MENU_DISP_TEXT,
                       6,
                       HLM_DisplayWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_EXIT],
                       MENU_EXIT_NAME,
                       MENU_EXIT_TEXT,
                       7,
                       NULL);


    /*  initialize program  */
    Program_t * highlight_menu_program = PROG_Initialize();

    /*  initialize key container    */
    Key_t * user_input = KEY_Init();

    /*  initialize highlight menu   */
    HLM_t * highlight_menu = HLM_Initialize(menu_list, NUMBER_OF_MENUS, user_input, highlight_menu_program);

    /*  configure colors    */
    ColorOptions_t color_opt = {
            .head_bg_color = HEADER_BG_COLOR,
            .head_fg_color = HEADER_FG_COLOR,
            .norm_bg_color = MENU_BG_COLOR,
            .norm_fg_color = MENU_FG_COLOR,
            .select_bg_color = SELECT_BG_COLOR,
            .select_fg_color = SELECT_FG_COLOR,
    };

    HLM_ColorsConfig(highlight_menu, &color_opt);

    /*  configure search function callback   */
    HLM_SearchKeyCallbackSet(highlight_menu, HLM_SearchHandler);

    while(PROG_StateGet(highlight_menu->program) != STATE_EXIT)
    {
        switch(PROG_StateGet(highlight_menu->program))
        {
            case STATE_DISPLAY_UPDATE:
                HLM_DisplayUpdate(highlight_menu);
                break;

            case STATE_INPUT:
                HLM_GetInput(highlight_menu);
                break;

            case STATE_EXIT:
                break;

        }   /*  end switch  */
    }   /*  end while   */

    HLM_TearDown(highlight_menu);

    return 0;
}

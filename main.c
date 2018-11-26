#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "dlinkedlist.h"
#include "data_handlers.h"

#include "key.h"
#include "program.h"
#include "highlightmenu.h"
#include "menu_handlers.h"

#define NULL    ((void *)0)

#define _DATA_HANDLERS_TEST_    0
#define _LINKEDLIST_TEST_       1
#define _HLM_TEST_              2

#define CURRENT_TEST            2


int main(void)
{

#if CURRENT_TEST == _DATA_HANDLERS_TEST_

    DLL_Node_t * emplist[3];
    Employee_t * temp_data = NULL;
    DLL_Node_t * temp_node = NULL;

    temp_data = (Employee_t *)calloc(sizeof(Employee_t), 1);
    temp_node = DLL_CreateNode(temp_data);
    temp_node->next_node = NULL;
    temp_node->prev_node = NULL;
    temp_data->id = 1;
    temp_data->salary = 1000;
    temp_data->name = (char*)calloc(sizeof(char), strlen("Ali"));
    strcpy(temp_data->name, "Ali");
    emplist[0] = temp_node;

    temp_data = (Employee_t *)calloc(sizeof(Employee_t), 1);
    temp_node = DLL_CreateNode(temp_data);
    temp_node->next_node = NULL;
    temp_node->prev_node = NULL;
    temp_data->id = 2;
    temp_data->salary = 1500;
    temp_data->name = (char*)calloc(sizeof(char), strlen("Amr"));
    strcpy(temp_data->name, "Amr");
    emplist[1] = temp_node;

    temp_data = (Employee_t *)calloc(sizeof(Employee_t), 1);
    temp_node = DLL_CreateNode(temp_data);
    temp_node->next_node = NULL;
    temp_node->prev_node = NULL;
    temp_data->id = 3;
    temp_data->salary = 2000;
    temp_data->name = (char*)calloc(sizeof(char), strlen("Ans"));
    strcpy(temp_data->name, "Ans");
    emplist[2] = temp_node;

//    HND_SwapData(emplist[0]->data, emplist[1]->data);

//    HND_PrintNodeData(temp_data);
//    HND_CopyNodeData(emplist[0]->data, temp_data);
//    HND_PrintNodeData(temp_data);

//    int x = 1;
//    printf("%d\n", HND_SearchData(emplist[0]->data, &x));

    HND_PrintNodeData(emplist[0]->data);
    HND_PrintNodeData(emplist[1]->data);
    HND_PrintNodeData(emplist[2]->data);

#elif CURRENT_TEST == _LINKEDLIST_TEST_

    DLinkedList_t * test = DLL_Initialize();
    Employee_t * temp_data = NULL;
    DLL_Node_t * temp_node = NULL;

    temp_data = HND_NewEmployye(1, "Ali", 1000);
    temp_node = DLL_CreateNode(temp_data);
    DLL_AddNode(test, temp_node);

    temp_data = HND_NewEmployye(2, "Amr", 1500);
    temp_node = DLL_CreateNode(temp_data);
    DLL_AddNode(test, temp_node);

    temp_data = HND_NewEmployye(3, "Ans", 2000);
    temp_node = DLL_CreateNode(temp_data);
    DLL_AddNode(test, temp_node);

    temp_data = HND_NewEmployye(4, "S3d", 2500);
    temp_node = DLL_CreateNode(temp_data);
    DLL_AddNode(test, temp_node);

//    DLL_ListPrint(test, HND_PrintNodeData);

//    DLL_SwapNodesData(test->head, test->head->next_node, HND_SwapData);

    DLL_SwapAdjacentNodes(test, test->tail->prev_node, test->tail);

    DLL_ListPrint(test, HND_PrintNodeData);

#elif CURRENT_TEST == _HLM_TEST_
    /*  Initialize menus    */
    Menu_t * menu_list = (Menu_t *)calloc(sizeof(Menu_t), NUMBER_OF_MENUS);

    MENU_AttrinutesSet(&menu_list[MENU_NEW],
                       MENU_NEW_NAME,
                       MENU_NEW_TEXT,
                       1,
                       HND_NewWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_INSERT],
                       MENU_INSERT_NAME,
                       MENU_INSERT_TEXT,
                       2,
                       HND_InsertWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_SEARCH],
                       MENU_SEARCH_NAME,
                       MENU_SEARCH_TEXT,
                       3,
                       HND_SearchWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DELETE],
                       MENU_DELETE_NAME,
                       MENU_DELETE_TEXT,
                       4,
                       HND_DeletWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DISPLAY_ALL],
                       MENU_DISP_ALL_NAME,
                       MENU_DISP_ALL_TEXT,
                       5,
                       HND_DisplayAllWindowInput);

    MENU_AttrinutesSet(&menu_list[MENU_DISPLAY],
                       MENU_DISP_NAME,
                       MENU_DISP_TEXT,
                       6,
                       HND_DisplayWindowInput);

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
    HLM_SearchKeyCallbackSet(highlight_menu, HND_SearchData);

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

#endif

    return 0;
}

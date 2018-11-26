#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include "dlinkedlist.h"
#include "data_handlers.h"

#include "program.h"
#include "key.h"
#include "highlightmenu.h"
#include "menu_handlers.h"


///* ======================= Private APIs ========================= */

/*  hider cursor    */
static void hidecursor(void)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

/*  moves cursor in console to the given location */
static void gotoxy(int x, int y)
{
    COORD coord = { 0, 0 };
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*  colors text */
static void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

///* ======================= MENU APIs ========================= */

/*    initialize a menu instance    */
Menu_t * MENU_Initialize (const unsigned char * name,
                          const unsigned char * text,
                          unsigned int handle,
                          iFunPtr inp_callback)
{
    Menu_t * new_menu = (Menu_t *) calloc(sizeof(Menu_t), 1);

    if (new_menu)
    {
        new_menu->handle = handle;

        new_menu->name = (unsigned char *)calloc(sizeof(unsigned char), strlen(name) + 1);
        new_menu->text = (unsigned char *)calloc(sizeof(unsigned char), strlen(text) + 1);

        if (new_menu->name)
        {
            strcpy(new_menu->name, name);
        }   /*  end if  */

        if (new_menu->text)
        {
            strcpy(new_menu->text, text);
        }   /*  end if  */


        if (inp_callback)
        {
            new_menu->inp_callback = inp_callback;
        }   /*  end if  */

    }   /*  end if menu */
    return new_menu;
}

/*  sets menu attributes */
void MENU_AttrinutesSet(Menu_t * self, const char * name, const char * text,
                        unsigned int handle, iFunPtr inp_callback)
{

    if(self)
    {
        self->handle = handle;
        self->inp_callback = inp_callback;

        if(name)
        {
            self->name = (char *) calloc(sizeof(char), strlen(name));
            strcpy(self->name, name);
        }   /*  end if  */

        if(text)
        {
            self->text = (char *) calloc(sizeof(char), strlen(text));
            strcpy(self->text, text);
        }   /*  end if  */
    }   /*  end if  */
}

/*  display menu    */
void MENU_Display(Menu_t * self)
{
    printf("%s\n-----------------\n", self->name);
    printf("%s\n", self->text);
}

/*  handle input   */
int MENU_InputHandle(Menu_t * self)
{
    return self->inp_callback(self);
}

/*  destroy menu    */
void MENU_TearDown(Menu_t * self)
{
    free(self->name);
    free(self->text);
    free(self);
}

///* ===================== HLM APIs ============================== */

/*  initialize highlight menu instance  */
HLM_t * HLM_Initialize(Menu_t * menus_list, unsigned int menus_num, Key_t * key, Program_t * prog)
{
    HLM_t * new_menu = (HLM_t *) calloc(sizeof(HLM_t), 1);

    if (new_menu)
    {
        new_menu->sub_menus_num = menus_num;
        new_menu->sub_menus_list = menus_list;
        new_menu->last_key = key;
        new_menu->program = prog;

    }   /*  end if  */

    new_menu->employee_data = DLL_Initialize();
    new_menu->current_selection = MENU_NEW;
    new_menu->current_window = WIN_MAIN;
    new_menu->color_options = NULL;

    new_menu->search_key = NULL;
    new_menu->search_args = NULL;

    return new_menu;
}

/*  configure colors    */
void HLM_ColorsConfig(HLM_t * self, ColorOptions_t * color_opts)
{
    self->color_options = color_opts;
}

/*  current window get  */
HLM_Windows_t HLM_WindowGet(HLM_t * self)
{
    return self->current_window;
}

/*  current window set  */
void HLM_WindowSet(HLM_t * self, HLM_Windows_t new_win)
{
    if (new_win < NUMBER_OF_WINDOWS)
    {
        self->current_window = new_win;
    }   /*  end if  */
}

/*  current selection set  */
void HLM_SelectionSet(HLM_t * self, HLM_Menus_t new_select)
{
    if (new_select < NUMBER_OF_MENUS)
    {
        self->current_selection = new_select;
    }   /*  end if  */
}

/*  current selection get  */
HLM_Menus_t HLM_SelectionGet(HLM_t * self)
{
    return self->current_selection;
}

/*  get key */
Key_t * HLM_KeyGet(HLM_t * self)
{
    return self->last_key;
}

/*  set key */
void HLM_KeySet(HLM_t * self, Key_t * key)
{
    self->last_key = key;
}

/*  sets search args for linked list search */
void HLM_SearchArgsSet(HLM_t * self, void * args)
{
    self->search_args = args;
}

/*  sets callback function for linked list search   */
void HLM_SearchKeyCallbackSet(HLM_t * self, uDataSearchKey callback)
{
    self->search_key = callback;
}

/*  displays a menu */
void HLM_DisplayMenu(HLM_t * self, HLM_Menus_t menu)
{
    if (menu < NUMBER_OF_MENUS)
    {
        MENU_Display(&self->sub_menus_list[menu]);
    }   /*  end if   */
}

/*  display main menu   */
void HLM_DisplayMainMenu(HLM_t * self)
{
    textattr(SET_TEXT_COLOR(self->color_options->head_bg_color, self->color_options->head_fg_color));
    printf("Employees Manager\n-----------------\n");
    textattr(SET_TEXT_COLOR(self->color_options->norm_bg_color, self->color_options->norm_fg_color));

    for (int i = 0; i < self->sub_menus_num; i++)
    {
        gotoxy(3, i + 2);
        if (HLM_SelectionGet(self) == i)
        {
            textattr(SET_TEXT_COLOR(self->color_options->select_bg_color, self->color_options->select_fg_color));
            printf("%s", self->sub_menus_list[i].name);
            textattr(SET_TEXT_COLOR(self->color_options->norm_bg_color, self->color_options->norm_fg_color));
        }
        else
        {
            printf("%s\n", self->sub_menus_list[i].name);
        }   /*  end if  */
    }   /*  end for */
}

/*  display update */
void HLM_DisplayUpdate(HLM_t * self)
{
    hidecursor();
    system("cls");
    gotoxy(0, 0);

    switch (HLM_WindowGet(self))
    {
        case WIN_MAIN:
            HLM_DisplayMainMenu(self);
            break;

        case WIN_NEW:
        case WIN_INSERT:
        case WIN_SEARCH:
        case WIN_DELETE:
        case WIN_DISPLAY_ALL:
        case WIN_DISPLAY:
            MENU_Display(&self->sub_menus_list[ ( HLM_WindowGet(self) - 1 ) ]);
            break;

        case WIN_EXIT:
            break;

        default:
            break;
    }   /*  end switch */

    PROG_StateSet(self->program, STATE_INPUT);
}

/*  get user input  */
void HLM_GetInput(HLM_t * self)
{
    Menu_t * current_menu = &self->sub_menus_list[HLM_WindowGet(self) - 1];

    switch(self->current_window)
    {
    case WIN_MAIN:
        if ( HND_MainWindowInput(self) == EXIT_PROGRAM )
        {
            PROG_StateSet(self->program, STATE_EXIT);
            HLM_WindowSet(self, WIN_EXIT);
        }
        else
        {
            PROG_StateSet(self->program, STATE_DISPLAY_UPDATE);
        }   /*  end if  */
        break;

    case WIN_NEW:
    case WIN_INSERT:
    case WIN_SEARCH:
    case WIN_DELETE:
    case WIN_DISPLAY_ALL:
    case WIN_DISPLAY:
        switch(current_menu->inp_callback(self))
        {

        case STAY_IN_MENU:
            PROG_StateSet(self->program, STATE_DISPLAY_UPDATE);
            break;

        case RETRUN_TO_MAIN_MENU:
            HLM_WindowSet(self, WIN_MAIN);
            PROG_StateSet(self->program, STATE_DISPLAY_UPDATE);
            break;

        case EXIT_PROGRAM:
            PROG_StateSet(self->program, STATE_EXIT);
            break;

        }   /*  end switch  */
        break;

    case WIN_EXIT:
        break;
    }   /*  end switch  */
}

/*  destroy HLM instance    */
void HLM_TearDown(HLM_t * self)
{
    DLL_ListTearDown(self->employee_data);
}

/*  exit program    */
void HLM_Exit(HLM_t * self)
{
    HLM_TearDown(self);
}

#ifndef _HL_MENU_H_
#define _HL_MENU_H_


/** ================== Constants =================== */
#define MENU_NEW_NAME       "New"
#define MENU_NEW_TEXT       "New Employee Data"

#define MENU_INSERT_NAME    "Insert"
#define MENU_INSERT_TEXT    "Insert Employee Data"

#define MENU_SEARCH_NAME    "Search"
#define MENU_SEARCH_TEXT    "Search Employee Data"

#define MENU_DELETE_NAME    "Delete"
#define MENU_DELETE_TEXT    "Delete Employee Data"

#define MENU_DISP_ALL_NAME  "Display All"
#define MENU_DISP_ALL_TEXT  "Display Data"

#define MENU_DISP_NAME      "Display"
#define MENU_DISP_TEXT      "Display Employee Data"

#define MENU_EXIT_NAME      "Exit"
#define MENU_EXIT_TEXT      "Exit Employee Data"

/* ================= Custom types ==================== */
typedef enum
{
    MENU_NEW,
    MENU_INSERT,
    MENU_SEARCH,
    MENU_DELETE,
    MENU_DISPLAY_ALL,
    MENU_DISPLAY,
    MENU_EXIT,
    NUMBER_OF_MENUS,
} HLM_Menus_t;

typedef enum
{
    WIN_MAIN,
    WIN_NEW,
    WIN_INSERT,
    WIN_SEARCH,
    WIN_DELETE,
    WIN_DISPLAY_ALL,
    WIN_DISPLAY,
    WIN_EXIT,
    NUMBER_OF_WINDOWS,
} HLM_Windows_t;

typedef enum
{
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CAYAN,
    COLOR_RED,
    COLOR_PURPLE,
    COLOR_GOLD,
    COLOR_WHITE,
    COLOR_GREY,
    COLOR_BLUE_BR,
    COLOR_GREEN_BR,
    COLOR_CAYAN_BR,
    COLOR_RED_BR,
    COLOR_PURPLE_BR,
    COLOR_GOLD_BR,
    COLOR_WHITE_BR,
} Color_t;

typedef struct
{
    Color_t head_fg_color;
    Color_t head_bg_color;
    Color_t select_fg_color;
    Color_t select_bg_color;
    Color_t norm_fg_color;
    Color_t norm_bg_color;
} ColorOptions_t;

/** ======================== HLM TYPES ========================= **/

static struct MenuStruct {
    unsigned char * name;
    unsigned char * text;
    unsigned int handle;
    unsigned int (* inp_callback)(struct MenuStruct *);
};

typedef struct MenuStruct Menu_t;
typedef unsigned int (* iFunPtr)(Menu_t *);

//typedef struct
//{
//    unsigned char * name;
//    unsigned char * text;
//    unsigned int handle;
//    iFunPtr inp_callback;
//
//} Menu_t;

typedef struct
{
    Menu_t * sub_menus_list;
    unsigned int sub_menus_num;

    ColorOptions_t * color_options;

    HLM_Menus_t current_selection;
    HLM_Windows_t current_window;

    Key_t * last_key;
    Program_t * program;

    DLinkedList_t * employee_data;
    uNodeSearchKey search_key;
    void * search_args;

} HLM_t;

/* =================== Constants =========================== */


#define RETRN_TO_MENU           1
#define RETRUN_TO_MAIN_MENU     2
#define EXIT_PROGRAM            -1

#define HEADER_FG_COLOR   COLOR_RED_BR
#define HEADER_BG_COLOR   COLOR_BLACK
#define MENU_FG_COLOR     COLOR_GREEN_BR
#define MENU_BG_COLOR     COLOR_BLACK
#define SELECT_FG_COLOR   COLOR_BLUE_BR
#define SELECT_BG_COLOR   COLOR_WHITE


/* ====================== Macros ================================= */

#define SET_TEXT_COLOR(bgc, fgc)   (((bgc&0xf) << 4) | (fgc&0xf))

/* ===================== Public APIs =========================== */

///* ------------------- Menu APIs ----------------------------- */
/*    initialize a menu instance    */
Menu_t * MENU_Initialize (const unsigned char * name,
                          const unsigned char * text,
                          unsigned int handle,
                          iFunPtr inp_callback);

/*  sets menu attributes */
void MENU_AttrinutesSet(Menu_t * self,
                        const char * name,
                        const char * text,
                        unsigned int handle,
                        iFunPtr inp_callback);

/*  display menu    */
void MENU_Display(Menu_t * self);

/*  handle input   */
int MENU_InputHandle(Menu_t * self);

/*  handle output   */
void MENU_OutputHandle(Menu_t * self);

/*  destroy menu    */
void MENU_TearDown(Menu_t * self);

///* --------------------------- HLM APIs ------------------------ */

/*  initialize highlight menu instance  */
HLM_t * HLM_Initialize(Menu_t * menus_list, unsigned int menus_num, Key_t * key, Program_t * prog);

/*  configure colors    */
void HLM_ColorsConfig(HLM_t * self, ColorOptions_t * color_opts);

/*  current window get  */
HLM_Windows_t HLM_WindowGet(HLM_t * self);

/*  current window set  */
void HLM_WindowSet(HLM_t * self, HLM_Windows_t new_win);

/*  current selection set  */
void HLM_SelectionSet(HLM_t * self, HLM_Menus_t new_select);

/*  current selection get  */
HLM_Menus_t HLM_SelectionGet(HLM_t * self);

/*  get key */
Key_t * HLM_KeyGet(HLM_t * self);

/*  set key */
void HLM_KeySet(HLM_t * self, Key_t * key);

/*  sets callback function for linked list search   */
void HLM_SearchKeyCallbackSet(HLM_t * self, uNodeSearchKey callback);

/*  sets search args for linked list search */
void HLM_SearchArgsSet(HLM_t * self, void * args);

/*  display update */
void HLM_DisplayUpdate(HLM_t * self);

/*  get user input  */
void HLM_GetInput(HLM_t * self);

/*  exit program    */
void HLM_Exit(HLM_t * self);

/*  destroy HLM instance    */
void HLM_TearDown(HLM_t * self);

/* ============================ Private APIs =============================== */

///*  Displays main menu  */
//void HLM_DisplayMainMenu(HLM_t * self);     /// ---> private

///*  Display main menu   */
//void HLM_DisplayMenu(HLM_t * self, HLM_Menus_t menu);   /// ---> private

///*  sets search args for linked list search */
//void HLM_SearchArgsSet(HLM_t * self, void * args);  /// ---> private

///*  a private method used by search menu to look for employees */
//unsigned int HLM_DataSearchKey(DLL_Node_t * node, void * args);

///*  hider cursor    */
//static void hidecursor(void);  /// ---> private
//
///*  moves cursor in console to the given location */
//static void gotoxy(int x, int y);  /// ---> private
//
///*  colors text */
//static void textattr(int i);   /// ---> private

#endif // _HL_MENU_H_

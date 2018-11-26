#ifndef _MENU_HANDLERS_H_
#define _MENU_HANDLERS_H_

/* ------------------------ Public APIs --------------------------- */

/*  handles input in main window  */
int HND_MainWindowInput(HLM_t * self);      /// ---> CONFIG

/*  handle input in DISPLAY ALL window  */
int HND_DisplayAllWindowInput(HLM_t * self);    /// ---> CONFIG

/*  handle input in DISPLAY window  */
int HND_DisplayWindowInput(HLM_t * self);   /// ---> CONFIG

/*  handles input in DELETE window  */
int HND_DeletWindowInput(HLM_t * self);     /// ---> CONFIG

/*  handle input in SEARCH Win   */
int HND_SearchWindowInput(HLM_t * self);    /// ---> CONFIG

/*  handle input in NEW window  */
int HND_NewWindowInput(HLM_t * self);       /// ---> CONFIG

/*  handle input in INSERT Menu */
int HND_InsertWindowInput(HLM_t * self);    /// ---> CONFIG


#endif // _MENU_HANDLERS_H_

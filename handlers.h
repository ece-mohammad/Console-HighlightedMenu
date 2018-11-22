
#ifndef _HANDLERS_H_
#define _HANDLERS_H_

/* ------------------------ Public APIs --------------------------- */

/*  node print handler   */
int HLM_NodePrint(DLL_Node_t * node);

/*  node search handler */
unsigned int HLM_SearchHandler(DLL_Node_t * node, void * id);

/*  handles input in main window  */
int HLM_MainWindowInput(HLM_t * self);      /// ---> CONFIG

/*  handle input in DISPLAY ALL window  */
int HLM_DisplayAllWindowInput(HLM_t * self);    /// ---> CONFIG

/*  handle input in DISPLAY window  */
int HLM_DisplayWindowInput(HLM_t * self);   /// ---> CONFIG

/*  handles input in DELETE window  */
int HLM_DeletWindowInput(HLM_t * self);     /// ---> CONFIG

/*  handle input in SEARCH Win   */
int HLM_SearchWindowInput(HLM_t * self);    /// ---> CONFIG

/*  handle input in NEW window  */
int HLM_NewWindowInput(HLM_t * self);       /// ---> CONFIG

/*  handle input in INSERT Menu */
int HLM_InsertWindowInput(HLM_t * self);    /// ---> CONFIG


#endif // _HANDLERS_H_

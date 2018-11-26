#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlinkedlist.h"
#include "data_handlers.h"
#include "key.h"
#include "program.h"
#include "highlightmenu.h"


/* ---------------------- Private Functions ------------------------ */

/* gets employee data from user (private)   */
Employee_t * HLM_GetEmploeeData(void)
{
    Employee_t * data = (Employee_t *) calloc(sizeof(Employee_t), 1);
    data->name = (char *) calloc(sizeof(char), 20);

    printf("Enter employee ID: ");
    scanf("%d", &data->id);
    fflush(stdin);

    printf("Enter Employee Name: " );
    fgets(data->name, 20, stdin);
    fflush(stdin);

    printf("Enter employee salary: ");
    scanf("%f", &data->salary);
    fflush(stdin);

    return data;
}

/*  handles input in main window  */
int HND_MainWindowInput(HLM_t * self)
{
    int ret = STAY_IN_MENU;
    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {
        case KEY_TYPE_SCROLL:

            switch (KEY_CodeGet(self->last_key))
            {
                case KCODE_DOWN:
                case KCODE_RIGHT:
                    if (HLM_SelectionGet(self) == MENU_EXIT)
                    {
                        HLM_SelectionSet(self,  MENU_NEW );
                    }
                    else
                    {
                        HLM_SelectionSet( self, HLM_SelectionGet(self) + 1 );
                    }
                    break;

                case KCODE_UP:
                case KCODE_LEFT:
                    if (HLM_SelectionGet(self) == MENU_NEW)
                    {
                        HLM_SelectionSet(self,  MENU_EXIT );
                    }
                    else
                    {
                        HLM_SelectionSet( self, HLM_SelectionGet(self) - 1 );
                    }
                    break;

                case KCODE_PG_UP:
                case KCODE_HOME:
                    HLM_SelectionSet( self, MENU_NEW );
                    break;

                case KCODE_PG_DWN:
                case KCODE_END:
                    HLM_SelectionSet( self, MENU_EXIT );
                    break;

            }   /*  end switch  KEY_CodeGet */
            break; /*  end case KEY_TYPE_SCROLL    */

        case KEY_TYPE_NORMAL:
            switch (KEY_CodeGet(self->last_key))
            {

                case KCODE_TAB:
                    if (HLM_SelectionGet(self) == MENU_EXIT)
                    {
                        HLM_SelectionSet(self,  MENU_NEW );
                    }
                    else
                    {
                        HLM_SelectionSet( self, HLM_SelectionGet(self) + 1 );
                    }
                    break;

                case KCODE_ENTER:
                    if (HLM_SelectionGet(self) == MENU_EXIT)
                    {
                        ret = EXIT_PROGRAM;
                    }
                    else
                    {
                        HLM_WindowSet(self, HLM_SelectionGet(self) + 1);
                    }
                    break;

                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

            }   /*  end switch  KEY_CodeGet */
            break;  /*  end case KEY_TYPE_NORMAL    */

        default:
            break;
    }   /*  end switch  KEY_TypeGet */
    return ret;
}

/*  handle input in DISPLAY ALL window  */
int HND_DisplayAllWindowInput(HLM_t * self)
{
    int ret = RETRUN_TO_MAIN_MENU;

    DLL_ListPrint(self->employee_data, HND_PrintNodeData);

    printf("\n========\nPress one of the following keys:\n");
    printf("ESC : Exit the program.\n");
    printf("Any key to return to main menu.\n");

    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {

        case KEY_TYPE_NORMAL:

            switch (KEY_CodeGet(self->last_key))
            {
                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

                default:
                    ret = RETRUN_TO_MAIN_MENU;
                    break;
            }   /*  end switch code_get */
            break;

        default:
            break;
    }   /*  end switch key_code */

    return ret;
}

/*  handle input in DISPLAY window  */
int HND_DisplayWindowInput(HLM_t * self)
{
    int loop_condition = CONTINUE_LOOP;
    int ret = STAY_IN_MENU;
    DLL_Node_t * current_node = self->employee_data->head;

    do
    {

        system("cls");
        printf("Navigate between employees data used right and left arrows!\n");
        printf("Press Enter to return to main menu, or ESC to quit the program.\n");
        printf("Current employee data:\n----------------------\n");

        if (current_node)
        {
            HND_PrintNodeData(current_node->data);

            KEY_GetKey(self->last_key);

            switch (KEY_TypeGet(self->last_key))
            {

                case KEY_TYPE_SCROLL:

                    switch (KEY_CodeGet(self->last_key))
                    {

                        case KCODE_RIGHT:
                            if (current_node->next_node)
                            {
                                current_node = current_node->next_node;
                            }
                            else
                            {
                                current_node = self->employee_data->head;
                            }   /*  end if  */
                            break;

                        case KCODE_LEFT:
                            if (current_node->prev_node)
                            {
                                current_node = current_node->prev_node;
                            }
                            else
                            {
                                current_node = self->employee_data->tail;
                            }   /*  end if  */
                            break;

                        default:
                            break;

                    }   /*  end switch get_code  */

                    break;

                case KEY_TYPE_NORMAL:

                    switch (KEY_CodeGet(self->last_key))
                    {

                        case KCODE_ESC:
                            loop_condition = END_LOOP;
                            ret = EXIT_PROGRAM;
                            break;

                        case KCODE_ENTER:
                            loop_condition = END_LOOP;
                            ret = RETRUN_TO_MAIN_MENU;
                            break;
                    }   /*  end switch get_code */
                    break;

                default:
                    break;

            }   /*  end switch key_type */

        }
        else
        {
            printf("### No data to display!\n");
            loop_condition = END_LOOP;
            ret = RETRUN_TO_MAIN_MENU;
            system("pause");
        }   /*  end if  */
    }
    while (loop_condition);     /*  end while   */

    return ret;
}

/*  handles input in DELETE window  */
int HND_DeletWindowInput(HLM_t * self)
{
    int ret = STAY_IN_MENU;
    int index = 0;

    printf("Enter employee index to delete: ");
    scanf("%d", &index);

    DLL_DeleteNode(self->employee_data, index);

    printf("\n========\nPress one of the following keys:\n");
    printf("'y' : Delete another employee.\n");
    printf("ESC : Exit the program.\n");
    printf("Any key to return to main menu.\n");

    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {

        case KEY_TYPE_NORMAL:

            switch (KEY_CodeGet(self->last_key))
            {

                case 'y':
                case 'Y':
                    ret = STAY_IN_MENU;
                    break;

                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

                default:
                    ret = RETRUN_TO_MAIN_MENU;
                    break;
            }   /*  end switch code_get */
            break;

        default:
            break;
    }   /*  end switch key_code */

    return ret;

}

/*  handle input in SEARCH Win   */
int HND_SearchWindowInput(HLM_t * self)
{
    int ret = STAY_IN_MENU;
    int id = 0;
    DLL_Node_t * res = NULL;
    Employee_t * found = NULL;

    printf("Enter employee ID to search for: ");
    scanf("%d", &id);
    fflush(stdin);

    HLM_SearchArgsSet(self, &id);
    res = DLL_Search(self->employee_data, self->search_key, self->search_args);

    if (res)
    {
        found = (Employee_t *) res->data;
        printf("ID: %d \nName: %sSalary: %.2f \n", found->id, found->name, found->salary);
    }
    else
    {
        printf("\nEmployee not found!!\n");
    }   /* end if  */

    printf("\n========\nPress one of the following keys:\n");
    printf("'y' : Search for another employee.\n");
    printf("ESC : Exit the program.\n");
    printf("Any key to return to main menu.\n");

    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {

        case KEY_TYPE_NORMAL:

            switch (KEY_CodeGet(self->last_key))
            {

                case 'y':
                case 'Y':
                    ret = STAY_IN_MENU;
                    break;

                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

                default:
                    ret = RETRUN_TO_MAIN_MENU;
                    break;
            }   /*  end switch code_get */
            break;

        default:
            break;
    }   /*  end switch key_code */

    return ret;
}

/*  handle input in NEW window  */
int HND_NewWindowInput(HLM_t * self)
{

    int ret = STAY_IN_MENU;
    DLL_Node_t * new_node = NULL;

    Employee_t * emp_data = HLM_GetEmploeeData();
    new_node = DLL_CreateNode(emp_data);

    printf("Entered employee data:\n----------\n");
    printf("ID: %d \nName: %s \nSalary: %.2f \n", emp_data->id, emp_data->name, emp_data->salary);

    printf("\n========\nPress one of the following keys:\n");
    printf("'y' : Confirm adding employee data to the system then add other data.\n");
    printf("'n' : Discard data and add other data to the system.\n");
    printf("'b' : Confirm adding employee data to the system and return to main menu.\n");
    printf("'c' : Cancel adding employee data to the system and return to main menu.\n");
    printf("ESC : Exit the program.\n");
    printf("Any key to return to main menu.\n");

    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {

        case KEY_TYPE_NORMAL:

            switch (KEY_CodeGet(self->last_key))
            {

                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

                case 'y':
                case 'Y':
                    DLL_AddNode(self->employee_data, new_node);
                    ret = STAY_IN_MENU;
                    break;

                case 'b':
                case 'B':
                    DLL_AddNode(self->employee_data, new_node);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;

                case 'n':
                case 'N':
                    //free(emp_data->name);
                    //free(new_node);
                    DLL_NodeTearDown(new_node, HND_DestroyData);
                    ret = STAY_IN_MENU;
                    break;

                case 'C':
                case 'c':
                    //free(emp_data->name);
                    //free(new_node);
                    DLL_NodeTearDown(new_node, HND_DestroyData);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;

                default:
                    //free(emp_data->name);
                    //free(new_node);
                    DLL_NodeTearDown(new_node, HND_DestroyData);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;
            }   /*  end switch key_code */

            break;

        default:
            break;

    }   /*  end switch key_type */

    return ret;
}

/*  handle input in INSERT Menu */
int HND_InsertWindowInput(HLM_t * self)
{
    int ret = STAY_IN_MENU;
    int index = 0;

    printf("Enter location to add the user: ");
    scanf("%d", &index);

    Employee_t * data = HLM_GetEmploeeData();
    DLL_Node_t * node = DLL_CreateNode(data);

    printf("Entered employee data:\n----------\n");
    printf("ID: %d \nName: %s \nSalary: %.2f \n", data->id, data->name, data->salary);

    printf("\n========\nPress one of the following keys:\n");
    printf("'y' : Confirm adding employee data to the system then add other data.\n");
    printf("'b' : Confirm adding employee data to the system and return to main menu.\n");
    printf("'n' : Discard data and add other data to the system.\n");
    printf("'c' : Cancel adding employee data to the system and return to main menu.\n");
    printf("ESC : Exit the program.\n");
    printf("Any key to return to main menu.\n");

    KEY_GetKey(self->last_key);

    switch (KEY_TypeGet(self->last_key))
    {
        case KEY_TYPE_NORMAL:

            switch (KEY_CodeGet(self->last_key))
            {
                case KCODE_ESC:
                    ret = EXIT_PROGRAM;
                    break;

                case 'y':
                case 'Y':
                    DLL_InsertNode(self->employee_data, node, index);
                    ret = STAY_IN_MENU;
                    break;

                case 'b':
                case 'B':
                    DLL_InsertNode(self->employee_data, node, index);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;

                case 'n':
                case 'N':
                    //free(data->name);
                    //free(node);
                    DLL_NodeTearDown(node, HND_DestroyData);
                    ret = STAY_IN_MENU;
                    break;

                case 'C':
                case 'c':
                    //free(data->name);
                    //free(node);
                    DLL_NodeTearDown(node, HND_DestroyData);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;

                default:
                    //free(data->name);
                    //free(node);
                    DLL_NodeTearDown(node, HND_DestroyData);
                    ret = RETRUN_TO_MAIN_MENU;
                    break;
            }   /*  end switch key_code */

            break;

        default:
            break;

    }   /*  end switch key_type */

    return ret;
}

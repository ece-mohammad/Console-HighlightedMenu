#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlinkedlist.h"
#include "key.h"
#include "program.h"
#include "highlightmenu.h"
#include "data_handlers.h"


/* --------------------------- Public Data Handlers ------------------------------- */

/*  make a new data container   */
Employee_t * HND_NewEmployye(int id, const char name [20], float salary)
{
    Employee_t * new_emp = (Employee_t *) calloc(sizeof(Employee_t), 1);
    if(new_emp)
    {
        new_emp->id = id;
        new_emp->salary = salary;
        new_emp->name = (char *) calloc(sizeof(char), strlen(name));
        strcpy(new_emp->name, name);
    }   /*  end if  */
    return new_emp;
}

/*  node data print handler   */
unsigned int HND_PrintNodeData(void * data)
{
    unsigned int ret = (!!data);
    if(ret)
    {
        printf("Employee data: Id: %d, name: %s, Salary: %.2f\n-------------------------\n",
               ((Employee_t *)data)->id,
               ((Employee_t *)data)->name,
               ((Employee_t *)data)->salary
               );
    }   /*  end if  */
    return ret;
}

/*  copy node data  */
unsigned int HND_CopyNodeData(void * src_data, void * dst_data)
{
    unsigned int ret = (src_data && dst_data);
    if(ret)
    {
        ((Employee_t *)dst_data)->id = ((Employee_t *) src_data)->id;
        ((Employee_t *)dst_data)->salary = ((Employee_t *) src_data)->salary;

        free(((Employee_t *)dst_data)->name);
        ((Employee_t *)dst_data)->name = (char *)calloc(sizeof(char), strlen( ((Employee_t *)src_data)->name) );
        strcpy( ((Employee_t *)dst_data)->name, ((Employee_t *) src_data)->name );
    }   /*  end if  */
    return ret;
}

/*  swap two nodes  */
unsigned int HND_SwapData(void * ldata, void* rdata)
{
    Employee_t * temp_data = (Employee_t *) calloc(sizeof(Employee_t), 1);
    unsigned int ret = (ldata && rdata);
    if(ret)
    {
        HND_CopyNodeData(ldata, temp_data);
        HND_CopyNodeData(rdata, ldata);
        HND_CopyNodeData(temp_data, rdata);
    }   /*  end if  */

    HND_DestroyData(temp_data);

    return ret;
}

/*  node search handler */
unsigned int HND_SearchData(void * data, void * search_key)
{
    unsigned int ret = (data && search_key);
    if(ret)
    {
        ret = ((Employee_t *)data)->id == *((unsigned int *)search_key);
    }   /*  en if   */
    return ret;
}

/*  compare two nodes  */
int HND_CompareData(void * ldata, void * rdata)
{
    int ret = (ldata && rdata);
    if(ret)
    {
        ret = ((Employee_t *)ldata)->id - ((Employee_t *)rdata)->id;
    }   /*  end if   */
    return ret;
}

/*  destroy node    */
unsigned int HND_DestroyData(void * data)
{
    unsigned int ret = (!!data);
    if(ret)
    {
        free( ((Employee_t *)data)->name );
        free(data);
    }   /*  end if  */
    return ret;
}


#ifndef _HANDLERS_H_
#define _HANDLERS_H_

/* ------------------------ Custom Types ------------------------- */

/* ===== Node Data ==== */
typedef struct
{
    char * name;
    float salary;
    unsigned int id;
} Employee_t;

/* ------------------------ Handlers --------------------------- */


/*  make a new data container   */
Employee_t * HND_NewEmployye(int id, const char name [20], float salary);

/*  node print handler   */
unsigned int HND_PrintNodeData(void * data);

/*  copy node data  */
unsigned int HND_CopyNodeData(void * src_data, void * dst_data);

/*  swap two nodes  */
unsigned int HND_SwapData(void * ldata, void* rdata);

/*  node search handler */
unsigned int HND_SearchData(void * data, void * search_key);

/*  compare two nodes  */
int HND_CompareData(void * lnode, void * rdata);

/*  destroy node    */
unsigned int HND_DestroyData(void * data);


#endif // _HANDLERS_H_

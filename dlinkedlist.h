#ifndef _DLINKED_LIST_H_
#define _DLINKED_LIST_H_


/* ---------------------- Custom types ------------------------ */

/* ===== Node Structure ==== */
struct node
{
    void * data;
    struct node * next_node;
    struct node * prev_node;
};

typedef struct node DLL_Node_t;

/* ===== Node handlers ==== */
typedef unsigned int (*uDataPrintHandle)(void * data);
typedef unsigned int (*uDataCopyHandle)(void * src, void * dst);
typedef unsigned int (*uDataSwapHandle)(void * ldata, void * rdata);
typedef unsigned int (*uDataSearchKey)(void * data, void * key);
typedef int (*uDataCompareKey)(void * ldata, void * rdata);
typedef unsigned int (*uDataDestoryHandle)(void * data);

/* ===== Linked List ==== */
typedef struct
{
    DLL_Node_t * head;
    DLL_Node_t * tail;
    unsigned int list_size;
} DLinkedList_t;

/* --------------------- Public APIs -------------------------- */

/*  initialize LinkedList   */
DLinkedList_t * DLL_Initialize(void);

/*  create a new node in Linked List*/
DLL_Node_t * DLL_CreateNode(void * node_data);

/*  add a new node to the end of the list  */
void DLL_AddNode(DLinkedList_t * self, DLL_Node_t * node);

/*  deletes a node from the list  */
void DLL_DeleteNode(DLinkedList_t * self, unsigned int index);

/*  insert a node in the list   */
void DLL_InsertNode(DLinkedList_t * self, DLL_Node_t * node, unsigned int index);

/*  search for a node in the list   */
DLL_Node_t * DLL_Search(DLinkedList_t * self, uDataSearchKey key, void * serach_args);

/*  displays a given node   */
void DLL_NodePrint(DLL_Node_t * node, uDataPrintHandle display_func);

/*  print linked list   */
void DLL_ListPrint(DLinkedList_t * self, uDataPrintHandle display_func);

/*  copy a node into a new node */
void DLL_NodeCopy(DLL_Node_t * src_node, DLL_Node_t * dst_node, uDataCopyHandle copy_handle);

/* swap n2 nodes data  */
void DLL_SwapNodesData(DLL_Node_t * lnode, DLL_Node_t * rnode, uDataSwapHandle data_swap_handle);

/* swap 2 nodes */
void DLL_SwapAdjacentNodes(DLinkedList_t * self, DLL_Node_t * rnode, DLL_Node_t *lnode);

/*  compare 2 nodes */
int DLL_NodeCompare(DLL_Node_t *rnode, DLL_Node_t * lnode, uDataCompareKey compare_key);

/*  destroys a node */
void DLL_NodeTearDown(DLL_Node_t * node, uDataDestoryHandle destroy_handle);

/*  destroys a linked list   */
void DLL_ListTearDown(DLinkedList_t * self);

#endif // _DLINKED_LIST_H_

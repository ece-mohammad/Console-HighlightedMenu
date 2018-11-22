#ifndef _DLINKED_LIST_H_
#define _DLINKED_LIST_H_


/* ---------------------- Custom types ------------------------ */
/* ===== Node Data ==== */
typedef struct
{
    char * name;
    float salary;
    unsigned int id;
} Employee_t;

/* ===== Node Structure ==== */
struct node
{
    void * data;
    struct node * next_node;
    struct node * prev_node;
};

typedef struct node DLL_Node_t;

/* ===== Node handlers ==== */
typedef unsigned int (*uNodePrintHandle)(DLL_Node_t *);
typedef unsigned int (*uDataCopyHandle)(DLL_Node_t *, void *);
typedef unsigned int (*uNodeSwapHandle)(DLL_Node_t *, DLL_Node_t *);
typedef unsigned int (*uNodeSearchKey)(DLL_Node_t *, void *);
typedef unsigned int (*uNodeCompareKey)(DLL_Node_t *, DLL_Node_t *);
typedef unsigned int (*uNodeDestoryHandle)(DLL_Node_t *);

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
DLL_Node_t * DLL_Search(DLinkedList_t * self, uNodeSearchKey key, void * serach_args);

/*  displays a given node   */
void DLL_NodePrint(DLL_Node_t * node, uNodePrintHandle display_func);

/*  print linked list   */
void DLL_ListPrint(DLinkedList_t * self, uNodePrintHandle display_func);

/** @TODO*/
/*  copy node data from a source node to a given destination container */
void DLL_NodeDataCopy(DLL_Node_t * src_node, void * dst_cont);

/** @TODO*/
/** swap 2 nodes */
void DLL_SwapNodes(DLL_Node_t * rnode, DLL_Node_t *lnode, uNodeSwapHandle swap_handle);

/** @TODO*/
/*  compare 2 nodes */
int DLL_NodeCompare(DLL_Node_t *rnode, DLL_Node_t * lnode, uNodeCompareKey compare_key);

/*  destroys a node */
void DLL_NodeTearDown(DLL_Node_t * node);

/*  destroys a linked list   */
void DLL_ListTearDown(DLinkedList_t * self);

#endif // _DLINKED_LIST_H_

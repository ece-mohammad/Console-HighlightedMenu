#include <stdio.h>
#include <stdlib.h>
#include "dlinkedlist.h"


/*  initialize LinkedList   */
DLinkedList_t * DLL_Initialize(void)
{
    DLinkedList_t * new_list = (DLinkedList_t *)calloc(sizeof(DLinkedList_t), 1);

    if (new_list)
    {
        new_list->head = NULL;
        new_list->tail = NULL;
        new_list->list_size = 0;
    }   /*  end if  */

    return new_list;
}

/*  create a new node in Linked List*/
DLL_Node_t * DLL_CreateNode(void * node_data)
{
    DLL_Node_t * new_node = (DLL_Node_t *) calloc(sizeof(DLL_Node_t), 1);

    if (new_node)
    {
        new_node->data = node_data;
        new_node->next_node = NULL;
        new_node->prev_node = NULL;
    }   /*  end if  */
    return new_node;
}

/*  add a new node to the end of the list  */
void DLL_AddNode(DLinkedList_t * self, DLL_Node_t * node)
{
    /*  if first node to add    */
    if (self->list_size == 0)
    {
        self->head = self->tail = node;
        node->next_node = node->prev_node = NULL;
    }
    else
    {
        self->tail->next_node = node;
        node->prev_node = self->tail;
        node->next_node = NULL;
        self->tail = node;
    }   /*  end if  */

    /*  update list size    */
    self->list_size++;
}

/*  deletes a node from the list  */
void DLL_DeleteNode(DLinkedList_t * self, unsigned int index)
{
    /*  exit if index > list size   */
    if ((index >= self->list_size) || (self->list_size == 0))
    {
        return;
    }   /*  end if  */

    if (index == 0)
    {
        if (self->list_size == 1)
        {
            DLL_NodeTearDown(self->head);
            self->head = NULL;
            self->tail = NULL;
        }
        else
        {
            self->head = self->head->next_node;
            DLL_NodeTearDown(self->head->prev_node);
            self->head->prev_node = NULL;
        }   /*  end if  */
    }
    else
    {
        if (index == (self->list_size - 1))
        {
            self->tail = self->tail->prev_node;
            DLL_NodeTearDown(self->tail->next_node);
            self->tail->next_node = NULL;
        }
        else
        {

            DLL_Node_t * current_node = self->head;

            while (index--)
            {
                current_node = current_node->next_node;
            }   /*  end index   */

            /*  previous node next_node points to current node's next_node  */
            current_node->prev_node->next_node = current_node->next_node;

            /*  next node's prev_node points to current node's prev_node    */
            current_node->next_node->prev_node = current_node->prev_node;

            /*  delete current node */
            DLL_NodeTearDown(current_node);

        }   /*  end if  */

    }   /*  end if  */

    /*  decrement list size */
    self->list_size--;
}

/*  insert a node in the list   */
void DLL_InsertNode(DLinkedList_t * self, DLL_Node_t * node, unsigned int index)
{
    if (index == 0)
    {
        if (self->list_size == 0)
        {
            DLL_AddNode(self, node);
            self->list_size--;
        }
        else
        {
            self->head->prev_node = node;
            node->prev_node = NULL;
            node->next_node = self->head;
            self->head = node;
        }   /*  end if  */
    }
    else
        if (index >= self->list_size)
        {
            DLL_AddNode(self, node);
            /*  compensate for incrementing array size in AddNode   */
            self->list_size--;
        }
        else
        {
            DLL_Node_t * current_node = self->head;

            while (index--)
            {
                current_node = current_node->next_node;
            }   /*  end while   */

            /*  current next_node points to the next_node of the previous node  */
            current_node->prev_node->next_node = node;
            current_node->prev_node = node;

            node->next_node = current_node;
            node->prev_node = current_node->prev_node;

        }   /*  end if  */

    /*  increment link size */
    self->list_size++;
}

/*  search for a node in the list   */
DLL_Node_t * DLL_Search(DLinkedList_t * self, uNodeSearchKey key, void * search_args)
{
    DLL_Node_t * current_node = self->head;

    while (current_node)
    {
        if (key(current_node, search_args))
        {
            return current_node;
        }   /*  end if  */

        current_node = current_node->next_node;
    }   /*  end while   */

    return current_node;
}

/*  displays a given node   */
void DLL_NodePrint(DLL_Node_t * node, uNodePrintHandle display_func)
{
    if(node)
    {
        display_func(node);
    }   /*  end if  */
}

/*  print linked list   */
void DLL_ListPrint(DLinkedList_t * self, uNodePrintHandle display_func)
{
    DLL_Node_t * current_node = self->head;
    while (current_node)
    {
        DLL_NodePrint(current_node, display_func);
        current_node = current_node->next_node;
    }   /*  end while   */
}

/** @TODO*/
/*  copy node data from a source node to a given destination container */
void DLL_NodeDataCopy(DLL_Node_t * src_node, void * dst_cont, uDataCopyHandle data_copy_handle)
{
    if(dst_cont)
    {
        data_copy_handle(src_node, dst_cont);
    }   /*  end if  */
}

/** @TODO*/
/** swap 2 nodes */
void DLL_SwapNodes(DLL_Node_t * rnode, DLL_Node_t *lnode, uNodeSwapHandle swap_handle)
{
    swap_handle(rnode, lnode);
}

/** @TODO*/
/*  compare 2 nodes */
int DLL_NodeCompare(DLL_Node_t *rnode, DLL_Node_t * lnode, uNodeCompareKey compare_key)
{
    return compare_key(rnode, lnode);
}

/*  destroys a node */
void DLL_NodeTearDown(DLL_Node_t * node)
{
    node->next_node = NULL;
    node->prev_node = NULL;
    node->data = NULL;
    free(node);
}

/*  destroys a linked list   */
void DLL_ListTearDown(DLinkedList_t * self)
{
    DLL_Node_t * current_node;

    while (self->head != NULL)
    {
        current_node = self->head;
        self->head = self->head->next_node;
        free(current_node);

    }   /*  end while   */
}

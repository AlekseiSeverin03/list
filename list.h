
// list.h

#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H


#include <string.h>
#include <math.h>
#include <assert.h>
#include "graph_dump.h"



const int MAX_N_ELEM = 1000;
const int POISON     = 333;


typedef int elem_t;


typedef struct 
{
	elem_t  data;
	int     next;
	int     prev;
}					elem_list;


typedef struct
{
	int        free;
	int        head;
	int        tail;
	int        size;
	int        id_last_insert_elem;
	elem_list  elements[MAX_N_ELEM];
	elem_list  buffer[MAX_N_ELEM];
}										list_t;


int ListCtor      (list_t *list);
int ListInsert    (list_t *list, int pos_after, elem_t data);
int ListDelete 	  (list_t *list, int pos);
int LinealList    (list_t *list);
int DumpList   	  (list_t *list, int n_elem_dp);
int GraphDumpList (list_t *list, int n_elem_dp);

int MakeInfoList  (list_t *list);



#define DATA(n_elem_list)  list->elements[n_elem_list].data
#define NEXT(n_elem_list)  list->elements[n_elem_list].next
#define PREV(n_elem_list)  list->elements[n_elem_list].prev
#define FREE 			   list->free
#define HEAD               list->head
#define TAIL               list->tail
#define SIZE               list->size
#define LAST_INSERT        list->id_last_insert_elem

#define DATA_(n_elem_list)  list.elements[n_elem_list].data
#define NEXT_(n_elem_list)  list.elements[n_elem_list].next
#define PREV_(n_elem_list)  list.elements[n_elem_list].prev
#define FREE_  				list.free
#define HEAD_               list.head
#define TAIL_               list.tail
#define SIZE_               list.size
#define LAST_INSERT_        list.id_last_insert_elem

#define MODE         node->mode
#define NAME_NODE    node->name_node
#define NAME         node->name
#define NAME_FROM    node->name_from
#define NAME_TO      node->name_to
#define SHAPE        node->shape
#define F_COLOR      node->fillcolor


#endif  // INCLUDE_LIST_H


/*  SAUVAGE Tao
	19/09/11
	DList:
		Declaration of double linked list datatype
*/

#ifndef DEF_DLIST
#define DEF_DLIST

#include <stdlib.h>
#include <stdio.h> /* Debug only */

/* Record of one element */
typedef struct element
{
	void* d; /* Data of the element */
	struct element* next; /* Pointer to the next element */
	struct element* prev; /* Pointer to the previous element */
} Element;

/* Record of the head list */
typedef struct struct_dlist
{
	unsigned int length; /* Size of the list */
	struct element* head; /* Pointer to the first element of the list */
	struct element* tail; /* Pointer to the last element of the list */
} Struct_dlist;

typedef Struct_dlist* DList;

/* Creator & destructor */
DList create_list(void);
void delete_list(DList l);
/* Access methods */
void* value_of(DList l, unsigned int n);
void* head_value(DList l);
void* tail_value(DList l);
unsigned int length_list(DList l);
/* Modifiers */
DList insert_of(DList l, void* data, unsigned int n);
DList insert_head(DList l, void* data);
DList insert_tail(DList l, void* data);
DList remove_of(DList l, unsigned int n);
DList remove_head(DList l);
DList remove_tail(DList l);
/* Debug */
void print_list(DList l);

#endif


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
	int key; /* Data of the element */
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
void delete_list(DList);
/* Access methods */
Boolean is_null(void*);
Boolean is_empty(DList);
int value_of(DList, unsigned int);
int head_value(DList);
int tail_value(DList);
unsigned int length_list(DList);
/* Modifiers */
DList insert_of(DList, int, unsigned int);
DList insert_head(DList, int);
DList insert_tail(DList, int);
DList remove_of(DList, unsigned int);
DList remove_head(DList);
DList remove_tail(DList);
/* Debug */
void print_list(DList);

#endif


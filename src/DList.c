/*  SAUVAGE Tao
	19/10/11
	DList:
		Implementation of double linked list datatype
*/

#include <stdlib.h>
#include <stdio.h>/* Debug only */
#include "../include/utils.h"
#include "../include/DList.h"

/* Creator & destructor */
/*  Return: empty double linked list
	Data: nothing
	Process: Allocate a new DList element and initialize it */
DList create_list(void)
{
	DList l = NULL;
	l = (DList) calloc(1, sizeof(Struct_dlist));

	if(!is_empty(l)) /* If the allocation succeeded */
	{
		l->head = NULL;
		l->tail = NULL;
		l->length = 0;
	}

	return l;
}

/*  Return: nothing
	Data: list to delete
	Process: Travers the list to free each element */
void delete_list(DList l)
{
	Element* p = NULL;
	Element* tmp = NULL;

	if(!is_empty(l))
	{
		p = l->head;
		/* While we haven't reached the end of the list */
		while(!is_empty(p))
		{
			tmp = p; /* We save the current element into the buffer */
			p = p->next; /* We switch to the next element */
            free(tmp); /* And we free the buffer */
			tmp = NULL;
		}
		free(l); /* Finally we free the record of the list */
		l = NULL;
	}
}

/* Access methods */
/*  Result: data of the n-th element of the list
	Data: list to analyse
		  index of the element that we are looking for
	Process: if n is lower or equal than length/2, we start from the
	begin of the list. Otherwise, we start from the end. */
void* value_of(DList l, unsigned int n)
{
	unsigned int i = 1, k = 0;
	Element* p = NULL;

	if(!is_empty(l))
	{
		/* If n belongs to the interval [1, length] */
		if(n > 1 && n < l->length)
		{
		    n = n - 1;
			if(n <= (l->length/2)) /* We start from the begin */
			{
				p = l->head;
				while(i < n + 1) /* We reach the right element */
				{
					p = p->next;
					i = i + 1;
				}
				return p->d;
			}
			else /* Otherwise we start from the end */
			{
				p = l->tail;
				k = l->length - n ;
				while(i < k)
				{
					p = p->prev;
					i = i + 1;
				}
				return p->d;
			}
		}
		else if(n == 1)
            return head_value(l);
        else
            return tail_value(l);
	}
	return NULL;
}

/*  Result: data of the first element of the list
	Data: list to analyse
	Process: We go back to the first element and return the data */
void* head_value(DList l)
{
	Element* p = NULL;

	if(!is_empty(l))
	{
		p = l->head;
		return p->d;
	}
	return NULL;
}

/*  Result: data of the last element of the list
	Data: list to analyse
	Process: We go to the last element and return the data */
void* tail_value(DList l)
{
	Element* p = NULL;

	if(!is_empty(l))
	{
		p = l->tail;
		return p->d;
	}

	return NULL;
}

/*  Result: length of the list
	Data: list to analyse
	Process: Use the property of the list to return the length */
unsigned int length_list(DList l)
{
	return (!is_empty(l)) ? l->length : 0;
}

/* Modifiers */
/*  Result: new list with a new element
	Data: list to modify
		  data of the new element
		  index of the position of the new element
	Process: travers the list to reach the n-element
	and insert the the new element */
DList insert_of(DList l, void* data, unsigned int n)
{
	Element* p = NULL;
	Element* q = NULL;
	Element* tmp = NULL;
	unsigned int i = 1, k = 0;

	p = (Element*) calloc(1, sizeof(Element));
	if(!is_empty(p))
	{
		p->next = NULL;
		p->prev = NULL;
		p->d = data;
	}

	if(is_empty(l))
	{
		l->head = p;
		l->tail = p;
		l->length = 1;
		return l;
	}
	else
	{
		if(n >= l->length)
			return insert_tail(l, data);
        else if(n == 1)
            return insert_head(l, data);
		else
		{
		    n = n - 1;
			if(n <= (l->length/2))
			{
				q = l->head;
				while(i < n)
				{
					q = q->next;
					i = i + 1;
				}
				tmp = q->next;
				q->next = p;
				p->prev = q;
				tmp->prev = p;
				p->next = tmp;
			}
			else
			{
				q = l->tail;
				k = l->length - n;
				while(i < k)
				{
					q = q->prev;
					i = i + 1;
				}
				tmp = q->prev;
				q->prev = p;
				p->next = q;
				tmp->next = p;
				p->prev = tmp;
			}
			l->length = l->length + 1;
			return l;
		}
	}
}

/*  Result: list with a new element at the begin
	Data: list to modify
	Process: add a new element at the begin of the list */
DList insert_head(DList l, void* data)
{
	Element* p = NULL;
	p = (Element*) calloc(1, sizeof(Element));

    if(!is_empty(p))
    {
        if(!is_empty(l))
        {
            if(l->length >= 1)
            {
                p->prev = NULL;
                p->d = data;
                p->next = l->head;
                l->head->prev = p;
                l->head = p;
                l->length = l->length + 1;
                return l;
            }
            else
            {
                p->prev = NULL;
                p->next = NULL;
                p->d = data;
                l->head = p;
                l->tail = p;
                l->length = l->length + 1;
                return l;
            }
        }
    }
    return create_list();
}

/*  Result: list with a new element at the end
	Data: list to modify
	Process: add a new element at the end of the list */
DList insert_tail(DList l, void* data)
{
	Element* p = NULL;
	p = (Element*) calloc(1, sizeof(Element));

	if(!is_empty(p) && !is_empty(l))
	{
		p->next = NULL;
		p->d = data;
		l->tail->next = p;
		p->prev = l->tail;
		l->tail = p;
		l->length = l->length + 1;
		return l;
	}
	return create_list();
}

/*  Result: list without the n-th element
	Data: list to modify
		  index of the element which have to be deleted
	Process: travers the list to find the n-th element
	which have to be deleted */
DList remove_of(DList l, unsigned int n)
{
	Element* p = NULL;
	Element* tmp = NULL;
	unsigned int i = 1, k = 0;

	if(is_empty(l)) /* If the list is empty... */
		return create_list(); /* We return a new list */
	else
	{
	    if(n <= l->length) /* n belongs to [0, l->length] */
	    {
	        n = n - 1; /* To access to the n-th element */
			/* It's more efficient to travers the list from the beginning
			if n <= (l->length/2) */
	        if(n <= (l->length/2))
            {
                p = l->head; /* We start from the beginning */
                while(i <= n) /* We reach the rigth element */
                {
                    p = p->next;
                    i = i + 1;
                }
            }
			/* Else it's more efficient to start from the end of the list */
            else
            {
                p = l->tail; /* We start from the end */
                k = l->length - n;
                while(i <= k) /* We reach the right element */
                {
                    p = p->prev;
                    i = i + 1;
                }
            }
			tmp = p->prev; /* We save the previous element */
			/* We pass through the element we want to remove */
            tmp->next = p->next;
            tmp = p->next;
            tmp->prev = p->prev;
            free(p); /* We free the element */
            p = NULL;
            l->length = l->length - 1; /* The list has one element less */
            return l;
	    }
		else /* Else we force n to be equal to l->length */
            return remove_tail(l);
	}
}

/*  Result: list without the first element
	Data: list to modify
	Process: remove the head */
DList remove_head(DList l)
{
	Element* p = NULL;

	if(!is_empty(l))
	{
		p = l->head;
		/* New head is the next element of the previous last head of the list */
		l->head = l->head->next;
		free(p); /* We free the element */
		p = NULL;
		/* Previous element of the new head is nothing (i.e NULL) */
		l->head->prev = NULL;
		l->length = l->length - 1; /* The list has one element less */
	}
	return l;
}

/*  Result: list without the last element
	Data: list to modify
	Process: remove the tail */
DList remove_tail(DList l)
{
	Element* p = NULL;

	if(!is_empty(l))
	{
		p = l->tail;
		/* New tail is the previous element of the previous last element of the list */
		l->tail = l->tail->prev;
		free(p);
		p = NULL;
		/* New next element of the new tail is nothing (i.e NULL) */
		l->tail->next = NULL;
		l->length = l->length - 1; /* The list has one element less */
	}
	return l;
}

/* Debug */
/* Print the list as an array of integer */
void print_list(DList l)
{
    Element* p = NULL;
    int i = 1;

    p = l->head;
    for(i = 1; i <= l->length; i = i + 1)
    {
        printf("%d ", (int)(int*)p->d);
        p = p->next;
    }
    printf("\n");
}



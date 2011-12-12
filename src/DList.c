/*  SAUVAGE Tao
	19/10/11
	DList:
		Implementation of double linked list datatype
*/

#include <stdlib.h>
#include <stdio.h> /* Debug only */
#include <utils.h>
#include <DList.h>

/* Creator & destructor */
/*  Return: empty double linked list
	Data: nothing
	Process: allocate a new DList element and initialize it */
DList create_list(void)
{
	DList list = NULL;
	list = (DList) calloc(1, sizeof(Struct_dlist));

	if(!is_empty(list)) /* If the allocation succeeded */
	{
		list->head = NULL;
		list->tail = NULL;
		list->length = 0;
	}

	return list;
}

/*  Return: nothing
	Data: list to delete
	Process: Travers the list to free each element */
void delete_list(DList input)
{
	Element* current = NULL;
	Element* parent = NULL;

	if(!is_empty(input))
	{
		current = input->head;
		/* While we haven't reached the end of the list */
		while(!is_empty(current))
		{
			parent = current; /* We save the current element into the buffer */
			current = current->next; /* We switch to the next element */
            free(parent); /* And we free the buffer */
			parent = NULL;
		}
		free(input); /* Finally we free the record of the list */
		input = NULL;
	}
}

/* Access methods */
/*  Result: data of the n-th element of the list
	Data: list to analyse
		  index of the element that we are looking for
	Process: if n is lower or equal than length/2, we start from the
	begin of the list. Otherwise, we start from the end. */
int value_of(DList input, unsigned int n)
{
	unsigned int i = 1, k = 0;
	Element* current = NULL;

	if(!is_empty(input))
	{
		/* If n belongs to the interval [1, length] */
		if(n > 1 && n < input->length)
		{
		    n = n - 1;
			if(n <= (input->length/2)) /* We start from the begin */
			{
				current = input->head;
				while(i < n + 1) /* We reach the right element */
				{
					current = current->next;
					i = i + 1;
				}
				return current->key;
			}
			else /* Otherwise we start from the end */
			{
				current = input->tail;
				k = input->length - n ;
				while(i < k)
				{
					current = current->prev;
					i = i + 1;
				}
				return current->key;
			}
		}
		else if(n == 1)
            return head_value(input);
        else
            return tail_value(input);
	}
	return 0;
}

/*  Result: data of the first element of the list
	Data: list to analyse
	Process: We go back to the first element and return the data */
int head_value(DList input)
{
	Element* current = NULL;

	if(!is_empty(input))
	{
		current = input->head;
		return current->key;
	}
	return 0;
}

/*  Result: data of the last element of the list
	Data: list to analyse
	Process: We go to the last element and return the data */
int tail_value(DList input)
{
	Element* current = NULL;

	if(!is_empty(input))
	{
		current = input->tail;
		return current->key;
	}

	return 0;
}

/*  Result: length of the list
	Data: list to analyse
	Process: Use the property of the list to return the length */
unsigned int length_list(DList input)
{
	return (!is_empty(input)) ? input->length : 0;
}

/* Modifiers */
/*  Result: new list with a new element
	Data: list to modify
		  data of the new element
		  index of the position of the new element
	Process: travers the list to reach the n-element
	and insert the the new element */
DList insert_of(DList input, int value, unsigned int n)
{
	Element* newElem = NULL;
	Element* current = NULL;
	Element* parent = NULL;
	unsigned int i = 1, k = 0;

	newElem = (Element*) calloc(1, sizeof(Element));
	if(!is_empty(newElem))
	{
		newElem->next = NULL;
		newElem->prev = NULL;
		newElem->key = value;
	}

	if(is_empty(input))
	{
		input->head = newElem;
		input->tail = newElem;
		input->length = 1;
		return input;
	}
	else
	{
		if(n >= input->length)
			return insert_tail(input, value);
        else if(n == 1)
            return insert_head(input, value);
		else
		{
		    n = n - 1;
			if(n <= (input->length/2))
			{
				current = input->head;
				while(i < n)
				{
					current = current->next;
					i = i + 1;
				}
				parent = current->next;
				current->next = newElem;
				newElem->prev = current;
				parent->prev = newElem;
				newElem->next = parent;
			}
			else
			{
				current = input->tail;
				k = input->length - n;
				while(i < k)
				{
					current = current->prev;
					i = i + 1;
				}
				parent = current->prev;
				current->prev = newElem;
				newElem->next = current;
				parent->next = newElem;
				newElem->prev = parent;
			}
			input->length = input->length + 1;
			return input;
		}
	}
}

/*  Result: list with a new element at the begin
	Data: list to modify
	Process: add a new element at the begin of the list */
DList insert_head(DList input, int value)
{
	Element* newElem = NULL;
	newElem = (Element*) calloc(1, sizeof(Element));

    if(!is_empty(newElem))
    {
        if(!is_empty(input))
        {
            if(input->length >= 1)
            {
                newElem->prev = NULL;
                newElem->key = value;
                newElem->next = input->head;
                input->head->prev = newElem;
                input->head = newElem;
                input->length = input->length + 1;
                return input;
            }
            else
            {
                newElem->prev = NULL;
                newElem->next = NULL;
                newElem->key = value;
                input->head = newElem;
                input->tail = newElem;
                input->length = input->length + 1;
                return input;
            }
        }
    }
    return create_list();
}

/*  Result: list with a new element at the end
	Data: list to modify
	Process: add a new element at the end of the list */
DList insert_tail(DList input, int value)
{
	Element* newElem = NULL;
	newElem = (Element*) calloc(1, sizeof(Element));

	if(!is_empty(newElem) && !is_empty(input))
	{
		newElem->next = NULL;
		newElem->key = value;
		input->tail->next = newElem;
		newElem->prev = input->tail;
		input->tail = newElem;
		input->length = input->length + 1;

		return input;
	}
	return create_list();
}

/*  Result: list without the n-th element
	Data: list to modify
		  index of the element which have to be deleted
	Process: travers the list to find the n-th element
	which have to be deleted */
DList remove_of(DList input, unsigned int n)
{
	Element* current = NULL;
	Element* parent = NULL;
	unsigned int i = 1, k = 0;

	if(is_empty(input)) /* If the list is empty... */
		return create_list(); /* We return a new list */
	else
	{
	    if(n <= input->length) /* n belongs to [0, input->length] */
	    {
	        n = n - 1; /* To access to the n-th element */
			/* It's more efficient to travers the list from the beginning
			if n <= (input->length/2) */
	        if(n <= (input->length/2))
            {
                current = input->head; /* We start from the beginning */
                while(i <= n) /* We reach the rigth element */
                {
                    current = current->next;
                    i = i + 1;
                }
            }
			/* Else it's more efficient to start from the end of the list */
            else
            {
                current = input->tail; /* We start from the end */
                k = input->length - n;
                while(i <= k) /* We reach the right element */
                {
                    current = current->prev;
                    i = i + 1;
                }
            }
			parent = current->prev; /* We save the previous element */
			/* We pass through the element we want to remove */
            parent->next = current->next;
            parent = current->next;
            parent->prev = current->prev;
            free(current); /* We free the element */
            current = NULL;
            input->length = input->length - 1; /* The list has one element less */
            return input;
	    }
		else /* Else we force n to be equal to input->length */
            return remove_tail(input);
	}
}

/*  Result: list without the first element
	Data: list to modify
	Process: remove the head */
DList remove_head(DList input)
{
	Element* current = NULL;

	if(!is_empty(input))
	{
		current = input->head;
		/* New head is the next element of the previous last head of the list */
		input->head = input->head->next;
		free(current); /* We free the element */
		current = NULL;
		/* Previous element of the new head is nothing (i.e NULL) */
		input->head->prev = NULL;
		input->length = input->length - 1; /* The list has one element less */
	}
	return input;
}

/*  Result: list without the last element
	Data: list to modify
	Process: remove the tail */
DList remove_tail(DList input)
{
	Element* current = NULL;

	if(!is_empty(input))
	{
		current = input->tail;
		/* New tail is the previous element of the previous last element of the list */
		input->tail = input->tail->prev;
		free(current);
		current = NULL;
		/* New next element of the new tail is nothing (i.e NULL) */
		input->tail->next = NULL;
		input->length = input->length - 1; /* The list has one element less */
	}
	return input;
}

/* Debug */
/* Print the list as an array of integer */
void print_list(DList input)
{
    Element* current = NULL;
    int i = 1;

    current = input->head;
    for(i = 1; i <= input->length; i = i + 1)
    {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}


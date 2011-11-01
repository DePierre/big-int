/*  SAUVAGE Tao
	23/10/11
	DList:
		Implementation of big integer datatype
*/

#include <stdlib.h>
#include "../include/utils.h"
#include "../include/DList.h"
#include "../include/BigInt.h"


/* Creator & destructor */
/*  Result: empty big integer
	Data: nothing
	Process: Allocate a new BigInteger element and initialize it */
BigInteger create_big_int(void)
{
	BigInteger b = NULL;
	b = (BigInteger) calloc(1, sizeof(Struct_big_integer));

	if(!is_empty(b))
	{
		b->sign = 0;
		b->l = create_list();
		return b;
	}
	return NULL;
}

/*  Result: nothing
	Data: big integer to delete
	Process: use list datatype's destructor  and free the big integer */
void delete_big_int(BigInteger b)
{
	delete_list(b->l);
	free(b);
	b = NULL;
}

/* Access methods */
inline Boolean isNull(BigInteger b)
{
	return is_empty(b);
}

inline Boolean signBigInt(BigInteger b)
{
	return (is_empty(b->l)) ? 0 : (b->sign == 1) ? 1 : -1;
}

/*  Result: true if a == b, false otherwise
	Data: two big integers which have to be compare
	Process: we compare if the 2 BigInt have the same sign, then we
	compare if there is the same number of elements into the 2 lists of
	numbers and then, we travers the 2 list to compare each value of
	each list, otherwise, the 2 BigInt aren't equals */
Boolean equalsBigInt(BigInteger a, BigInteger b)
{
	Element *pa = NULL, *pb = NULL;

	/* If the 2 BigInt aren't empty */
	if(!isNull(a) && !isNull(b))
	{
		/* If they have the same sign but not zero */
		if((a->sign == b->sign) && a->sign != 0)
		{
			/* If the 2 list of both aren't empty too */
			if(!is_empty(a->l) && !is_empty(b->l))
			{
				/* If there is the same number of element into both list */
				if(a->l->length == b->l->length)
				{
					pa = a->l->tail;
					pb = b->l->tail;
					while(!is_empty(pa->prev) && !is_empty(pa->prev) && (pa->d == pb->d))
					{
						pa = pa->prev;
						pb = pb->prev;
					}
					/* We check if we stop because of there is no more element, or because
					there is no more equality */
					if(pa->d == pb->d)
						return TRUE; /* Then they are equals */
				}
			}
		}
		/* If both sign are equals to 0, a == b == 0 */
		else if(a->sign == 0 && b->sign == 0)
			return TRUE;
	}

	return FALSE; /* Otherwise they aren't equals */
}

/*  Result: 0 if a = b
			1 if a > b
			-1 if a < b
	Data: 2 BigInt which have to be compare
	Process: check each property of both BigInt, if they
	are equals, we use equalsBigInt, otherwise, we return
	the rigth value */
int compareBigInt(BigInteger a, BigInteger b)
{
	Element *pa = NULL, *pb = NULL;
	if(!isNull(a) && !isNull(b))
	{
		if(!is_empty(a->l) && !is_empty(b->l))
		{
			if(equalsBigInt(a, b))
				return 0;
			else
			{
				/* a > 0 and b < 0 => a > b */
				if(a->sign > b->sign)
					return 1;
				/* a < 0 and b > 0 => a < b */
				else if(a->sign < b->sign)
					return -1;
				/* if a > 0 and b > 0 OR a < 0 and b < 0 */
				else
				{
					/* if a has more element than b => a > b */
					if(a->l->length > b->l->length)
						return 1;
					/* else if a has less element than b => a < b */
					else if(a->l->length < b->l->length)
						return -1;
					/* else we have to reach the first element which is different
					between a and b */
					else
					{
						pa = a->l->tail;
						pb = b->l->tail;
						while(!is_empty(pa->prev) && !is_empty(pb->prev) && (pa->d == pb->d))
						{
							pa = pa->prev;
							pb = pb->prev;
						}
						/* a > b */
						if(pa->d > pb->d)
							return 1;
						/* a < b */
						else /* We don't check if they are equals because we already did it */
							return -1;
					}
				}
			}
		}
		else if(!is_empty(a->l) && is_empty(b->l))
			return 1;
		else if(is_empty(a->l) && !is_empty(b->l))
			return -1;
	}
	else if(!isNull(a) && isNull(b))
		return 1;
	else if(isNull(a) && !isNull(b))
		return -1;

	return 0;
}

/* Modifiers */
/*  Result: new big integer
	Data: number as a string
	Process: split the string into 4th characters parts */
BigInteger newBigInteger(char* str)
{
	char tmp[NBDIGITS + 1];
	int length = 0, l = 0, r = 0, c = 0, i = 0;
	BigInteger b = NULL;
	b = create_big_int();

	if(!is_empty(b))
	{
		length = strlen(str);
		r = length % NBDIGITS; /* Rest of the length */
		l = length - r; /* New string length multiple of NBDIGITS */
		/* Copy from the end of the string to the begin and stop
		if we reach the biggest mutliple of NBDIGITS of the list size */
		for(i = NBDIGITS; i <= l; i = i + NBDIGITS)
		{
			memcpy(tmp, &str[length - i], NBDIGITS);
			tmp[NBDIGITS] = '\0';
			c = atoi(tmp);
			/* Create new element which contains the group of NBDIGITS digits */
			b->l = insert_head(b->l, (void*)c);
		}
		/* If the length of the list was not already a multiple of NBDIGITS */
		if( r != 0)
		{
			/* Copy the rest of the list */
			memcpy(tmp, str, r);
			tmp[r] = '\0';
			c = atoi(tmp);
			b->l = insert_head(b->l, (void*)c);
		}
		b->sign = 1;
	}

	return b;
}

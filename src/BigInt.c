/*  SAUVAGE Tao
	23/10/11
	DList:
		Implementation of big integer datatype
*/

#include <stdlib.h>
#include <ctype.h>
#include <utils.h>
#include <DList.h>
#include <BigInt.h>


/* Creator & destructor */
/*  Result: empty big integer
	Data: nothing
	Process: Allocate a new BigInteger element and initialize it */
BigInteger create_big_int(void)
{
	BigInteger bigInt = NULL;
	bigInt = (BigInteger) calloc(1, sizeof(Struct_big_integer));

	if(!is_empty(bigInt))
	{
		bigInt->sign = 0;
		bigInt->list = create_list();
		return bigInt;
	}
	return NULL;
}

/*  Result: nothing
	Data: big integer to delete
	Process: use list datatype's destructor  and free the big integer */
void delete_big_int(BigInteger input)
{
	delete_list(input->list);
    free(input);
	input = NULL;
}

/* Private methods */
/*  Result: the number of elements of the smallest big-integer
	Data: two big integers which have to be compare
	Process: compare firstBigInt->list->length and secondBigInt->list->length */
int get_min_loops(BigInteger firstBigInt, BigInteger secondBigInt)
{
	int minLoops = 0;
	if(!isNull(firstBigInt) && !isNull(secondBigInt))
		if(!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
			minLoops = (firstBigInt->list->length < secondBigInt->list->length) ? firstBigInt->list->length : secondBigInt->list->length;

	return minLoops;
}

/*  Result: the number of elements of the biggest big-integer
	Data: two big integers which have to be compare
	Process: compare firstBigInt->list->length and secondBigInt->list->length */
int get_max_loops(BigInteger firstBigInt, BigInteger secondBigInt)
{
	int maxLoops = 0;
	if(!isNull(firstBigInt) && !isNull(secondBigInt))
		if(!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
			maxLoops = (firstBigInt->list->length > secondBigInt->list->length) ? firstBigInt->list->length : secondBigInt->list->length;

	return maxLoops;
}

/*  Result: big integer without any zero at the left
	Data: big integer which has to be processed
	Process: travers the list from the end and delete each element if
	it's equal to zero. Stop at the first occurence of a non-zero element */
BigInteger delete_left_zero(BigInteger input)
{
	Element *current = NULL;
	
	if(!isNull(input) && !is_null(input->list))
	{
		current = input->list->tail;
		while(current->key == 0 && current != input->list->head)
		{
			input->list = remove_tail(input_list);
			current = input->list->tail;
		}
	}

	return input;
}

/* Access methods */
Boolean isNull(BigInteger input)
{
	return is_empty(input);
}

int signBigInt(BigInteger input)
{
	return (is_empty(input->list)) ? 0 : (input->sign == 1) ? 1 : (input->sign == 0) ? 0 : -1;
}

/*  Result: true if a == b, false otherwise
	Data: two big integers which have to be compare
	Process: we compare if the 2 BigInt have the same sign, then we
	compare if there is the same number of elements into the 2 lists of
	numbers and then, we travers the 2 list to compare each value of
	each list, otherwise, the 2 BigInt aren't equals */
Boolean equalsBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
	Element *currentFirst = NULL, *currentSecond = NULL;

	/* If the 2 BigInt aren't empty */
	if(!isNull(firstBigInt) && !isNull(secondBigInt))
	{
		/* If they have the same sign but not zero */
		if((firstBigInt->sign == secondBigInt->sign) && firstBigInt->sign != 0)
		{
			/* If the 2 list of both aren't empty too */
			if(!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
			{
				/* If there is the same number of element into both list */
				if(firstBigInt->list->length == secondBigInt->list->length)
				{
					currentFirst = firstBigInt->list->tail;
					currentSecond = secondBigInt->list->tail;
					while(!is_empty(currentFirst->prev) && !is_empty(currentFirst->prev) && (currentFirst->key == currentSecond->key))
					{
						currentFirst = currentFirst->prev;
						currentSecond = currentSecond->prev;
					}
					/* We check if we stop because of there is no more element, or because
					there is no more equality */
					if(currentFirst->key == currentSecond->key)
						return TRUE; /* Then they are equals */
				}
			}
		}
		/* If both sign are equals to 0, a == b == 0 */
		else if(firstBigInt->sign == 0 && secondBigInt->sign == 0)
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
int compareBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
	Element *currentFirst = NULL, *currentSecond = NULL;
	if(!isNull(firstBigInt) && !isNull(secondBigInt))
	{
		if(!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
		{
			if(equalsBigInt(firstBigInt, secondBigInt))
				return 0;
			else
			{
				/* a > 0 and b < 0 => firstBigInt > b */
				if(firstBigInt->sign > secondBigInt->sign)
					return 1;
				/* a < 0 and b > 0 => a < b */
				else if(firstBigInt->sign < secondBigInt->sign)
					return -1;
				/* if a > 0 and b > 0 OR a < 0 and b < 0 */
				else
				{
					/* if a has more element than b => a > b */
					if(firstBigInt->list->length > secondBigInt->list->length)
						return 1;
					/* else if a has less element than b => a < b */
					else if(firstBigInt->list->length < secondBigInt->list->length)
						return -1;
					/* else we have to reach the first element which is different
					between a and b */
					else
					{
						currentFirst = firstBigInt->list->tail;
						currentSecond = secondBigInt->list->tail;
						while(!is_empty(currentFirst->prev) && !is_empty(currentSecond->prev) && (currentFirst->key == currentSecond->key))
						{
							currentFirst = currentFirst->prev;
							currentSecond = currentSecond->prev;
						}
						/* a > b */
						if(currentFirst->key > currentSecond->key)
							return 1;
						/* a < b */
						else /* We don't check if they are equals because we already did it */
							return -1;
					}
				}
			}
		}
		else if(!is_empty(firstBigInt->list) && is_empty(secondBigInt->list))
			return 1;
		else if(is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
			return -1;
	}
	else if(!isNull(firstBigInt) && isNull(secondBigInt))
		return 1;
	else if(isNull(firstBigInt) && !isNull(secondBigInt))
		return -1;

	return 0;
}

int* toIntArray(BigInteger input)
{
	int i = 0;
	int **bigIntStr = NULL;
	Elemt *current = NULL;
	
	if(!isNull(input))
	{
		*bigIntStr = calloc(input->list->length, sizeof(char*));
		if(bigIntStr != NULL)
		{
			current = input->list->tail;
			for(i = input->list->length; i > 0; i = i - 4)
			{
				*bigIntStr[i] = current->data % NBDIGITSPOW;
				*bigIntStr[i-1] = current->data % (NBDIGITSPOW / 10);
				*bigIntStr[i-2] = current->data % (NBDIGITSPOW / 100);
				*bigIntStr[i-3] = current->data % (NBDIGITSPOW / 1000);
				
				current = current->prev;
			}
		}
	}
	
	return *bigIntStr;
}
	
/* Arithmetic methods */
/*  Return: new big integer which is the sum of a and b
    Data: two big integers to sum
    Process: sum each element from both big integers */
BigInteger sumBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
    int currentSum = 0, i = 0, min = 0, max = 0, r = 0;
    BigInteger sum = create_big_int();
    Element *currentFirst = NULL, *currentSecond = NULL, *rest = NULL;

    if(!isNull(firstBigInt) && !isNull(secondBigInt))
    {
        /* -a + b <=> b - a */
        if(firstBigInt->sign == -1 && secondBigInt->sign == 1)
            return diffBigInt(secondBigInt, firstBigInt);
        /* a + (-b) <=> a - b */
        else if(firstBigInt->sign == 1 && secondBigInt->sign == -1)
            return diffBigInt(firstBigInt, secondBigInt);

        /* We compute the minimum number of loop to reach the end of the smallest big integer */
		min = get_min_loops(firstBigInt, secondBigInt);
		max = get_max_loops(firstBigInt, secondBigInt);

        currentFirst = firstBigInt->list->tail;
        currentSecond = secondBigInt->list->tail;

        for(i = 0; i < min; i = i + 1)
        {
            /* We sum both numbers */
            currentSum = currentFirst->key + currentSecond->key + r;
            /* We switch to the next elements */
            currentFirst = currentFirst->prev;
            currentSecond = currentSecond->prev;

            /* We save the deduction */
            r = currentSum / NBDIGITSPOW;
            /* We cast currentSum to a number with maximum 4 digits */
            currentSum = currentSum % NBDIGITSPOW;
            /* We insert the result into the new big int */
            sum->list = insert_head(sum->list, currentSum);
        }
        /* We save the position in the greatest big integer */
        rest = (i == firstBigInt->list->length) ? currentSecond : currentFirst;
        /* And we summ the rest of it */
        for(i = min; i < max; i = i + 1)
        {
            currentSum = rest->key + r;
            rest = rest->prev;

            r = currentSum / NBDIGITSPOW;
            currentSum = currentSum % NBDIGITSPOW;
            sum->list = insert_head(sum->list, currentSum);
        }
        /* If the deduction is not equal to zero we add it */
        if(r != 0)
            sum->list = insert_head(sum->list, r);
    }


    return delete_left_zero(sum);
}

/*  Return: new big integer which is the diff of a and b
    Data: two big integers to diff
    Process: diff each element from both big integers */
BigInteger diffBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
    int currentDiff = 0, i = 0, min = 0, max = 0;
    BigInteger diff = create_big_int();
    Element *currentFirst = NULL, *currentSecond = NULL, *rest = NULL;

    if((!isNull(firstBigInt) && !isNull(secondBigInt))
        && (!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list)))
    {
        min = get_min_loops(firstBigInt, secondBigInt);
        max = get_max_loops(firstBigInt, secondBigInt);

        diff->sign = compareBigInt(firstBigInt, secondBigInt);

        currentFirst = firstBigInt->list->tail;
        currentSecond = secondBigInt->list->tail;
        for(i = 0; i < min; i = i + 1)
        {
            if(currentFirst >= currentSecond)
            {
                currentDiff = currentFirst->key - currentSecond->key;
                printf("%d - %d = (%d)\n", currentFirst->key, currentSecond->key, currentDiff);
            }
            else
            {
                currentDiff = currentSecond->key - currentFirst->key;
                printf("%d - %d = (%d)\n", currentSecond->key, currentFirst->key, currentDiff);
            }
            diff->list = insert_head(diff->list, currentDiff);

            currentFirst = currentFirst->prev;
            currentSecond = currentSecond->prev;
        }
        /* We save the position in the greatest big integer */
        rest = (i == firstBigInt->list->length) ? currentSecond : currentFirst;
        for(i = min; i < max; i = i + 1)
        {
            currentDiff = rest->key;
            rest = rest->prev;
            diff->list = insert_head(diff->list, currentDiff);
        }

    }

    return delete_left_zero(diff);
}

/*  Return: new big integer which is the mul of a and b
    Data: two big integers to mul
    Process: mul each element from both big integers */
BigInteger mulBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
	int currentMul = 0, i = 0, j = 0, carry = 0, sign = 0;
	BigInteger mul = create_big_int();
	Element *currentGreatest = NULL, *currentLowest = NULL;
    BigInteger greatest = NULL, lowest = NULL;

	if(!isNull(firstBigInt) && !isNull(secondBigInt))
	{
		/* Special case : a = 0 or b = 0 */
		if(firstBigInt->sign == 0 || secondBigInt->sign == 0)
        {
			mul->list = insert_head(mul->list, 0);
            return mul;
        }
		else
		{
			if(!is_empty(firstBigInt->list) && !is_empty(secondBigInt->list))
			{
                sign = compareBigInt(firstBigInt, secondBigInt);
                if(sign == 1)
                {
                    greatest = firstBigInt;
                    lowest = secondBigInt;
                }
                else if(sign == -1)
                {
                    greatest = secondBigInt;
                    lowest = firstBigInt;
                }
				/* Special case : if b = 1, a * b = a */
				if(lowest->list->length == 1 && lowest->list->head->key == 1)
					return greatest;

				currentGreatest = greatest->list->tail;
				for(i = 0; i < greatest->list->length; i = i + 1)
				{
					currentLowest = lowest->list->tail;
					currentMul = 0;
					for(j = 0; j < lowest->list->length; j = j + 1)
					{
						currentMul = currentMul + currentGreatest->key * (currentLowest->key + carry);
                        /* DEBUG */
                        printf("%d * %d = (%d + %d)\n", currentGreatest->key, currentLowest->key, currentMul, carry);
						currentLowest = currentLowest->prev;
					}
					carry = currentMul / NBDIGITSPOW;
					currentMul = currentMul % NBDIGITSPOW;
					mul->list = insert_head(mul->list, currentMul);

					currentGreatest = currentGreatest->prev;
				}
                if(carry != 0)
                    mul->list = insert_head(mul->list, carry);
			}
		}
    }

	return delete_left_zero(mul);
}
/* Groups of functions for the division */
BigInteger product(BigInteger input, unsigned long k)
{
	BigInteger copy = NULL, unit = NULL;
	
	copy = fromBigIntegerToBigInteger(input);
	unit = fromUnsignedLongToBigInteger(k);
	
	mulBigInt(copy, unit);
	
	return copy;
}

BigInteger quotient(BigInteger input, unsigned long k)
{
	int i = 0, j = 0, m = 0, carry = 0, temp = 0, currentDiv = 0, currentPow = 10;
	BigInteger copy = NULL;
	Element *current = NULL;
	
	if(!isNull(input) && !is_empty(input->list))
	{
		copy = fromBigIntegerToBigInteger(input);
		
		m = input->list->length;
		current = copy->list->tail;
		for(i = m - 1; i >= 0; i = i - 1)
		{
			currentDiv = 0;
			currentPow = 10;
			for(j = 0; j < 4; j = j + 1)
			{
				temp = carry * NBDIGITSPOW + current->key / currentPow;
				currentDiv = currentDiv + temp / k;
				carry = temp % k;
				currentPow = currentPow * 10;
			}
			
			copy->list = insert_tail(copy->list, currentDiv);
			current = current->prev;
		}
	}
	
	return delete_left_zero(copy);
}
BigInteger remainder(BigInteger input, unsigned long k)
{
	int i = 0, j = 0, m = 0, carry = 0, currentPow = 10;
	BigInteger carry = NULL;
	Element *current = NULL;
	
	carry = create_big_integer();
	
	if(!isNull(carry) && !isNull(input) && !is_empty(input->list))
	{
		current = input->list->tail;
		
		m = input->list->length;
		for(i = m - 1; i >= 0; i = i - 1)
		{
			carry = 0;
			currentPow = 10;	
			for(j = 0; j < 4; j = j + 1)
				carry = carry + (carry * NBDIGITSPOW + current->key / currentPow) % k;		
			current = current->prev;
		}
	}
	
	return fromUnsignedLongToBigInteger(carry);
}

int trial_digit(BigInteger r, BigInteger d, int k, int m)
{
	int d2 = 0, km = 0, r3 = 0, temp = 0;
	
	if(!isNull(r) && !isNull(d) && !is_empty(r->list) && !is_empty(d->list))
	{
		/* Assuming { 2 <= m <= k+m <= w } */
		km = k + m;
		r3 = ((r->list->valueOf(km / 4) / pow(10, km % 4)) * NBDIGITSPOW + (r->list->valueOf((km - 1) / 4) / pow(10, (km - 1) % 4))) * NBDIGITSPIW + (r->list->valueOf((km - 2) / 4) / pow(10, (km - 2) % 4));
		d2 = (d->list->valueOf((m-1) / 4) / pow(10, (m-1) % 4)) * NBDIGITSPOW + (d->list->valueOf((m-2) / 4) / pow(10, (m-2) % 4))
		temp = (d2 == 0) ? 0 : r3 / d2;
	}
	
	return (temp <= NBDIGITSPOW - 1) ? temp : NBDIGITSPOW - 1;
}

Boolean smaller(BigInteger r, BigInteger dq, int k, int m)
{
	int i = m, j = 0;
	
	if(!isNull(r) && !isNull(dq) && !is_empty(r->list) && !is_empty(dq->list))
	{
		/* Assuming { r[k+m..k] < dq[m..0] } */
		while(i != j)
		{
			if((r->list->valueOf((i + k) / 4) / pow(10, (i + k) % 4)) != (dq->list->valueOf(i / 4) / pow(10, i % 4)))
				j = i;
			else
				i = i - 1;
		}
	}
	
	return ((r->list->valueOf((i + k) / 4) / pow(10, (i + k) % 4)) < (dq->list->valueOf(i / 4) / pow(10, i % 4))) ? TRUE : FALSE;
}

BigInteger difference(BigInteger r, BigInteger dq, int k, int m)
{
	int borrow = 0, diff = 0, i = 0, j = 0;
	BigInteger copyR = NULL;
	Element *current = NULL;
	
	copyR = fromBigIntegerToBigInteger(r);
	
	if(!isNull(r) && !isNull(dq) && !is_empty(r->list) && !is_empty(dq->list))
	{
		for(i = 0; i <= m; i = i + 1)
		{
			current = copyR->list->head;
			diff = r.number[i+k] - dq.number[i] - borrow + DIVIDENDRADIX;
			diff = (copyR->list->valueOf((i + k) / 4) / pow(10, (i + k) % 4)) - (dq->list->valueOf(i / 4) / pow(10, i % 4)) - borrow + NBDIGITSPOW;
			copyR->list = insert_of(copyR->list, diff % NBDIGITSPOW, i + k);
			for(j = 0; j < (i + k) / 4; j = j + 1)
				current = current->next;
			current->key = diff % NBDIGITSPOW * pow(10, (i + k) % 4);
			borrow = 1 - diff / NBDIGITSPOW;
		}
	}
	
	return copyR;
}

BigInteger long_div(BigInteger x, BigInteger y, int n, int m)
{
	int i = 0, f, k ,qt;
	BigInteger d = NULL, dq = NULL, q = NULL, r = NULL;
	Element *current = NULL;
	
	d = create_big_int();
	dq = create_big_int();
	q = create_big_int();
	r = create_big_int();
	
	if(!isNull(x) && !isNull(y) && !isNull(d) && !isNull(dq) && !isNull(q) && !isNull(r) &&
		!is_empty(x->list) && !is_empty(y->list))
	{
		f = NBDIGITSPOW / ((y->list->valueOf((m - 1) / 4) / pow(10, (m - 1) % 4)) + 1);
		r = product(x, f);
		d = product(y, f);
		q = fromUnsignedLongToBigInteger(0);
		for(k = n - m; k >= 0; k = k - 1)
		{
			qt = trial_digit(r, d, k, m);
			dq = product(d, qt);
			if(smaller(r, dq, k, m))
			{
				qt = qt - 1;
				dq = product(d, qt);
			}
			current = q->list->head;
			for(i = 0; i < k; i = i + 1)
				current = current->next;
			current->key = qt % NBDIGITSPOW * pow(10, k % 4);
			r = difference(r, dq, k, m);
		}
	}
	
	delete_big_int(d);
	delete_big_int(dq);
	delete_big_int(dr);
	
	return q;
}

BigInteger long_mod(BigInteger x, BigInteger y, int n, int m)
{
	BigInteger d = NULL, dq = NULL, r = NULL;
	int f, k, qt;
	
	d = create_big_int();
	dq = create_big_int();
	r = create_big_int();
	
	if(!isNull(x) && !isNull(y) && !isNull(d) && !isNull(dq) && !isNull(r) &&
		!is_empty(x->list) && !is_empty(y->list))
	{
		/* Assuming 2 <= m <= n <= w */
		f = NBDIGITSPOW / ((y->list->valueOf((m - 1) / 4) / pow(10, (m - 1) % 4)) + 1);
		r = product(x, f);
		d = product(y, f);
		for(k = n - m; k >= 0; k = k - 1)
		{
			/* Assuming 2 <= m <= k+m <= n <= w */
			qt = trial_digit(r, d, k, m);
			dq = product(d, qt);
			if(smaller(r, dq, k, m))
			{
				qt = qt - 1;
				dq = product(d, qt);
			}
			r = difference(r, dq, k, m);
		}
	}
	
	delete_big_int(d);
	delete_big_int(dq);
	
	return quotient(r, f);
}

BigInteger divBigInt(BigInteger x, BigInteger y)
{
	int m, n, y1;
	BigInteger q = NULL;
	
	q = create_big_int();
	
	if(!isNull(x) && !isNull(y) && !isNull(q) &&
		!is_empty(x->list) && !is_empty(y->list))
	{
		m = y->list->length;
		if(m == 1 && (y->list->head->key / 10) == 0)
		{
			/* assume y1 > 0 */
			q = quotient(x, y->list->head->key);
		}
		else
		{
			n = x->list->length;
			if(m > n)
				q = fromUnsignedLongToBigInteger(0);
			else
				q = long_div(x, y, n, m);
		}
	}
	
	return delete_left_zero(q);
}

BigInteger restBigInt(BigInteger x, BigInteger y)
{
	int m, n, y1;
	Number r;
	BigInteger r = NULL;
	
	r = create_big_int();
	
	if(!isNull(x) && !isNull(y) && !isNull(r) &&
		!is_empty(x->list) && !is_empty(y->list))
	{
		m = y->list->length;
		if(m == 1 && (y->list->head->key / 10) == 0)
		{
			/* assume y1 > 0 */
			r = remainder(x, y->list->head->key);
		}
		else
		{
			n = x->list->length;
			if(m > n)
				r = x;
			else
				r = long_mod(x, y, n, m);
		}
	}
	
	return delete_left_zero(r);
}

BigInteger divBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
	int i = 0, compare = 0, currentDiv = 0, carry = 0;
	BigInteger div = create_big_int();
	Element *currentFirst = NULL, *currentSecond = NULL;

	if(!isNull(firstBigInt) && !isNull(secondBigInt))
	{
		/* Special cases */
		compare = compareBigInt(firstBigInt, secondBigInt);
        printf("DEBUG\n");
		/* a < b, a / b = 0 */
		if(compare == -1)
		{
			div->list = insert_head(div->list, 0);
            return div;
        }
		/* a = b, a / b = 1 */
		else if(compare == 0)
		{
			div->list = insert_head(div->list, 1);
            return div;
		}
		/* b = 1, a / b = a */
		if(secondBigInt->list->length == 1 && secondBigInt->list->head->key == 1)
			return firstBigInt;

        printf("DEBUG\n");

		currentFirst = firstBigInt->list->tail;
		currentSecond = secondBigInt->list->tail;
		for(i = 0; i < firstBigInt->list->length; i = i + 1)
		{
            /* Works if length(a) = length(b) */
			/* TODO */
            currentDiv = (currentFirst->key / currentSecond->key);
            carry = currentDiv / NBDIGITSPOW;

            printf("%d / %d =>\t", currentFirst->key, currentSecond->key);
            printf("currentDiv = %d\n", currentDiv);
            printf("carry = %d\n", carry);

            if(carry)
            {
                currentDiv = currentDiv % NBDIGITSPOW;
                div->list = insert_head(div->list, currentDiv);
                currentDiv = carry;
                carry = 0;
                printf("DEBUG\n");
            }

            currentFirst = currentFirst->prev;
            currentSecond = currentSecond->prev;
		}
        div->list = insert_head(div->list, currentDiv);
	}

	return div;
}

BigInteger factorial(unsigned long input)
{
	unsigned long i = 0;
	BigInteger bigIntFact = NULL, current = NULL, temp = NULL, unit = NULL;
	Element* current = NULL;
	
	/* Special case */
	/* 0! = 1! = 1 */
	if(input == 0 || input == 1)
		return newBigInt("1");
		
	current = fromUnsignedLongToBigInteger(input);
	temp = diffBigInt(current, unit)
	unit = newBigInt("1");
	
	if(!isNull(current) && !isNull(temp) && !isNull(unit))
	{
		while(signBigInt(temp) == 1) /* while n != 1 */
		{
			bigIntFact = mulBigInt(current, temp); /* fact = n * (n-1) */
			current = diffBigInt(temp, unit); /* n <= n-1 */
			temp = diffBigInt(current, unit); /* n-1 <= n-2 */
		}
	}
	
	return delete_left_zero(bigIntFact);
}

BigInteger cnp(unsigned long n, unsigned long p)
{
	return divBigInt(factorial(n), mulBigInt(factorial(n), factorial(n - p)));
}

/* Conversion */
/*  Result: new big integer
	Data: number as a string
	Process: split the string into 4th characters parts */
BigInteger newBigInteger(char* str)
{
	char tmp[NBDIGITS + 1];
	int length = 0, l = 0, r = 0, c = 0, i = 0;
	BigInteger bigInt = NULL;
	bigInt = create_big_int();

	if(!is_empty(bigInt))
	{
		/* Take into account the sign of the big integer */
		if(!isdigit(str[0]))
		{
			if(str[0] == '-')
				bigInt->sign = -1;
			else if(str[0] == '+')
				bigInt->sign = 1;
			str = &str[1]; /* Gap of the sign */
		}
		else
			bigInt->sign = 1;

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
			bigInt->list = insert_head(bigInt->list, c);
		}
		/* If the length of the list was not already a multiple of NBDIGITS */
		if( r != 0)
		{
			/* Copy the rest of the list */
			memcpy(tmp, str, r);
			tmp[r] = '\0';
			c = atoi(tmp);
			bigInt->list = insert_head(bigInt->list, c);
		}
	}

	return delete_left_zero(bigInt);
}

/*  Result: new big integer
	Data: input as an unsigned long
	Process: convert the input in big integer */
BigInteger fromUnsignedLongToBigInteger(unsigned long input)
{
	int rest = 0, currentPow = basis;
	BigInteger bigInt = NULL;
	
	bigInt = create_big_int();
	if(!isNull(bigInt))
	{
		do
		{
			rest = input % NBDIGITSPOW;
			input = input / NBDIGITSPOW;
			
			bigInt->list = insert_head(bigInt->list, rest);
		}while(rest != 0);
	}
	
	printBigInteger(bigInt);
	return delete_left_zero(bigInt);
}

/*  Result: new big integer
	Data: input as a big integer
	Process: does a copy of input */
BigInteger fromBigIntegerToBigInteger(BigInteger input)
{
	int i = 0;
	BigInteger copy = create_big_int();
	Element *current = NULL;
	
	if(!isNull(input) && !isNull(copy))
	{
		copy->sign = input->sign;
		if(!is_empty(input->list))
		{
			current = input->list->head;
			for(i = 0; i < input->list->length; i = i + 1)
			{
				copy->list = insert_tail(copy->list, current->key);
				current = current->next;
			}
		}
	}
	
	return delete_left_zero(copy);
}

/* Debug */
void printBigInteger(BigInteger input)
{
    Element *current = NULL;
    int i = 0;

    if(is_empty(input) || is_empty(input->list))
        printf("The Big-Integer is empty!\n");
    else
    {
        if(input->sign == -1)
            printf("-");
        current = input->list->head;
        for(i = input->list->length; i > 0; i = i - 1)
        {
            printf("%.4d ", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

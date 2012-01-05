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

	if(!is_null(bigInt))
	{
		bigInt->sign = 0; /* We initialize the sign */
		bigInt->list = create_list(); /* and the list */
		return bigInt;
	}
	return NULL;
}

/*  Result: nothing
	Data: big integer to delete
	Process: use list datatype's destructor  and free the big integer */
void delete_big_int(BigInteger input)
{
	if(input != NULL)
    {
        delete_list(input->list);
        free(input);
	    input = NULL;
    }
}

/* Private methods */
/*  Result: the number of elements of the smallest big-integer
	Data: two big integers which have to be compare
	Process: compare firstBigInt->list->length and secondBigInt->list->length */
int get_min_loops(BigInteger firstBigInt, BigInteger secondBigInt)
{
	int minLoops = 0;
	if(!isNull(firstBigInt) && !isNull(secondBigInt))
		if(!is_null(firstBigInt->list) && !is_null(secondBigInt->list))
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
		if(!is_null(firstBigInt->list) && !is_null(secondBigInt->list))
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

	if(!isNull(input) && !is_null(input->list) && !is_empty(input->list))
	{
		/* We start from the most significant elements */
	    current = input->list->tail;
        if((input->list->length > 1)) /* The final list must contain at least one element */
        {
			/* While we didn't find a key different from 0 and the current element is not the head */
            while(current->key == 0 && current != input->list->head)
            {
                input->list = remove_tail(input->list); /* We delete it */
                current = input->list->tail;
            }
        }

        if(is_empty(input->list))
            input->sign = 0;
	}

	return input;
}

/* Access methods */
Boolean isNull(BigInteger input)
{
	return (input == NULL) ? TRUE : FALSE;
}

int signBigInt(BigInteger input)
{
	return (is_null(input->list)) ? 0 : (input->sign == 1) ? 1 : (input->sign == 0) ? 0 : -1;
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
			if(!is_null(firstBigInt->list) && !is_null(secondBigInt->list))
			{
				/* If there is the same number of element into both list */
				if(firstBigInt->list->length == secondBigInt->list->length)
				{
					currentFirst = firstBigInt->list->tail;
					currentSecond = secondBigInt->list->tail;
					while(!is_null(currentFirst->prev) && !is_null(currentFirst->prev) && (currentFirst->key == currentSecond->key))
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
		if(!is_null(firstBigInt->list) && !is_null(secondBigInt->list))
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
						while(!is_null(currentFirst->prev) && !is_null(currentSecond->prev) && (currentFirst->key == currentSecond->key))
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
		else if(!is_null(firstBigInt->list) && is_null(secondBigInt->list))
			return 1;
		else if(is_null(firstBigInt->list) && !is_null(secondBigInt->list))
			return -1;
	}
	else if(!isNull(firstBigInt) && isNull(secondBigInt))
		return 1;
	else if(isNull(firstBigInt) && !isNull(secondBigInt))
		return -1;

	return 0;
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
        {
            secondBigInt->sign = 1;
            sum = diffBigInt(firstBigInt, secondBigInt);
            secondBigInt->sign = -1;
            return sum;
        }
        else /* a > 0 and b > 0 */
            sum->sign = 1;

        /* We compute the minimum number of loop to reach the end of the smallest big integer */
		min = get_min_loops(firstBigInt, secondBigInt);
		max = get_max_loops(firstBigInt, secondBigInt);

        currentFirst = firstBigInt->list->head;
        currentSecond = secondBigInt->list->head;

        for(i = 0; i < min; i = i + 1)
        {
            /* We sum both numbers */
            currentSum = currentFirst->key + currentSecond->key + r;
            /* We switch to the next elements */
            currentFirst = currentFirst->next;
            currentSecond = currentSecond->next;

            /* We save the deduction */
            r = currentSum / NBDIGITSPOW;
            /* We cast currentSum to a number with maximum 4 digits */
            currentSum = currentSum % NBDIGITSPOW;
            /* We insert the result into the new big int */
            sum->list = insert_tail(sum->list, currentSum);
        }
        /* We save the position in the greatest big integer */
        rest = (i == firstBigInt->list->length) ? currentSecond : currentFirst;
        /* And we summ the rest of it */
        for(i = min; i < max; i = i + 1)
        {
            currentSum = rest->key + r;
            rest = rest->next;

            r = currentSum / NBDIGITSPOW;
            currentSum = currentSum % NBDIGITSPOW;
            sum->list = insert_tail(sum->list, currentSum);
        }
        /* If the deduction is not equal to zero we add it */
        if(r != 0)
            sum->list = insert_tail(sum->list, r);
    }

    return delete_left_zero(sum);
}

/*  Return: new big integer which is the diff of a and b
    Data: two big integers to diff
    Process: diff each element from both big integers */
BigInteger diffBigInt(BigInteger firstBigInt, BigInteger secondBigInt)
{
    int currentDiff = 0, i = 0, min = 0, max = 0;
    Boolean flag = FALSE;
    BigInteger diff = create_big_int();
    Element *currentFirst = NULL, *currentSecond = NULL, *rest = NULL;

    if((!isNull(firstBigInt) && !isNull(secondBigInt)) && (!is_null(firstBigInt->list) && !is_null(secondBigInt->list)))
    {
        /* a - (-b) <=> a + b */
        if(firstBigInt->sign == 1 && secondBigInt->sign == -1)
        {
            secondBigInt->sign = 1;
            diff = sumBigInt(firstBigInt, secondBigInt);
            secondBigInt->sign = -1;
            return diff;
        }

		/* We define the sign of the result */
        diff->sign = compareBigInt(firstBigInt, secondBigInt);

		/* We compute the minimum number of loop to reach the end of the smallest big integer */
        min = get_min_loops(firstBigInt, secondBigInt);
        max = get_max_loops(firstBigInt, secondBigInt);

        currentFirst = firstBigInt->list->head;
        currentSecond = secondBigInt->list->head;
        for(i = 0; i < min; i = i + 1)
        {
            flag = FALSE; /* If the last computation was 0 - x */
			/* If the current key if greater than the second */
            if(currentFirst->key >= currentSecond->key)
                currentDiff = currentFirst->key - currentSecond->key; /* We diff the two keys */
            else
            {
                if(currentFirst->key != 0)
                    currentDiff = currentSecond->key - currentFirst->key;
                else /* Special case 0 - x */
                {
                    currentDiff = 10000 - currentSecond->key;
                    flag = TRUE;
                }
            }
			/* We insert the current result */
            diff->list = insert_tail(diff->list, currentDiff);

            currentFirst = currentFirst->next;
            currentSecond = currentSecond->next;

            if(flag) /* If we reach the special case 0 - x */
                currentFirst->key = currentFirst->key - 1;
        }
        /* We save the position in the greatest big integer */
        rest = (i == firstBigInt->list->length) ? currentSecond : currentFirst;
        /* We add the rest of the elements */
		for(i = min; i < max; i = i + 1)
        {
            currentDiff = rest->key;
            rest = rest->next;
            diff->list = insert_tail(diff->list, currentDiff);
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
			mul->sign = 0;
            return mul;
        }
		else
		{
			/* We define the sign of the result */
		    if((firstBigInt->sign == 1 && secondBigInt->sign == 1) || (firstBigInt->sign == -1 && secondBigInt->sign == -1))
                mul->sign = 1;
            else
                mul->sign = -1;

			if(!is_null(firstBigInt->list) && !is_null(secondBigInt->list))
			{
				/* We save the greatest and the lowest BigIntegers */
                sign = compareBigInt(firstBigInt, secondBigInt);
                if(sign == 1 || sign == 0)
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

				currentGreatest = greatest->list->head;
				/* For each element of the greatest BI */
				for(i = 0; i < greatest->list->length; i = i + 1)
				{
					currentLowest = lowest->list->head;
					currentMul = 0;
					/* we multiply it by the elements of the greatest one */
					for(j = 0; j < lowest->list->length; j = j + 1)
					{
						currentMul = currentMul + currentGreatest->key * currentLowest->key + carry;
						currentLowest = currentLowest->next;
					}
					carry = currentMul / NBDIGITSPOW;
					currentMul = currentMul % NBDIGITSPOW;
					mul->list = insert_tail(mul->list, currentMul);

					currentGreatest = currentGreatest->next;
				}
				/* If there is a carry of the last computation */
                if(carry != 0)
                    mul->list = insert_tail(mul->list, carry);
			}
		}
    }

	return delete_left_zero(mul);
}

/*  Return: new big integer which is the factorial of a
    Data: a the number
    Process: compute the factorial */
BigInteger factorial(unsigned long input)
{
    BigInteger number = NULL, res = NULL, count = NULL;
    number = fromUnsignedLongToBigInteger(input);
    res = fromUnsignedLongToBigInteger(1);
    count = fromUnsignedLongToBigInteger(1);

	/* Special cases: 0! = 1 and 1! = 1 */
    if(input == 0 || input == 1)
        return delete_left_zero(fromUnsignedLongToBigInteger(1));
	/* n! = n*(n-1)! <=> n*(n-1)*(n-2)! <=> n*(n-1)*…*1 */
    if(!isNull(number) && !isNull(res) && !isNull(count))
    {
        for(;compareBigInt(count, number); count = sumBigInt(count, fromUnsignedLongToBigInteger(1)))
            res = mulBigInt(res, count);
        res = mulBigInt(res, count);
    }

    return delete_left_zero(res);
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

	if(!is_null(bigInt))
	{
	    length = strlen(str);
	    if(length == 0)
            return NULL;
        else
        {
            /* Take into account the sign of the big integer */
            if(!isdigit(str[0]))
            {
                if(str[0] == '-')
                    bigInt->sign = -1;
                else if(str[0] == '+')
                    bigInt->sign = 1;

                if(length == 1)
                    return NULL;
                else
                {
                    str = &str[1]; /* Gap of the sign */
                    length = length - 1;
                }
            }
            else
                bigInt->sign = 1;

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
                bigInt->list = insert_tail(bigInt->list, c);
            }
            /* If the length of the list was not already a multiple of NBDIGITS */
            if(r != 0)
            {
                /* Copy the rest of the list */
                memcpy(tmp, str, r);
                tmp[r] = '\0';
                c = atoi(tmp);
                bigInt->list = insert_tail(bigInt->list, c);
            }
        }
	}

    if(bigInt->list->length == 1 && bigInt->list->head->key == 0)
        bigInt->sign = 0;

	return delete_left_zero(bigInt);
}

/*  Result: new big integer
	Data: input as an unsigned long
	Process: convert the input in big integer */
BigInteger fromUnsignedLongToBigInteger(unsigned long input)
{
	int rest = 0;
	BigInteger bigInt = NULL;
	bigInt = create_big_int();

	if(!isNull(bigInt))
	{
	    bigInt->sign = 1;

	    rest = input % NBDIGITSPOW;
		input = input / NBDIGITSPOW;

		while(rest != 0)
		{
			bigInt->list = insert_head(bigInt->list, rest);
			rest = input % NBDIGITSPOW;
			input = input / NBDIGITSPOW;
		}
	}

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
		if(!is_null(input->list))
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

    if(isNull(input) || is_null(input->list))
        printf("The Big-Integer is empty!\n");
    else if(input->sign == 0)
        printf("0\n");
    else
    {
        if(input->sign == -1)
            printf("-");
        current = input->list->tail;
		/* The most significant element is not necessary composed of 4 digits */
        printf("%d ", current->key);

        current = current->prev;
        for(i = input->list->length - 1; i > 0; i = i - 1)
        {
            printf("%.4d ", current->key);
            current = current->prev;
        }
        printf("\n");
    }
}

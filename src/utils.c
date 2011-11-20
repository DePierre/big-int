/*  SAUVAGE Tao
	19/10/11
	Utils
*/

#include "../include/utils.h"

Boolean is_empty(void* d)
{
	return (d == NULL) ? TRUE : FALSE;
}

int power(int n, int p)
{
    int i = 0, current = n;

    for(i = 0; i < p; i = i + 1)
        current = current*n;

    return current;
}


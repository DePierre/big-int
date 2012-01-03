/*  SAUVAGE Tao
	19/10/11
	Utils
*/

#include <utils.h>

Boolean is_empty(void* d)
{
	return (d == NULL) ? TRUE : FALSE;
}

int power(int n, int p)
{
    int i, current = n;

    for(i = 1; i < p; i = i + 1)
        current = current*n;

    return current;
}


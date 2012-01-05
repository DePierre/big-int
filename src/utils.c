/*  SAUVAGE Tao
	19/10/11
	Utils
*/

#include <utils.h>

int power(int n, int p)
{
    int i, current = n;

    for(i = 1; i < p; i = i + 1)
        current = current*n;

    return current;
}

void clean_stdin()
{
    char c;

    /* while c = '\n' and c = '\r' */
    while (scanf("%c",&c)==1 && c!=10 && c!=13);
}

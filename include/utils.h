/*  SAUVAGE Tao
	19/10/11
	Utils
*/

#ifndef DEF_UTILS
#define DEF_UTILS

#include <stdlib.h>

/* Boolean datatype */
#define TRUE 1
#define FALSE 0

typedef unsigned int Boolean;

/*  Result: boolean
	Data: data to test
	Process: test if the data is empty (i.e NULL) */
inline Boolean is_empty(void* d);

#endif


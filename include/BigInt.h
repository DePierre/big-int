/*  SAUVAGE Tao
	23/10/11
	DList:
		Declaration of big integer datatype
*/

#ifndef DEF_BIGINT
#define DEF_BIGINT

#define NBDIGITS 4 /* Number of digits by each element */

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "DList.h"

/* Record of a big integer */
typedef struct
{
	int sign; /* Sign of the big int */
	DList l; /* Pointer to the list */
} Struct_big_integer;

typedef Struct_big_integer* BigInteger;

/* Creator & destructor */
BigInteger create_big_int(void);
void delete_big_int(BigInteger b);
/* Access methods */
inline Boolean isNull(BigInteger b);
inline Boolean signBigInt(BigInteger b);
Boolean equalsBigInt(BigInteger a, BigInteger b);
int compareBigInt(BigInteger a, BigInteger b);
/* Modifiers */
BigInteger newBigInteger(char* str);

#endif

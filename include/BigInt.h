/*  SAUVAGE Tao
	23/10/11
	DList:
		Declaration of big integer datatype
*/

#ifndef DEF_BIGINT
#define DEF_BIGINT

#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <DList.h>

#define NBDIGITS 4 /* Number of digits by each element */
/* Each number can't be greater than 1000 */
#define NBDIGITSPOW (int)power(10, NBDIGITS)

/* Record of a big integer */
typedef struct
{
	int sign; /* Sign of the big int */
	DList list; /* Pointer to the list */
} Struct_big_integer;

typedef Struct_big_integer* BigInteger;

/* Creator & destructor */
BigInteger create_big_int(void);
void delete_big_int(BigInteger);
/* Private methods */
int get_min_loops(BigInteger, BigInteger);
int get_max_loops(BigInteger, BigInteger);
BigInteger delete_left_zero(BigInteger);
/* Access methods */
Boolean isNull(BigInteger);
int signBigInt(BigInteger);
Boolean equalsBigInt(BigInteger, BigInteger);
int compareBigInt(BigInteger, BigInteger);
int* toIntArray(BigInteger);
/* Arithmetic methods */
BigInteger sumBigInt(BigInteger, BigInteger);
BigInteger diffBigInt(BigInteger, BigInteger);
BigInteger mulBigInt(BigInteger, BigInteger);
/* Conversion */
BigInteger newBigInteger(char*);
BigInteger fromUnsignedLongToBigInteger(unsigned long);
BigInteger fromBigIntegerToBigInteger(BigInteger);
/* Debug */
void printBigInteger(BigInteger);

#endif /* DEF_BIGINT */


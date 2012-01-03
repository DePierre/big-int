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
/* Each number can't be greater than 10,00 */
#define NBDIGITSPOW (int)power(10, NBDIGITS)
/* Definition of the two radix needed to the division */
#define DIVIDENDRADIX NBDIGITSPOW
#define DIVISORRADIX 10

/* Record of a big integer */
typedef struct
{
	int sign; /* Sign of the big int */
	DList list; /* Pointer to the list */
} Struct_big_integer;

typedef Struct_big_integer* BigInteger;

typedef struct
{
	int number[DIVISORRADIX + 1];
} Number;

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
/* Division */
BigInteger product(BigInteger, unsigned long);
BigInteger quotient(BigInteger, unsigned long);
BigInteger remainder(BigInteger, unsigned long);
int trial_digit(BigInteger, BigInteger, int, int);
Boolean smaller(BigInteger, BigInteger, int, int);
BigInteger difference(BigInteger, BigInteger, int, int);
BigInteger long_div(BigInteger, BigInteger, int, int);
BigInteger long_mod(BigInteger, BigInteger, int, int);
BigInteger divBigInt(BigInteger, BigInteger);
BigInteger restBigInt(BigInteger, BigInteger);
/* End division*/
/* Advanced arithmetic methods */
BigInteger factorial(unsigned long);
BigInteger cnp(unsigned long, unsigned long);
/* Conversion */
BigInteger newBigInteger(char*);
BigInteger fromUnsignedLongToBigInteger(unsigned long);
BigInteger fromBigIntegerToBigInteger(BigInteger);
/* Debug */
void printBigInteger(BigInteger);
void printNumber(Number);

#endif /* DEF_BIGINT */


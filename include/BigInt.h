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
#define DIVISORRADIX NBDIGITSPOW / 10

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
/* Groups of functions for the division */
float value(Number, int);
int length(Number, int);
Number product(Number, int);
Number quotient(Number, int);
Number remainder(Number, int);
int trial_digit(Number, Number, int, int);
Boolean smaller(Number, Number, int, int);
Number difference(Number, Number, int, int);
Number long_div(Number, Number, int, int);
Number long_mod(Number, Number, int, int);
Number divide(Number, Number);
Number modulo(Number, Number);
BigInteger divBigInt(BigInteger, BigInteger);
/* Modifiers */
BigInteger newBigInteger(char* str);
/* Debug */
void printBigInteger(BigInteger);
void printNumber(Number);

#endif /* DEF_BIGINT */


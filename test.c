#include "test.h"

int main(void)
{
    BigInteger bigInt1 = newBigInteger("1");
    BigInteger bigInt2 = newBigInteger("123456789");
    BigInteger sum = NULL;
    int test = 0;

    printf("Hello world!\n");
    printBigInteger(bigInt1);
    printBigInteger(bigInt2);

    test = compareBigInt(bigInt1, bigInt2);
    if(test == 0)
        printf("a et b sont égaux\n");
    else if(test == 1)
        printf("a est sup à b\n");
    else if(test == -1)
        printf("a est inf à b\n");

    sum = sumBigInt(bigInt1, bigInt2);
    printf("a + b = ");
    printBigInteger(sum);

    delete_big_int(bigInt1);
    delete_big_int(bigInt2);
    delete_big_int(sum);
    return 0;
}


#include <utils.h>
#include <DList.h>
#include <BigInt.h>
#include <stdio.h>

int main(void)
{
    BigInteger bigInt1 = newBigInteger("999900009876");
    BigInteger bigInt2 = newBigInteger("999999999999");
    BigInteger bigInt3 = newBigInteger("9999");
    BigInteger bigInt4 = newBigInteger("2");
    BigInteger sum = NULL, diff = NULL, mul = NULL;
    int test = 0;

    printf("Hello world!\n");
    printBigInteger(bigInt1);
    printBigInteger(bigInt2);
    printBigInteger(bigInt3);
    printBigInteger(bigInt4);

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

    diff = diffBigInt(bigInt1, bigInt2);
    printf("a - b = ");
    printBigInteger(diff);

    mul = mulBigInt(bigInt3, bigInt4);
    printf("c * d = ");
    printBigInteger(mul);

    delete_big_int(bigInt1);
    delete_big_int(bigInt2);
    delete_big_int(bigInt3);
    delete_big_int(bigInt4);
    delete_big_int(sum);
    delete_big_int(diff);
    delete_big_int(mul);
    return 0;
}


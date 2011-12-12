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
    BigInteger bigInt5 = newBigInteger("999922221234");
    BigInteger bigInt6 = newBigInteger("111111111111");
    BigInteger sum = NULL, diff = NULL, mul = NULL, div = NULL;;
    int test = 0;

    printf("Hello world!\n");
    printBigInteger(bigInt1);
    printBigInteger(bigInt2);
    printBigInteger(bigInt3);
    printBigInteger(bigInt4);
    printBigInteger(bigInt5);
    printBigInteger(bigInt6);

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

    div = divBigInt(bigInt5, bigInt6);
    printf("e / f = ");
    printBigInteger(div);

    delete_big_int(bigInt1);
    delete_big_int(bigInt2);
    delete_big_int(bigInt3);
    delete_big_int(bigInt4);
    delete_big_int(bigInt5);
    delete_big_int(bigInt6);
    delete_big_int(sum);
    delete_big_int(diff);
    delete_big_int(mul);
    delete_big_int(div);
    return 0;
}


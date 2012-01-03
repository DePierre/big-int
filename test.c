/*  SAUVAGE Tao
    27/10/11
    Main:
        Main menu useable by the user
*/

#define MAX 100

#include <utils.h>
#include <DList.h>
#include <BigInt.h>
#include <stdlib.h>
#include <stdio.h>

void clean_stdin(void)
{
    int c;

    do
    {
        c = getchar();
    }while(c != '\n' && c != EOF);
}

int main(void)
{
    int choice = 0, test = 0;
    char str[MAX];
    BigInteger a = NULL, b = NULL, temp = NULL, ope = NULL;

    printf("Project of LO27: Big Integers\n\n");
    printf("Please define the first big integer\n");
    scanf("%s", str);
    a = newBigInteger(str);
    printf("Please define the second big integer\n");
    scanf("%s", str);
    b = newBigInteger(str);

    do
    {
        printf("Menu:\n");
        printf("1. Swap the two big integers\n");
        printf("2. Sum the two big integers\n");
        printf("3. Diff the two big integers\n");
        printf("4. Mul the two bif integers\n");
        printf("5. Test the sign of the two big integers\n");
        printf("6. Compare the two big integers\n");
        printf("7. Print the two big integers\n");
        printf("8. Quit\n\n");

        printf("Choice :\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                temp = fromBigIntegerToBigInteger(a);
                a = fromBigIntegerToBigInteger(b);
                b = fromBigIntegerToBigInteger(temp);
                printf("The two big integers have been swaped\n");
                break;
            case 2:
                ope = sumBigInt(a, b);
                printBigInteger(a);
                printf(" + \n");
                printBigInteger(b);
                printf(" = \n");
                printBigInteger(ope);
                break;
            case 3:
                ope = diffBigInt(a, b);
                printBigInteger(a);
                printf(" - \n");
                printBigInteger(b);
                printf(" = \n");
                printBigInteger(ope);
                break;
            case 4:
                ope = mulBigInt(a, b);
                printBigInteger(a);
                printf(" * \n");
                printBigInteger(b);
                printf(" = \n");
                printBigInteger(ope);
                break;
            case 5:
                test = signBigInt(a);
                if(test == 1)
                    printf("The first big integer is greater than 0\n");
                else if(test == -1)
                    printf("The first big integer is lower than 0\n");
                else
                    printf("The first big integer is equal to 0\n");
                test = signBigInt(b);
                if(test == 1)
                    printf("The second big integer is greater than 0\n");
                else if(test == -1)
                    printf("The second big integer is lower than 0\n");
                else
                    printf("The second big integer is equal to 0\n");
                break;
            case 6:
                test = compareBigInt(a, b);
                if(test == 1)
                    printf("The first big integer is greater than the second one\n");
                else if(test == -1)
                    printf("The first big integer is lower than the seconde one\n");
                else
                    printf("The two big integers are equal to each other\n");
                break;
            case 7:
                printBigInteger(a);
                printBigInteger(b);
                break;

            printf("\n");
        }
    }while(choice <= 7 && choice >= 1);



    delete_big_int(a);
    delete_big_int(b);
    delete_big_int(temp);
    delete_big_int(ope);

    return 0;
}


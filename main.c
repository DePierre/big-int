/*  SAUVAGE Tao
    27/10/11
    Main:
        Main menu useable by the user
*/

#include <main.h>

int main(void)
{
    int choice = 0, lastOpe = 0;
    unsigned long fact = 0;
    char *str = NULL;
    BigInteger biOne = NULL, biTwo = NULL, res = NULL, temp = NULL;

    do
    {
        choice = display_menu();

        switch(choice)
        {
            case 1:
                clean_stdin();
                str = new_str_of_big_int(1);
                biOne = newBigInteger(str);
                free(str);
                str = NULL;
                break;
            case 2:
                clean_stdin();
                str = new_str_of_big_int(2);
                biTwo = newBigInteger(str);
                free(str);
                str = NULL;
                break;
            case 3:
                temp = fromBigIntegerToBigInteger(biOne);
                biOne = fromBigIntegerToBigInteger(biTwo);
                biTwo = fromBigIntegerToBigInteger(temp);
                break;
            case 4:
                lastOpe = '+';
                res = sumBigInt(biOne, biTwo);
                break;
            case 5:
                lastOpe = '-';
                res = diffBigInt(biOne, biTwo);
                break;
            case 6:
                lastOpe = '*';
                res = mulBigInt(biOne, biTwo);
                break;
            case 7:
                printf("Enter the number :\t");
                scanf("%ld", &fact);
                res = factorial(fact);
                printf("(%ld)! = ", fact);
                printBigInteger(res);
                break;
            case 8:
                printf("BigInteger 1 :\t");
                printBigInteger(biOne);
                printf("BigInteger 2:\t");
                printBigInteger(biTwo);
                if(lastOpe != 0)
                {
                    printf("\n(1) %c (2) = ", lastOpe);
                    printBigInteger(res);
                }
                break;
        }
        printf("\n");
    }while (choice != 9);

    delete_big_int(biOne);
    delete_big_int(biTwo);
    delete_big_int(res);
    delete_big_int(temp);
    return 0;
}

int display_menu()
{
    int choice = 0;

    printf("Menu: \n");
    printf("1. Define the first big integer\n");
    printf("2. Define the second big integer\n");
    printf("3. Swap the two big integers\n");
    printf("\n4. Sum big integers\n");
    printf("5. Diff big integers\n");
    printf("6. Mul big integers\n");
    printf("\n7. Factorial\n");
    printf("\n8. Print the big integers\n");
    printf("\n9. Quit\n");

    printf("\nChoice : ");
    scanf("%d", &choice);
    printf("\n");

    return choice;
}

char* new_str_of_big_int(int index)
{
    char* wholeNumber;
    char nb;
    int i;

    wholeNumber=(char*) calloc(1, sizeof(char));

    printf("\nWrite the number %d : ", index);

    i=0;
    while(scanf("%c",&nb)==1 && nb!=10 && nb!=13)
    {
        /* If nb is a digit or if its first input is '+' or '-' */
        if(isdigit(nb) || (i==0 && (nb=='+' || nb=='-')))
        {
            wholeNumber[i]=nb;
            i++;
            wholeNumber=(char*) realloc(wholeNumber,(i+1)*sizeof(char));
        }
    }
    wholeNumber[i]='\0';

    return wholeNumber;
}

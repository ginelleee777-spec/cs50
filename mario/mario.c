
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // get long by first getting string
    long n;
    while (1)
    {
        printf("enter integer from 1 to 8 inclusive: ");
        char num[5];
        scanf("%4s", num);
        char *end;
        n = strtol(num, &end, 10);

        // validation
        if (*end == '\0')
        {
            if (n > 0 && n < 9)
            {
                // printf("%ld \n", n);
                break;
            }
        }
        printf("invalid input\n");
    }

    // printf("%ld \n" , n);

    for (long i = 1; i <= n; i++)
    {
        long diff = n - i;

        for (long x = 1; x <= diff; x++)
        {
            printf(" ");
        }

        for (long j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("  ");

        for (long j = 1; j <= i; j++)
        {
            printf("#");
        }

        // for (long x =1; x<=diff; x++)
        // {
        //     printf(" ");
        // }

        printf("\n");
    }
}

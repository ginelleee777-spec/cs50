
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long get_posint(void);
bool luhn(long nummm, int lengthhh);

int main(void)
{
    long num = get_posint();

    // check and get length
    int length = 0;
    long temp = labs(num); // handles negative
    char invalid[] = "INVALID";

    do
    {
        temp /= 10;
        length++;
    }
    while (temp != 0);

    if (length == 15)
    {
        // AMEX potentially

        // get power to divide by
        long power = 1;
        for (int i = 0; i < length - 2; i++)
        {
            power *= 10;
        }

        int first = (num / (power) == 34);
        int second = (num / (power) == 37);

        if ((first) == 0 && second == 0)
        {
            printf("%s\n", invalid);
        }

        else
        {
            bool validdd = luhn(num, length);
            if (validdd == 1)
            {
                printf("AMEX\n");
                return 0;
            }
            else
            {
                printf("%s\n", invalid);
            }
        }
    }

    else if (length == 13)
    {
        // VISA potentially
        // get power to divide by
        long power = 1;
        for (int i = 0; i < length - 1; i++)
        {
            power *= 10;
        }

        int visafirst = (num / power) == 4;

        if (visafirst == 0)
        {
            printf("%s\n", invalid);
            return 0;
        }

        else
        {
            bool validdd = luhn(num, length);
            if (validdd == 1)
            {
                printf("VISA\n");
                return 0;
            }
            else
            {
                printf("%s\n", invalid);
            }
        }
    }

    else if (length == 16)
    {
        // MASTERCARD & VISA potentially

        long power = 1;
        for (int i = 0; i < length - 2; i++)
        {
            power *= 10;
        }

        // MASTERCARD possibility

        int sixteenfirst = (num / power == 51);
        int sixteensecond = (num / power == 52);
        int sixteenthird = (num / power == 53);
        int sixteenfourth = (num / power == 54);
        int sixteenfifth = (num / power == 55);

        // VISA possibility
        // get power to divide by
        power = 1;
        for (int i = 0; i < length - 1; i++)
        {
            power *= 10;
        }

        int visafirst = (num / power) == 4;

        // test if MASTERCARD

        if (sixteenfirst == 0 && sixteensecond == 0 && sixteenthird == 0 && sixteenfourth == 0 &&
            sixteenfifth == 0 && visafirst == 0)
        {
            printf("%s\n", invalid);
            return 0;
        }

        else if (visafirst == 1)
        {
            bool validdd = luhn(num, length);
            if (validdd == 1)
            {
                printf("VISA\n");
                return 0;
            }
            else
            {
                printf("%s\n", invalid);
            }
        }

        else
        {
            bool validdd = luhn(num, length);
            if (validdd == 1)
            {
                printf("MASTERCARD\n");
                return 0;
            }
            else
            {
                printf("%s\n", invalid);
            }
        }
    }

    else
    {
        printf("%s\n", invalid);
    }

    // printf("\n");
}

// rmb to declare prototype
bool luhn(long nummm, int lengthhh)
{
    int sum = 0;
    long tempnum = nummm;

    for (int count = 0; count < lengthhh; count++)
    {
        int digit = tempnum % 10;
        tempnum /= 10;

        if (count % 2 == 0)
        {
            sum += digit;
        }

        else
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
            sum += digit;
        }
    }

    // printf("luhn's algo sum: %d \n", sum);

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

long get_posint(void)
{
    char intString[100];
    bool notvalid = true;
    long n;

    do
    {
        // Ask the user to input integer in string
        printf("Number: ");

        // Get the integer in string
        fgets(intString, sizeof(intString), stdin);

        char *end;
        n = strtol(intString, &end, 10);

        // strtol keeps \n     strtol == 0 is NOT a valid test
        if ((*end == '\n' || *end == '\0') && n > 0)
        {
            notvalid = false;
        }
    }

    while (notvalid);

    // Output the text
    // printf("your number is %li \n", n);

    return n;
}

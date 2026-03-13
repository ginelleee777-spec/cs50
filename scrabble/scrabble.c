
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void get_stringgg(char fullName[], int size, int num);
int get_points(char stringgg[]);

int main(void)
{
    char one[100];
    get_stringgg(one, 100, 1);

    char two[100];
    get_stringgg(two, 100, 2);
    // printf("%s\n", h);

    int onesum = get_points(one);
    int twosum = get_points(two);

    if (onesum > twosum)
    {
        printf("Player 1 wins! \n");
    }
    else if (twosum > onesum)
    {
        printf("Player 2 wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }

    // printf("sum is %d\n", onesum);
    return 0;
}

int get_points(char stringgg[])
{
    int sum = 0;
    for (int i = 0; (stringgg[i] != '\0' && stringgg[i] != '\n' && stringgg[i] != ' '); i++)
    {
        switch (stringgg[i])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'l':
            case 'n':
            case 'o':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'L':
            case 'N':
            case 'O':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
                sum += 1;
                break;

            case 'd':
            case 'g':
            case 'D':
            case 'G':
                sum += 2;
                break;

            case 'b':
            case 'c':
            case 'm':
            case 'p':
            case 'B':
            case 'C':
            case 'M':
            case 'P':
                sum += 3;
                break;

            case 'f':
            case 'h':
            case 'v':
            case 'w':
            case 'y':
            case 'F':
            case 'H':
            case 'V':
            case 'W':
            case 'Y':
                sum += 4;
                break;

            case 'k':
            case 'K':
                sum += 5;
                break;

            case 'j':
            case 'x':
            case 'J':
            case 'X':
                sum += 8;
                break;

            case 'q':
            case 'z':
            case 'Q':
            case 'Z':
                sum += 10;
                break;

            default:
                // printf("NOT FOUND \n");
                break;

                // 1 - aeilnorstu
                // 2 - dg
                // 3 - bcmp
                // 4 - fhvwy
                // 5 - k
                // 8 - jx
                // 10 - qz
        }
    }
    return sum;
}

void get_stringgg(char fullName[], int size, int num)
{

    printf("Player %d: ", num);

    fgets(fullName, size, stdin);
}

// 1 - aeilnorstu
// 2 - dg
// 3 - bcmp
// 4 - fhvwy
// 5 - k
// 8 - jx
// 10 - qz

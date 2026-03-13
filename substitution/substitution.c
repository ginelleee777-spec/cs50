
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_stringgg(char fullName[], int size);

bool valid_key(char *key);

int main(int argc, char *argv[])
{

    printf("number of args: %d, argv: %s\n", argc, *argv);
    // int x = argc;
    // char *y = argv;

    if (argc <= 1)
    {
        printf("pls provide key to encrypt\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("too many arguments\n");
        return 1;
    }
    else
    {
        int len = strlen(argv[1]);
        char *key = argv[1];
        if (len != 26)
        {
            printf("your key doesnt have 26 characters, it has %d characters\n", len);
            return 1;
        }
        else
        {
            bool valid = valid_key(key);
            if (!valid)
            {
                printf("not valid key");
                return 1;
            }

            // printf("it is %s that the key u have entered is valid\n", valid ? "true" : "false");
        }
    }

    // obtain plaintext:

    char *keyyy = argv[1];

    char h[10000];
    get_stringgg(h, 10000);
    // printf("%s\n", h);

    // assume everyt in capital letters:

    int lenh = strlen(h);
    bool isup;
    printf("ciphertext: ");

    // loop through string h
    for (int j = 0; j < lenh; j++)
    {
        char curr = h[j];

        // check what letter it is

        if (curr >= 97 && curr <= 122)
        {
            int num = curr - 97;
            // printf("not upper\n");
            isup = false;
            printf("%c", tolower(keyyy[num]));
        }
        else if (curr >= 65 && curr <= 90)
        {
            int num = curr - 65;
            // printf("stays upper\n");
            isup = true;
            printf("%c", toupper(keyyy[num]));
        }
        else
        {
            printf("%c", h[j]);
        }

        // printf("huh");

        // return 0;
    }
    printf("\n");
    return 0;
}

bool valid_key(char *key)
{

    //                            NEW ATTEMPT:
    bool found;
    for (int letter = 'A'; letter <= 'Z'; letter++)
    {
        found = false;
        for (int i = 0; i < 26; i++)
        {
            if (toupper(key[i]) == letter)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            // printf("not valid key\n");
            // printf("letter is %c\n", letter);
            return false;
        }
    }

    // printf("valid key\n");
    return true;

    //                           FAILED ATTEMPT:
    // bool valid_keyyy = true;
    // bool found_letter;
    // int len = strlen(key);

    // // so now u know there are 26 characters in the string,
    // // u just need to check if each letter appears at least once
    // found_letter = false;
    // int curr = 65;
    // while (valid_keyyy == true)
    // {
    //     int i = 0;
    //     found_letter = false;
    //     while (found_letter == false)
    //     {
    //         if ((key[i] == curr) || (key[i] == (curr + 32)))
    //         {
    //             found_letter = true;
    //             if (curr + 1 > 90)
    //             {
    //                 printf("valid key ! :D \n");
    //                 return valid_keyyy;
    //             }
    //             else
    //             {
    //                 curr++;
    //             }

    //         }
    //         else if (i+1 != len)      // not at last character yet
    //         {
    //             i++;
    //         }
    //         else
    //         {
    //             valid_keyyy = false;
    //             printf("not valid key \n");
    //             return valid_keyyy;

    //         }
    //     }

    // }
}

void get_stringgg(char fullName[], int size)
{

    printf("plaintext: ");

    fgets(fullName, size, stdin);
}

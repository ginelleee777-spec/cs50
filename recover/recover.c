#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    // const int HEADERSIZE = 32;
    bool continueee = false;

    // typedef uint8_t  BYTE;
    // typedef uint32_t DWORD;

    if (argc != 2)
    {
        printf("Usage: ./recover <filename> \n");
        return 1;
    }

    char *recover = argv[1];
    FILE *input = fopen(recover, "r");
    if (input == NULL)
    {
        printf("Could not open %s \n", recover);
        return 1;
    }

    // DWORD buffer;
    // DWORD valid = 11111111110110001111111111100000;
    bool validdd = false;
    char str[20];
    int count = 0;
    uint8_t buffer[512];
    FILE *output = NULL;
    bool validdddd;

    while (fread(buffer, 512, 1, input))
    {
        // check header
        validdddd = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                     (buffer[3] & 0xf0) == 0xe0);
        if (validdddd)
        {
            // validdd = true;
            // continueee = false;
            if (output != NULL)
            {
                fclose(output);
                count += 1;
            }

            sprintf(str, "%03d.jpg", count);
            output = fopen(str, "w");
        }

        if (output != NULL)
            fwrite(buffer, 512, 1, output);
    }
    fclose(output);
    fclose(input);
    return 0;
}

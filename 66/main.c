/* textConvert
Convert a string to either the binary or hexadecimal representation
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u8 uint8_t
#define u32 uint32_t
#define i32 int32_t

typedef enum
{
    MODE_HEX,
    MODE_BIN,
    MODE_NIL
} MODE;

char getSegment(u8 base);

void printBin(char ch);
void printHex(char ch);

int main(int argc, char **argv)
{
    MODE mode = MODE_NIL;
    u32 splitDistance = 0;
    char *text = NULL;

    for (i32 i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-x") == 0)
            mode = MODE_HEX;
        else if (strcmp(argv[i], "-b") == 0)
            mode = MODE_BIN;
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (i + 1 < argc)
            {
                splitDistance = atoi(argv[++i]);
            }
            else
            {
                fprintf(stderr, "[Error] No split distance was specified\n");
                return 1;
            }
        }
        else if (text == NULL)
            text = argv[i];
        else
        {
            fprintf(stderr, "[Error] \"%s\" is not a valid argument\n", argv[i]);
            return 1;
        }
    }

    if (mode == MODE_NIL)
    {
        fprintf(stderr, "[Error] No mode was selected\n");
        return 1;
    }
    else if (text == NULL)
    {
        fprintf(stderr, "[Error] No text to convert was specified\n");
        return 1;
    }

    for (u32 i = 0; i < strlen(text); i++)
    {
        if (mode == MODE_BIN)
            printBin(text[i]);
        else
            printHex(text[i]);

        if (splitDistance != 0)
        {
            if ((i + 1) % splitDistance == 0)
                printf("\n");
        }
    }

    printf("\n");
    return 0;
}

char getSegment(u8 base)
{
    if (base < 10)
        return base + '0';
    else
        return base + 'A' - 10;
}

void printBin(char ch)
{
    char buffer[9] = {0};
    for (u8 i = 0; i < 8; i++)
    {
        if (ch & (1 << i))
            buffer[7 - i] = '1';
        else
            buffer[7 - i] = '0';
    }

    printf("%s ", buffer);
}

void printHex(char ch)
{
    char buffer[3] = {0};
    buffer[0] = getSegment(ch >> 4);
    buffer[1] = getSegment(ch & 0x0F);
    printf("%s ", buffer);
}

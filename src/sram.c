// sram.c

#include <stdio.h>

#include "sram.h"

/*
=============================================================================
						 SRAM DUMP
=============================================================================
*/

static unsigned char *byte_buffer;

//===========================================================================

/*
===============
sramdump_validate

Validate the *.srm file supplied on the command-line as a Zelda no Densetsu / Link to the Past SRAM dump
===============
*/
void sramdump_validate(char *file)
{
    FILE *srm = fopen(file, "rb");

    if (srm == (FILE *)NULL)
    {
        printf("\n\n\t%s does not exist.\n", file);
    }

    if (srm)
    {
        fseek(srm, 0, SEEK_END);
        unsigned long sz = ftell(srm);
        fseek(srm, 0, SEEK_SET);

        // error - expecting SRAMSIZE

        /*
        Let's do some other nice things down the road to verify it's an LTTP SRM file
        Test if $0 is mirrored at $500, etc
        */

        // Dump the *.srm file to *byte_buffer
        sramdump(srm);
    }
}

/*
===============
sramdump

Go through the entire byte_buffer index and print it to the console
===============
*/
void sramdump(FILE *srm)
{
    char ch;
    unsigned long index = 0;
    unsigned long width = 0;
    byte_buffer = malloc(SLOTSIZE);

    printf("Slot 0:\n\n");

    while (!feof(srm))
    {
        ch = getc(srm);

        if ((index >= 0) && (index <= SLOTSIZE))
        {
            byte_buffer[index] = ch;

            if (byte_buffer[index] != 0)
            {
                printf("\x1B[36m%02x ", byte_buffer[index]);
                printf("\x1B[0m");
            }
            else
            {
                printf("%02x ", byte_buffer[index]);
            }

            // Represent 0 through F per row
            if (width == 15)
            {
                printf("\n");
                width = 0;
            }
            else
            {
                width++;
            }

            index++;
        }
    }

    fclose(srm);
    //free(byte_buffer);
}

char *sramdump_print()
{
    // ...
    return byte_buffer;
}
/*

    char *function() {
    char *str = malloc(13); // dynamically allocate a char array

    if(str == NULL) {
        printf("Error allocating memory for string.");
        exit(1);
    }

    strcpy(str, "hello world!");
    return str;
    }

    int main(void) {
    char *str = function();
    printf("%s\n", str);
    free(str);                   // free the memory
    return 0;
    }

*/

// strcpy byte_buffer in my function above
// call this function from serve.c
// All of this has to occur from a new TEST switch - which calls the sram_validate first,
//      - so that byte_buffer exists
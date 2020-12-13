// sram.c

#include <stdio.h>
#include <windows.h>

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

Go through the entire byte_buffer index
===============
*/
void sramdump(FILE *srm)
{
    char ch;
    unsigned long index = 0;

    byte_buffer = malloc(SLOTSIZE);

    while (!feof(srm))
    {
        ch = getc(srm);

        if ((index >= 0) && (index <= SLOTSIZE))
        {
            byte_buffer[index] = ch;

            //sprintf(dump, "0x%02x", byte_buffer[index]);
            //sprintf(dump + (index * 2), "%02x", byte_buffer[index]);
            //...

            index++;
        }
    }

    //free(byte_buffer);
    fclose(srm);
}
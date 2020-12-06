// sram.c

#include <stdio.h>

#include "sram.h"

/*
=============================================================================
						 SRAM DUMP
=============================================================================
*/

//static unsigned char *byte_buffer;
static char *dump;

/*
===============
sramdump_window

Create the Win32 Window that will display the contents of the SRAM dump
===============
*/
void sramdump_window(void)
{
    // SDL stuff
}

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

x
===============
*/
void sramdump(FILE *srm)
{
    char ch;
    unsigned char *byte_buffer;
    unsigned long index = 0;

    byte_buffer = malloc(SLOTSIZE);
    dump = malloc(SLOTSIZE);

    while (!feof(srm))
    {
        ch = getc(srm);

        if ((index >= 0) && (index <= SLOTSIZE))
        {
            byte_buffer[index] = ch;

            //sprintf(dump, "0x%02x", byte_buffer[index]);
            //sprintf(dump+(index*2), "%02x", byte_buffer[index]);

            // Rework this logic - The idea is to have spreadsheet/hex editor like cells
            index++;

            if (index == SLOTSIZE)
                sramdump_window();
        }
    }

    free(byte_buffer);
    fclose(srm);
}
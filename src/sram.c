// sram.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sram.h"

/*
=============================================================================
						 SRAM DUMP
=============================================================================
*/

// Byte buffer doesn't need to be here any more

char sram[SLOTSIZE * 2 + 1];

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

    unsigned char *byte_buffer = malloc(SLOTSIZE);

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

    // Cast unsigned char to char
    for (int n = 0; n < SLOTSIZE; n++)
    {
        snprintf(&sram[n * 2], sizeof(sram) - (n * 2), "%02X", byte_buffer[n]);
    }
}

// free(byte_buffer);

/*

//This is the sample program to notify us for the file creation and file deletion takes place in “/tmp” directory
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main( )
{
  int length, i = 0;
  int fd;
 = int wd;
  char buffer[EVENT_BUF_LEN];

  //creating the INOTIFY instance
  fd = inotify_init();

  //checking for error
  if ( fd < 0 ) {
    perror( "inotify_init" );
  }

  //adding the “/tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.
  wd = inotify_add_watch( fd, "/tmp", IN_CREATE | IN_DELETE );

  //read to determine the event change happens on “/tmp” directory. Actually this read blocks until the change event occurs

  length = read( fd, buffer, EVENT_BUF_LEN ); 

  //checking for error
  if ( length < 0 ) {
    perror( "read" );
  }  

  //actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.
  while ( i < length ) {     struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     if ( event->len ) {
      if ( event->mask & IN_CREATE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "New directory %s created.\n", event->name );
        }
        else {
          printf( "New file %s created.\n", event->name );
        }
      }
      else if ( event->mask & IN_DELETE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "Directory %s deleted.\n", event->name );
        }
        else {
          printf( "File %s deleted.\n", event->name );
        }
      }
    }
    i += EVENT_SIZE + event->len;
  }
  //removing the “/tmp” directory from the watch list.
   inotify_rm_watch( fd, wd );

  //closing the INOTIFY instance
   close( fd );

}

*/
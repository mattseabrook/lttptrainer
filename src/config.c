// config.c

#include <stdio.h>

#include "config.h"

/*
=============================================================================
						 CONFIG FILE INTERFACE
=============================================================================
*/

char snes_nine_x_path;

//===========================================================================

/*
===============
parse_cfg

Open this application's standard *.cfg file, and make the parameters available via key-value pairs
===============
*/
void parse_cfg()
{
    //
    // Location of the Config File
    //
#ifdef __WIN32__
    char *cfg_file = getenv("USERPROFILE");
    char *cfg_filename = "\\lttptrainer.cfg";

    strncat(cfg_file, cfg_filename, 16);
#else
    char cfg_file[] = "~/.lttptrainer";
#endif

    FILE *file = fopen(cfg_file, "r");

    if (file != NULL)
    {
        char *line[1000];

        while (fgets(line, sizeof line, file) != NULL)
        {
            printf("%s", line);

            // Path to snes9x emu
            if (strncmp(line, "snes9x_path", 11) == 0)
            {
                printf("<- match found");
            }
        }
        fclose(file);
    }
    else
    {
        perror(file);
    }

    printf("Hello");
}

/*

while ( fgets ( line, sizeof line, file ) != NULL )
      {
         fputs ( line, stdout ); 
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); 
   }
















            // Path to snes9x emu
            if (strncmp(line, keys[0], 8) == 0)
            {
                printf("We have a match!");
                strcpy(snes_nine_x_path, line);
            }




            
   */
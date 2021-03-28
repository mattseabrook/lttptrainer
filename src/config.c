// config.c

#include <stdio.h>

#include "config.h"

/*
=============================================================================
						 CONFIG FILE INTERFACE
=============================================================================
*/

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

    // Keys
    char keys[2];
    keys[0] = "snes9x_path";
    keys[1] = "sramtrace_interval";

    FILE *file = fopen(cfg_file, "r");

    if (file != NULL)
    {
        char line[1000];

        while (fgets(line, sizeof line, file) != NULL) /* read a line from a file */
        {
            fprintf(stdout, "%s", line); //print the file contents on stdout.
            if (strncmp(line, keys[0], strlen(keys[0])) == 0)
            {
                char *value = strchr(line, '=');
                value += 1;

                char snes_nine_x_path = strdup(value);
            }

            // Need to check the struct and then break
            break;
        }
        fclose(file);
    }
    else
    {
        // We will hard-code defaults
    }
}
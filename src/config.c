// config.c

#include <stdio.h>

#include "config.h"

/*
=============================================================================
						 CONFIG FILE INTERFACE
=============================================================================
*/

char snes_nine_x_path[1000];
int sramtrace_interval;

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
            if ((strstr(line, "snes9x_path")) != NULL)
            {
                char *path = strrchr(line, '=');
                strcpy(snes_nine_x_path, path + 1);
            }

            // SRAM trace interval in milliseconds
            if ((strstr(line, "sramtrace_interval")) != NULL)
            {
                char *num = strrchr(line, '=');
                sramtrace_interval = atoi(num + 1);
            }
        }
        fclose(file);
    }
    else
    {
        perror(file);
    }
}
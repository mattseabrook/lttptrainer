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

    // Test
    printf("Configuration File Location: %s\n", cfg_file);
}
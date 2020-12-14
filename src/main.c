// lttptrainer.c

/*

    Link to the Past: Trainer & API in C

    Matthew Seabrook
    info@mattseabrook.net

    https://www.mattseabrook.net

*/

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "sram.h"
#include "serve.h"

//===========================================================================

/*
=============================================================================
						 MAIN ENTRYPOINT
=============================================================================
*/
int main(int argc, char *argv[])
{
    // Get a handle on the Command Prompt
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Program information & credits
    SetConsoleTextAttribute(hStdOut, 2);
    printf("Zelda: A Link to the Past\n");
    SetConsoleTextAttribute(hStdOut, 7);
    printf("Trainer API v.1.1 - Matt Seabrook (info@mattseabrook.net)\n\n");

    //
    // Parse CLI args
    //
    if (!argv[1])
    {
        help_text();
        return 0;
    }

    // Testing - Remove once the final architecture is in place
    if (strcmp(argv[1], "-T") == 0 || strcmp(argv[1], "-t") == 0)
    {
        printf("Test was invoked.\n");
    }
    //
    // Inspect an *.srm file containing an SRAM dump
    //
    else if (strcmp(argv[1], "-I") == 0 || strcmp(argv[1], "-i") == 0)
    {
        sramdump_validate(argv[2]);
    }
    //
    // RAM Trace (virtual)
    //
    else if (strcmp(argv[1], "-R") == 0 || strcmp(argv[1], "-r") == 0)
    {
        // Figure out stuff about pids and background processes in Windows,
        http_serve();

        // Get snes9x process
        // Hotkey to save srm file
    }
    //
    // Version info
    //
    else if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "-v") == 0)
    {
        printf("\n\n              _______\n\
         ..-'`       ````---.\n\
       .'          ___ .'````.'SS'.\n\
      /        ..-SS####'.  /SSHH##'.\n\
     |       .'SSSHHHH##|/#/#HH#H####'.\n\
    /      .'SSHHHHH####/||#/: \\SHH#####\\\n\
   /      /SSHHHHH#####/!||;`___|SSHH###\\\n\
-..__    /SSSHHH######.         \\SSSHH###\\\n\
`.'-.''--._SHHH#####.'           '.SH####/\n\
  '. ``'-  '/SH####`/_             `|H##/\n\
  | '.     /SSHH###|`'==.       .=='/\\H|\n\
  |   `'-.|SHHHH##/\\__\\/        /\\//|~|/\n\
  |    |S#|/HHH##/             |``  |\n\
  |    \\H' |H#.'`              \\    |\n\
  |        ''`|               -     /\n\
  |          /H\\          .----    /\n\
  |         |H#/'.           `    /\n\
  |          \\| | '..            /\n\
  |            /|    ''..______.'\n\
   \\          //\\__    _..-. | \n\
    \\         ||   ````     \\ |_\n\
     \\    _.-|               \\| |_\n\
     _\\_.-'   `'''''-.        |   `--.\n\
 ''``    \\            `''-;    \\ /\n\
          \\      .-'|     ````.' -\n\
          |    .'  `--'''''-.. |/\n\
          |  .'               \\|\n\
          |.'\n");

        printf("\n\n\tlttptrainer\n");
        printf("\tv.1.1 - 12/13/2020 \n\n");
        printf("\tAuthor: Matt Seabrook\n");
    }
    //
    // Help text
    //
    else if (strcmp(argv[1], "-H") == 0 || strcmp(argv[1], "-h") == 0)
        help_text();

    return 0;
}

/*
===============
help_text

Display typical help text to the console
===============
*/
void help_text()
{
    printf("\tUsage: lttptrainer -switch [options...]\n\n");
    printf("\t-h\tDisplay this help text\n");
    printf("\t-i\tInspect an *.srm file containing the contents of an SRAM dump\n");
    printf("\t-s\tStart the RAM Tracing engine\n");
    printf("\t-v\tDisplay version information\n");
    printf("\nPlease refer to the README.md for more information.\n");
}
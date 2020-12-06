// sram.c

#include <stdio.h>
#include <windows.h>

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
sramdump_winProc

This is the Window Procedure for our sramdump feature
===============
*/
long __stdcall sramdump_winProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        sramdump_wndDraw(window);

        break;
    }
    case WM_DESTROY:
        // Clean up
        PostQuitMessage(0);
        return 0L;
    default:
        return DefWindowProc(window, msg, wp, lp);
    }
}

/*
===============
sramdump_wndDraw

Test
===============
*/
void sramdump_wndDraw(HWND window)
{
    RECT rc;
    PAINTSTRUCT ps;

    rc.left = 0;
    rc.top = 0;
    rc.right = 100;
    rc.bottom = 0;

    BeginPaint(window, &ps);
    GetClientRect(window, &rc);

    UINT format = DT_LEFT | DT_TOP;
    //DrawText(ps.hdc, byte_buffer, SLOTSIZE, &rc, format );
    DrawText(ps.hdc, dump, SLOTSIZE, &rc, format);

    //DrawText(ps.hdc, byte_buffer, SLOTSIZE, &rc, DT_TOP);
    EndPaint(window, &ps);
}

/*
===============
sramdump_window

Create the Win32 Window that will display the contents of the SRAM dump
===============
*/
void sramdump_window(void)
{
    const char *const myclass = "myclass";

    WNDCLASSEX wndclass = {
        sizeof(WNDCLASSEX),
        CS_DBLCLKS,
        sramdump_winProc,
        0,
        0,
        GetModuleHandle(0),
        LoadIcon(0, IDI_APPLICATION),
        LoadCursor(0, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        0,
        myclass,
        LoadIcon(0, IDI_APPLICATION)};

    if (RegisterClassEx(&wndclass))
    {
        HWND window = CreateWindowEx(
            0,
            myclass,
            "SRAM dump",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 1600, 960,
            NULL, NULL, GetModuleHandle(0), 0);
        if (window)
        {
            ShowWindow(window, SW_SHOWDEFAULT);
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0))
                DispatchMessage(&msg);
        }
    }
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

Go through the entire byte_buffer index and apply proprietary Nintendo LTTP logic to the data
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
            sprintf(dump+(index*2), "%02x", byte_buffer[index]);

            index++;

            if (index == SLOTSIZE)
                sramdump_window();
        }
    }

    free(byte_buffer);
    fclose(srm);
}
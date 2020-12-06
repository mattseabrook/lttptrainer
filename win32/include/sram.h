// sram.h

#ifndef SRAM_H
#define SRAM_H

#define SRAMSIZE 8192
#define SLOTSIZE 1280
// More definitions for SRAM memory locations, checksum etc

//===========================================================================

long __stdcall sramdump_winProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
void sramdump_wndDraw(HWND window);
void sramdump_window(void);
void sramdump_validate(char *file);
void sramdump(FILE *srm);

#endif
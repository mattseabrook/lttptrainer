// sram.h

#ifndef SRAM_H
#define SRAM_H

#define SRAMSIZE 8192
#define SLOTSIZE 1280
// More definitions for SRAM memory locations, checksum etc

//===========================================================================

void sramdump_validate(char *file);
void sramdump(FILE *srm);

#endif
# Introduction

Please note this is an extremely early initial commit, so things aren't lost before the switch to SDL.

The first step is to gather as much community documentation regarding A Link to the Past as possible, clean it up, and create a proper Knowledge Base / PDF for Developers.

No frameworks, working in C so that this can ultimately be used with real hardware. This project has many ambitious short & long-term goals regarding the usage of data traced in real-time from the memory of the SNES game Zelda: A Link to the Past. Future revisions of the document will go into further detail. 

## Status

**December 2020**:

win32 API is a net zero for my time, so I'm switching over to SDL for the next revision. 

## Table-of-Contents

1. [Getting Started](https://github.com/mattseabrook/lttptrainer#getting-started)
      1. Windows
2. [LTTP State RAM Debugging](https://github.com/mattseabrook/lttptrainer#lttp-state-ram-debugging)
      1. Manual solution from 2010
      2. Real-time tracing from SNES9x source
3. SRAM Map
      1. Notes
4. Cross-platform C code for colorized console output of SRAM bytes in hex
5. Code
      1. Moving a window using win32
6. Notes & Links

# Getting Started

Clone this repository and use `NMAKE` included with Microsoft Visual Studio to build this on the command-line. Ultimately this project is cross-platform so I wanted to stay away from the use of the Visual Studio IDE GUI. Use the **Developer Command Prompt for VS 2019** to interact with the C compiler on Microsoft Windows in a manner that is at least half-way decent

## Windows

**Compile**:

Go to the `build` directory and run `nmake all`. The `*.exe` will be located in `\bin\x86`

# LTTP State RAM Debugging

## Manual solution from 2010

**Prerequisites:**
| Software        | Description |
| --------------- | ----------- |
| snes9x lua      | x           |
| geiger debugger | x           |

**Steps:**
- Show Hex button
- Set Range: 7E0000 - 7FFFFF
- Dump (this dumps the entire memory of the SNES game)

## Real-time tracing from SNES9x source

Given the source code of an emulator, you could recompile from source to generate PDB file using Visual Studio.

**Notes:**
- DWARF or PDB file (information of where said data is located in memory)
- Compiler combined w/ Linker knows exactly where things are

# SRAM Map

The `*.srm` file represents memory addresses `$7E0000` through `$7FFFFF`

| Offset           | Description                                                                                      |
| ---------------- | ------------------------------------------------------------------------------------------------ |
| 0x00000000       | Slot 1 Bank 0x7E                                                                                 |
| 0x000004FE - 4FF | Inverse Checksum (is really a 16-bit number, not just two 8-bit numbers functioning separately.) |
| 0x00000F00       | Mirror of Slot 1                                                                                 |

## Notes

The SRAM save loading routing relies upon an inverse checksum. Additions to any byte in the .srm file, must be subtracted from that save game's checksum to maintain integrity. Failure to observe this precaution will cause the game to attempt to load the mirror copy. Should the mirror copy also fail the checksum verification, the save slot will be cleared.

If I add a value to a memory location with an even address, I must subtract from the even address of the inverse checksum. Example: Suppose I add $4 to $305. $305 is odd, so I SUBTRACT $4 from the odd checksum byte: $4FF. If I subtracted from $305, I must add to $4FF. This maintains the "balance" of the file and keeps it from being erased.

# SNES9X

x

- Recommend some snes9x settings to the user if applicable?
- Force the user to enter the path of their snes9x config file
- ...

## Send key(s) to the snes9x process in Windows

x

## Decompress snes9x save-state files

Given `sample.00*`:

```bash
# Run this command
file sample.000

# Output
sample.000: gzip compressed data, from TOPS/20, original size modulo 2^32 1164513
```

# Links

- Map of memory offsets in the Save State: <http://alttp.run/hacking/index.php?title=SRAM_Map>
- Dev Reading: <https://www.romhacking.net/forum/index.php?topic=22338.0>
- Z3 Compendium v1.8.4 PDF: <http://dl.dropbox.com/s/8v2vjem6gtaj2a4/Zelda%203%20Compendium%20v1.8.4.pdf> (somewhat out of date?)

# TODO

- Expand Makefile to have `make windows` , `make linux` , etc.
- Add `git` functionality to the makefile
- Add `make configure` to the makefile
- Implement `*.cfg` file in C.

# Errors

Things to work on, based on compile from: `02/20/2021`

```text
src/serve.c:57:48: warning: passing argument 4 of 'setsockopt' from incompatible pointer type [-Wincompatible-pointer-types]
   57 |     setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
      |                                                ^~~~
      |                                                |
      |                                                int *

-


In file included from src/serve.c:9:
/usr/x86_64-w64-mingw32/include/winsock2.h:999:88: note: expected 'const char *' but argument is of type 'int *'
  999 |   WINSOCK_API_LINKAGE int WSAAPI setsockopt(SOCKET s,int level,int optname,const char *optval,int optlen);
      |                                                                            ~~~~~~~~~~~~^~~~~~
```
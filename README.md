## Table-of-Contents

1. [Introduction](https://github.com/mattseabrook/lttptrainer#introduction)
   1. [lttptrainer](https://github.com/mattseabrook/lttptrainer#lttptrainer)
   2. [links-lab](https://github.com/mattseabrook/lttptrainer#links-lab)
2. [Getting Started](https://github.com/mattseabrook/lttptrainer#getting-started)
      1. [Windows](https://github.com/mattseabrook/lttptrainer#windows)
3. [Developer Notes](https://github.com/mattseabrook/lttptrainer#developer-notes)
   1. [LTTP State RAM Debugging](#lttp-state-ram-debugging)
      1. Manual solution from 2010
      2. Real-time tracing from SNES9x source
   2. [SRAM Map](https://github.com/mattseabrook/lttptrainer#sram-map)
      1. Notes
4. Cross-platform C code for colorized console output of SRAM bytes in hex
5. Code
      1. Moving a window using win32
6. Notes & Links
7. LICENSE & Copyright Information

# Introduction

Welcome to the `z3api`! This project has many ambitious short & long-term goals regarding the usage of data traced in real-time from the memory of the SNES game Zelda: A Link to the Past. No frameworks, and working in `C` so that this can ultimately be used with real hardware. 

As I gather as much community documentation regarding A Link to the Past as possible, clean it up, and create my own notes for this project, I am generating an up-to-date Offical PDF for 2021. It's a WIP included in this repo [here](#).

This software is compromised of a high-performance `C`-based server engine named `lttptrainer`, and an `http` front-end named `links-lab`. Cloning this repository, and following the below instructions in the [Getting Started](x) guide will automate the entire process of "hooking" into `snes9x` and performing a real-time memory trace. This data is fed at lightening-speed to the front-end of this software via the custom API I have developed.

## lttptrainer

`lttptrainer` is the "back-end" and interfaces directly with `snes9x` in a proprietary manner to capture both the active/current **SRAM** state of the game, and the entire **RAM** state of the machine in real-time (*of which the former is included.*) In this instance, machine specifically refers to the virtual representation of a Super Nintendo x specs.

For our purposes in Phase One, real-time is a literal interval of `250` milliseconds. Phase Two (TBD) will include performance measurements and enhancements.

As of 

# Getting Started for End-Users

Follow the instructions for your platform. Listed below are the pre-requisites and installation instructions for each platform- if you're **not** using the included `Dockerfile` (coming soon. For reference, the Docker container is based upon `Alpine Linux`, with a `mingw-w64-gcc` build system.)

## Windows

`nc` is not built-in to either the `CMD` or `POSH` environments of Windows. If you're starting from scratch, and not a Developer, then I recommend installing `ncat`, which you can read more about [here](https://nmap.org/ncat/). Feel free to use Python, Apache, or whatever `http://127.0.0.1:80` solution typically works for you. However please 

### Pre-requisites

| Pre-req   | Desc                                                                                                                     |
| --------- | ------------------------------------------------------------------------------------------------------------------------ |
| ncat      | https://nmap.org/ncat/                                                                                                   |
| snes9x    | No LUA or special Developer or Debugging builds required. At this time only the normal `v.x.x` is "officially" supported |
| alttp rom | Zelda no Densetsu - Kamigami no Triforce. At this time, I can't verify                                                   |

These are the specifications of the exact ROM image we are working with:

```text
Name: ZELDANODENSETSU
Speed: 20/SlowROM
ROM Map: LoROM
Type: 02
Kart contents: ROM+RAM+BAT
Header ROM Size: 8Mbits
Calculated ROM Size: 8 Mbits
SRAM size: 64Kbits (64Kbit)
Actual Checksum: CDC8
Header Checksum: CDC8
Header Checksum Compliment: 3237
Output: NTSC 60Hz
CRC32: 3322EFFC
Licensee: Nintendo
ROM Version: 1.0
Region: Japan
```

# Developer Notes

This section is a WIP containing Dev Notes.

## LTTP State RAM Debugging

### Manual solution from 2010

**Prerequisites:**
| Software        | Description |
| --------------- | ----------- |
| snes9x lua      | x           |
| geiger debugger | x           |

**Steps to reproduce:**
- Show Hex button
- Set Range: 7E0000 - 7FFFFF
- Dump (this dumps the entire memory of the SNES game)

### Real-time tracing from SNES9x source

Given the source code of an emulator, you could recompile from source to generate PDB file using Visual Studio.

**Notes:**
- DWARF or PDB file (information of where said data is located in memory)
- Compiler combined w/ Linker knows exactly where things are

## SRAM Map

The `*.srm` file represents memory addresses `$7E0000` through `$7FFFFF`

| Offset           | Description                                                                                      |
| ---------------- | ------------------------------------------------------------------------------------------------ |
| 0x00000000       | Slot 1 Bank 0x7E                                                                                 |
| 0x000004FE - 4FF | Inverse Checksum (is really a 16-bit number, not just two 8-bit numbers functioning separately.) |
| 0x00000F00       | Mirror of Slot 1                                                                                 |

### Notes

*This is copied from a wiki- Need to clean up the copy and cite credits, sources, etc.*

The SRAM save loading routing relies upon an inverse checksum. Additions to any byte in the .srm file, must be subtracted from that save game's checksum to maintain integrity. Failure to observe this precaution will cause the game to attempt to load the mirror copy. Should the mirror copy also fail the checksum verification, the save slot will be cleared.

If I add a value to a memory location with an even address, I must subtract from the even address of the inverse checksum. Example: Suppose I add $4 to $305. $305 is odd, so I SUBTRACT $4 from the odd checksum byte: $4FF. If I subtracted from $305, I must add to $4FF. This maintains the "balance" of the file and keeps it from being erased.

# SNES9X

This section contains my notes and useful information related to how my program interacts with `snes9x`. At a high-level we are not using LUA scripts, specially compiled emulators, or anything that is a barrier-to-entry for end-users.

## Design Notes

- Recommend some snes9x settings to the user if applicable?
- Force the user to enter the path of their snes9x config file
- The reason is, we will need to disable messages/HUD of snes9x since we will be spamming save-state

## Send key(s) to the snes9x process in Windows

One of the main things I want to do is send an `F5` hotkey every `500 ms` (*or more or less?*) to the `snes9x` process running in Windows, that essentially dumps the entire RAM state of the Super Nintendo to the hard disk. It's `gzip` compressed.

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
$ src/serve.c:57:48: warning: passing argument 4 of 'setsockopt' from incompatible pointer type [-Wincompatible-pointer-types]
   57 |     setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
      |                                                ^~~~
      |                                                |
      |                                                int *

$ In file included from src/serve.c:9:
/usr/x86_64-w64-mingw32/include/winsock2.h:999:88: note: expected 'const char *' but argument is of type 'int *'
  999 |   WINSOCK_API_LINKAGE int WSAAPI setsockopt(SOCKET s,int level,int optname,const char *optval,int optlen);
      |                                                                            ~~~~~~~~~~~~^~~~~~
```
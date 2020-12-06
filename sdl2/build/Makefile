#define macros
EXECUTABLE_NAME = lttptrainer.exe
DIR_SRC = ..\src
DIR_INCLUDE = ..\include
DIR_BIN = ..\bin
DIR_BIN_X86 = $(DIR_BIN)\x86
DIR_INTERMEDIATE = ..\intermediate
DIR_INTERMEDIATE_X86 = $(DIR_INTERMEDIATE)\x86
# SDL2
SDL_INCLUDE = C:\sdl2\include

SRC_FILES= \
  $(DIR_SRC)\main.c \
  $(DIR_SRC)\sram.c

{$(DIR_SRC)}.c{$(DIR_INTERMEDIATE_X86)}.obj ::
        @echo Compiling...
 cl /c /EHsc /Fo$(DIR_INTERMEDIATE_X86)\ /I$(DIR_INCLUDE) /I$(SDL_INCLUDE) $<

$(EXECUTABLE_NAME) : $(DIR_INTERMEDIATE_X86)\*.obj
   @echo Linking $(EXECUTABLE_NAME)...
   link /out:$(DIR_BIN_X86)\$(EXECUTABLE_NAME) $(DIR_INTERMEDIATE_X86)\*.obj /subsystem:console user32.lib c:\sdl2\sdl2.lib

# build application
lttptrainer: $(EXECUTABLE_NAME)

# create output directories
create_dirs:
 @if not exist $(DIR_BIN_X86) mkdir $(DIR_BIN_X86)
 @if not exist $(DIR_INTERMEDIATE_X86) mkdir $(DIR_INTERMEDIATE_X86)

# delete output directories
clean:
 @if exist $(DIR_BIN) rmdir /S /Q $(DIR_BIN)
 @if exist $(DIR_INTERMEDIATE) rmdir /S /Q $(DIR_INTERMEDIATE)

# create directories and build application
all: clean create_dirs lttptrainer
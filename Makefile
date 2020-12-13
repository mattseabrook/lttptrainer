# Makefile for lttptrainer

CC = gcc
CFLAGS = -Wall

# Define Includes
INCLUDES = -Iinclude

# Define Libs
#LIBS = -lcrypto

# Define C++ source files
SRC = $(wildcard src/*.c)

# Define C object files
OBJ = $(SRC:.c=.o)

# Define main executable
TARGET = lttptrainer.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJ)

# Suffix replacement rule
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) src/*.o *~ $(TARGET)

# Libs: $(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJ) $(LIBS)
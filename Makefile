CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS ?= -lm

TARGET = shooting.exe
OBJECTS = main.o BomArray.o DrawObject.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

main.o: main.c BomArray.h DrawObject.h
	$(CC) $(CFLAGS) -c -o $@ main.c

BomArray.o: BomArray.c BomArray.h
	$(CC) $(CFLAGS) -c -o $@ BomArray.c

DrawObject.o: DrawObject.c DrawObject.h
	$(CC) $(CFLAGS) -c -o $@ DrawObject.c

clean:
	$(RM) $(OBJECTS) $(TARGET)

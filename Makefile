CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS ?= -lm

TARGET = shooting.exe
OBJECTS = main.o ParticleArray.o DrawObject.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

main.o: main.c ParticleArray.h DrawObject.h
	$(CC) $(CFLAGS) -c -o $@ main.c

ParticleArray.o: ParticleArray.c ParticleArray.h
	$(CC) $(CFLAGS) -c -o $@ ParticleArray.c

DrawObject.o: DrawObject.c DrawObject.h
	$(CC) $(CFLAGS) -c -o $@ DrawObject.c

clean:
	$(RM) $(OBJECTS) $(TARGET)

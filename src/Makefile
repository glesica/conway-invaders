CC=gcc
CFLAGS=-Wall -std=c99 -g
INCLUDES=
LIBS=-lGL -lglut -lGLU -lm
FILES=invader.c vector.c lifeform.c lfdraw.c util.c ship.c bullets.c game.c
TARGET=invader

all: clean build

clean:
	-rm -f $(TARGET)

build: $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LIBS)

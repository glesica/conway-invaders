CC=gcc
CFLAGS=-Wall -std=c99 -g -O3
INCLUDES=
FILES=invader.c vector.c lifeform.c lfdraw.c util.c ship.c bullets.c game.c
TARGET=invader
ifeq ($(shell uname),Darwin)
	LIBS=-framework OpenGL -framework GLUT
else
	LIBS=-lGL -lglut -lGLU -lm
endif

.PHONY: all clean build

all: build

clean:
	-rm -f $(TARGET)

build: $(TARGET)

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LIBS)


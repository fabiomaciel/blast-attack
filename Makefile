.PHONY: build clean run

CFLAGS := -Wall

ifeq ($(OS),Windows_NT)
	CC := gcc
	CFLAGS +=	-lmingw32 -lSDL2main -lSDL2 \
		-IG:\dev\mingw\include\SDL2
else
	CFLAGS += -Wall $(shell pkg-config sdl2 --cflags --libs)
endif

build:
	$(CC) src/main.c -o main $(CFLAGS)  

clean:
	rm ./game;

run:
	./game;

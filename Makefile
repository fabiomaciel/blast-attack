TARGET      ?= blast_attack
SOURCE_DIR  ?= ./src
BUILD_DIR   ?= ./build

CFLAGS := -Wall
OBJS   := $(BUILD_DIR)/main.o

ifeq ($(OS),Windows_NT)
	CC := gcc
	CFLAGS +=	-lmingw32 -lSDL2main -lSDL2 \
		-IG:\dev\mingw\include\SDL2
else
	CFLAGS += -Wall $(shell pkg-config sdl2 --cflags --libs)
endif

.PHONY: build clean run $(TARGET)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm $(TARGET)

run:
	./$(TARGET)

TARGET       ?= blast_attack
SOURCE_DIR   ?= ./src
TEST_DIR     ?= ./test
LIB_DIR      ?= ./lib
BUILD_DIR    ?= ./build

CFLAGS       := -Wall -lm
CFLAGS_TEST  := -Isrc -Ithird_party -Llib -lmunit
SRCS         := $(wildcard $(SOURCE_DIR)/*.c)
SRCS_TEST    := $(wildcard $(TEST_DIR)/*.c)
OBJS         := $(patsubst $(SOURCE_DIR)/%.c,    $(BUILD_DIR)/%.o, $(SRCS))
TESTS        := $(patsubst $(TEST_DIR)/%-test.c, $(TEST_DIR)/%,    $(SRCS_TEST))

ifeq ($(OS),Windows_NT)
	CC := gcc
	CFLAGS +=	-lmingw32 -lSDL2main -lSDL2 \
		-IG:\dev\mingw\include\SDL2
else
	CFLAGS += $(shell pkg-config sdl2 --cflags --libs)
endif

.PHONY: build clean run test $(TARGET)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

$(BUILD_DIR):
	@mkdir -p $@

$(LIB_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/%-test: $(BUILD_DIR)/%.o $(TEST_DIR)/%-test.c
	$(CC) $(CFLAGS) $(CFLAGS_TEST) $? -o $@ 

$(TEST_DIR)/%: $(TEST_DIR)/%-test
	./$@-test

test: lib/libmunit.so $(BUILD_DIR) $(TESTS) 

lib/libmunit.so: $(LIB_DIR) third_party/munit/munit.c
	$(CC) -Wall -fpic -c third_party/munit/munit.c -shared -o lib/libmunit.so

checkstyle:
	clang-format -dry-run -Werror */**.c */**.h

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIB_DIR)
	@rm $(TARGET)

run: all
	./$(TARGET)

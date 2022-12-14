CC := gcc
RM := del
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
DATABASE_DIR := database

EXE := $(BIN_DIR)/main.exe
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -W -Wall -pedantic
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean run

all: $(EXE) run

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

clean:
	@$(RM) /Q $(BIN_DIR) $(OBJ_DIR) $(DATABASE_DIR)

run:
	.\$(EXE)

-include $(OBJ:.o=.d)
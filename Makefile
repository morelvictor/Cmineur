CFLAGS = -D_XOPEN_SOURCE_EXTENDED
SRC_DIR = src
BIN_DIR = .bin
CC = gcc
FLAGS = -Wall
INCLUDES = -lncurses
EXE = cmineur

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))

$(EXE): $(OBJ) $(BIN_DIR) $(SRC_DIR)
	$(CC) $(LDFLAGS) $(FLAGS) $(INCLUDES) $(OBJ) -o $(EXE)

$(BIN_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(BIN_DIR)
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

$(SRC_DIR):
	@mkdir -p $(SRC_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)/$(SRC_DIR)

.PHONY: clean

clean:
	rm -rf $(EXE) $(BIN_DIR)


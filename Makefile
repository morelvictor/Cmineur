
SRC_DIR = src
BIN_DIR = .bin
CC = gcc
FLAGS = -Wall
EXE = demineur

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))

$(EXE): $(OBJ) $(BIN_DIR) $(SRC_DIR)
	$(CC) $(OBJ) -o $(EXE) $(FLAGS)

$(BIN_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(BIN_DIR)
	$(CC) -c $< -o $@ $(FLAGS)

$(SRC_DIR):
	@mkdir -p $(SRC_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)/$(SRC_DIR)

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

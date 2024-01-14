COMP = gcc
FLAGS = -lm -o
SRC_DIR = .
LIB_DIR = lib
UTILITIES_DIR = utilities
BIN_DIR = bin

# Lista de archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTILITIES_DIR)/*.c)

# Lista de archivos de cabecera
HDRS = $(wildcard $(LIB_DIR)/*.h)

create_server: 
	$(COMP) $(FLAGS) $(BIN_DIR)/Server $(SRCS) $(HDRS)


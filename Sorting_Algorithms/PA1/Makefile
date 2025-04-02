CC = gcc
CFLAGS = -std=gnu11 -Wall 
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

all: ${BIN_DIR}/pa1.out

$(OBJ_DIR):m
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)


${OBJ_DIR}/evalenum.o: ${SRC_DIR}/evalenum.c 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/evalenum.c  -o ${OBJ_DIR}/evalenum.o

${BIN_DIR}/pa1.out: ${OBJ_DIR}/evalenum.o 
	$(CC) $(CFLAGS) ${OBJ_DIR}/evalenum.o -o ${BIN_DIR}/pa1.out

clean:
	rm -f $(OBJ_DIR)/evalenum.o $(BIN_DIR)/pa1.out
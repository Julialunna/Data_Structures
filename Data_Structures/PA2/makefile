CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all: ${BIN_DIR}/pa2.out

$(OBJ_DIR):m
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

${BUILD_DIR}/adjacency_list.o: ${INCLUDE_DIR}/adjacency_list.hpp ${SRC_DIR}/adjacency_list.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/adjacency_list.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/adjacency_list.o

${BUILD_DIR}/graph.o: ${INCLUDE_DIR}/graph.hpp ${INCLUDE_DIR}/adjacency_list.hpp ${SRC_DIR}/graph.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/graph.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/graph.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/graph.hpp  ${INCLUDE_DIR}/adjacency_list.hpp ${SRC_DIR}/main.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/pa2.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/adjacency_list.o ${BUILD_DIR}/graph.o 
	@mkdir -p ${BIN_DIR}
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/adjacency_list.o ${BUILD_DIR}/graph.o -o ${BIN_DIR}/pa2.out


clean:
	rm -f $(OBJ_DIR)/graph.o $(OBJ_DIR)/adjacency_list.o $(BIN_DIR)/pa2.out
CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all: ${BIN_DIR}/pa2.out

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${BUILD_DIR}/node.o: ${INCLUDE_DIR}/node.hpp ${SRC_DIR}/node.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/node.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/node.o

${BUILD_DIR}/list.o: ${INCLUDE_DIR}/list.hpp ${SRC_DIR}/list.cpp ${INCLUDE_DIR}/node.hpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/list.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/list.o

${BUILD_DIR}/node_adjacency.o: ${INCLUDE_DIR}/node_adjacency.hpp ${SRC_DIR}/node_adjacency.cpp ${INCLUDE_DIR}/list.hpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/node_adjacency.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/node_adjacency.o

${BUILD_DIR}/list_adjacency.o: ${INCLUDE_DIR}/list_adjacency.hpp ${SRC_DIR}/list_adjacency.cpp ${INCLUDE_DIR}/node_adjacency.hpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/list_adjacency.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/list_adjacency.o

${BUILD_DIR}/graph.o: ${INCLUDE_DIR}/graph.hpp ${INCLUDE_DIR}/list_adjacency.hpp ${SRC_DIR}/graph.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/graph.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/graph.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/graph.hpp ${INCLUDE_DIR}/list_adjacency.hpp ${SRC_DIR}/main.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/pa2.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/list_adjacency.o ${BUILD_DIR}/graph.o ${BUILD_DIR}/node_adjacency.o
	@mkdir -p ${BIN_DIR}
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/list_adjacency.o ${BUILD_DIR}/graph.o ${BUILD_DIR}/node_adjacency.o -o ${BIN_DIR}/pa2.out

clean:
	rm -f ${BUILD_DIR}/*.o ${BIN_DIR}/pa2.out
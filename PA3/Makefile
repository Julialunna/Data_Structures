CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all:${BIN_DIR}/pa3.out

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${BUILD_DIR}/heap.o: ${INCLUDE_DIR}/heap.hpp ${SRC_DIR}/heap.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/heap.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/heap.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/heap.hpp ${SRC_DIR}/main.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/pa3.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/heap.o  
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/heap.o -o ${BIN_DIR}/pa3.out
clean:
	rm -f ${BUILD_DIR}/*.o ${BIN_DIR}/pa3.out
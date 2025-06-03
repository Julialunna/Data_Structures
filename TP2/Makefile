CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all: ${BIN_DIR}/tp2.out

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${BUILD_DIR}/Stack.o: ${INCLUDE_DIR}/Stack.hpp ${SRC_DIR}/Stack.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/Stack.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/Stack.o

${BUILD_DIR}/List.o: ${INCLUDE_DIR}/List.hpp  ${SRC_DIR}/List.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/List.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/List.o

${BUILD_DIR}/Queue.o: ${INCLUDE_DIR}/Queue.hpp  ${SRC_DIR}/Queue.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/Queue.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/Queue.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/List.hpp  ${INCLUDE_DIR}/Stack.hpp ${SRC_DIR}/main.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/tp2.out: ${BUILD_DIR}/main.o  ${BUILD_DIR}/Stack.o ${BUILD_DIR}/List.o ${BUILD_DIR}/Queue.o
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/Stack.o  ${BUILD_DIR}/List.o ${BUILD_DIR}/Queue.o -o ${BIN_DIR}/tp2.out

valgrind: ${BIN_DIR}/tp2.out
	valgrind --leak-check=full --track-origins=yes ./${BIN_DIR}/tp2.out
clean:
	rm -rf ${BUILD_DIR}/*.o ${BIN_DIR}/tp2.out
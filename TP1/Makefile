CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all:${SRC_DIR}/main

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${BUILD_DIR}/OperationsCounter.o: ${INCLUDE_DIR}/OperationsCounter.hpp ${SRC_DIR}/OperationsCounter.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/OperationsCounter.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/OperationsCounter.o

${BUILD_DIR}/UniversalSorter.o: ${INCLUDE_DIR}/UniversalSorter.hpp ${INCLUDE_DIR}/OperationsCounter.hpp ${INCLUDE_DIR} ${SRC_DIR}/UniversalSorter.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/UniversalSorter.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/UniversalSorter.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/UniversalSorter.hpp ${INCLUDE_DIR} ${SRC_DIR}/main.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${SRC_DIR}/main: ${BUILD_DIR}/main.o ${BUILD_DIR}/UniversalSorter.o  ${BUILD_DIR}/OperationsCounter.o 
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/UniversalSorter.o ${BUILD_DIR}/OperationsCounter.o -o ${SRC_DIR}/main

clean:
	rm -f ${BUILD_DIR}/*.o ${SRC_DIR}/main
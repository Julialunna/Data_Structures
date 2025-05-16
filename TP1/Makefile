CC = g++
CFLAGS = -g  -std=c++11  -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all:${BIN_DIR}/tp1.out


${BUILD_DIR}/OperationsCounter.o: ${INCLUDE_DIR}/OperationsCounter.hpp ${SRC_DIR}/OperationsCounter.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/OperationsCounter.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/OperationsCounter.o

${BUILD_DIR}/Sorter.o: ${INCLUDE_DIR}/Sorter.hpp ${SRC_DIR}/Sorter.cpp ${INCLUDE_DIR}/OperationsCounter.hpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/Sorter.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/Sorter.o

${BUILD_DIR}/UniversalSorter.o: ${INCLUDE_DIR}/UniversalSorter.hpp ${BUILD_DIR}/Sorter.o ${INCLUDE_DIR}/OperationsCounter.hpp ${INCLUDE_DIR} ${SRC_DIR}/UniversalSorter.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/UniversalSorter.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/UniversalSorter.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/UniversalSorter.hpp ${INCLUDE_DIR}/OperationsCounter.hpp ${INCLUDE_DIR}/Sorter.hpp ${SRC_DIR}/main.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o


${BIN_DIR}/tp1.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/UniversalSorter.o  ${BUILD_DIR}/OperationsCounter.o ${BUILD_DIR}/Sorter.o
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/UniversalSorter.o ${BUILD_DIR}/OperationsCounter.o ${BUILD_DIR}/Sorter.o -o ${BIN_DIR}/tp1.out

valgrind: ${BIN_DIR}/tp1.out
	valgrind --leak-check=full ${BIN_DIR}/tp1.out

clean:
	rm -f ${BUILD_DIR}/*.o ${BIN_DIR}/tp1.out
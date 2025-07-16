CC = g++
CFLAGS = -g -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

all: ${BIN_DIR}/tp3.out

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${BUILD_DIR}/EventStorage.o: ${INCLUDE_DIR}/EventStorage.hpp ${SRC_DIR}/EventStorage.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/EventStorage.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/EventStorage.o

${BUILD_DIR}/ClientsStorage.o: ${INCLUDE_DIR}/ClientsStorage.hpp ${SRC_DIR}/ClientsStorage.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/ClientsStorage.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/ClientsStorage.o

${BUILD_DIR}/PackageStorage.o: ${INCLUDE_DIR}/PackageStorage.hpp ${SRC_DIR}/PackageStorage.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/PackageStorage.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/PackageStorage.o
	
${BUILD_DIR}/QueriesExecutor.o: ${INCLUDE_DIR}/QueriesExecutor.hpp ${INCLUDE_DIR}/EventStorage.hpp ${INCLUDE_DIR}/ClientsStorage.hpp ${INCLUDE_DIR}/PackageStorage.hpp ${SRC_DIR}/QueriesExecutor.cpp 
	$(CC) $(CFLAGS) -c ${SRC_DIR}/QueriesExecutor.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/QueriesExecutor.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/EventStorage.hpp ${INCLUDE_DIR}/QueriesExecutor.hpp ${SRC_DIR}/main.cpp
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/tp3.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/EventStorage.o ${BUILD_DIR}/QueriesExecutor.o  ${BUILD_DIR}/ClientsStorage.o ${BUILD_DIR}/PackageStorage.o | ${BIN_DIR}
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/EventStorage.o ${BUILD_DIR}/QueriesExecutor.o ${BUILD_DIR}/ClientsStorage.o ${BUILD_DIR}/PackageStorage.o -o ${BIN_DIR}/tp3.out

valgrind: ${BIN_DIR}/tp3.out
	valgrind --leak-check=full --track-origins=yes ./${BIN_DIR}/tp3.out entrada.txt

clean:
	rm -rf ${BUILD_DIR}/*.o ${BIN_DIR}/tp3.out

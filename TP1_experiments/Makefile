# Parâmetros de compilação
KEYSIZE      ?= 5
REGISTERSIZE ?= 20
VETSIZE      ?= 200

# Nome do sufixo para os binários e objetos
SUFFIX = k$(KEYSIZE).r$(REGISTERSIZE).v$(VETSIZE)

# Ferramentas e diretórios
CC = g++
CFLAGS = -g -std=c++11 -Wall \
         -DKEYSIZE=$(KEYSIZE) \
         -DREGISTERSIZE=$(REGISTERSIZE) \
         -DVETSIZE=$(VETSIZE)
SRC_DIR     = src
BUILD_DIR   = obj/$(SUFFIX)
INCLUDE_DIR = include
BIN_DIR     = bin

# Alvo principal
all: $(BIN_DIR)/tp1.$(SUFFIX).out

# Diretórios
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilações
$(BUILD_DIR)/OperationsCounter.o: $(INCLUDE_DIR)/OperationsCounter.hpp $(SRC_DIR)/OperationsCounter.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/OperationsCounter.cpp -I$(INCLUDE_DIR) -o $@

$(BUILD_DIR)/Sorter.o: $(INCLUDE_DIR)/Sorter.hpp $(SRC_DIR)/Sorter.cpp $(INCLUDE_DIR)/OperationsCounter.hpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Sorter.cpp -I$(INCLUDE_DIR) -o $@

$(BUILD_DIR)/UniversalSorter.o: $(INCLUDE_DIR)/UniversalSorter.hpp $(SRC_DIR)/UniversalSorter.cpp $(BUILD_DIR)/Sorter.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UniversalSorter.cpp -I$(INCLUDE_DIR) -o $@

$(BUILD_DIR)/main.o: $(INCLUDE_DIR)/UniversalSorter.hpp $(INCLUDE_DIR)/OperationsCounter.hpp $(INCLUDE_DIR)/Sorter.hpp $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $@

$(BIN_DIR)/tp1.$(SUFFIX).out: $(BUILD_DIR)/main.o $(BUILD_DIR)/UniversalSorter.o $(BUILD_DIR)/OperationsCounter.o $(BUILD_DIR)/Sorter.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Valgrind com executável atual
valgrind: all
	valgrind --leak-check=full $(BIN_DIR)/tp1.$(SUFFIX).out

# Limpa apenas a configuração atual
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)/tp1.$(SUFFIX).out

# Limpa tudo
clean-all:
	rm -rf obj bin

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
#include "UniversalSorter.hpp"

int main()
{

    float threshold_cost = 0, comparison_coefficient = 0, movimentation_coefficient = 0, call_coefficient = 0;
    int seed = 1, num_of_keys = 0;
    std::string file_name, line;
    srand48(seed);
    
    std::cin >> file_name;
    //file_name = "entrada.txt";
    std::ifstream file(file_name);

    if (!file) {
        std::cerr << "Err ao abrir o arquivo.\n";
        return 1;
    }
    
    file >> threshold_cost;
    file >> comparison_coefficient;
    file >> movimentation_coefficient;
    file >> call_coefficient;
    file >> num_of_keys;

    
    UniversalSorter *universal_sorter = new UniversalSorter(comparison_coefficient, movimentation_coefficient, call_coefficient);
    int *vet = (int *)malloc(num_of_keys * sizeof(int));
    for (int i = 0; i < num_of_keys; ++i)
    {
        vet[i] = static_cast<int>(drand48() * num_of_keys);
    }
    
    int partition_threshold = universal_sorter->determine_partition_threshold(vet, num_of_keys, threshold_cost);
    int break_threshold = universal_sorter->determine_break_threshold(partition_threshold, vet, num_of_keys, threshold_cost);
    

    free(vet);
    delete(universal_sorter);
    file.close();

    return 0;
}
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
#include "UniversalSorter.hpp"

int main(int argc, char*argv[])
{

    double threshold_cost = 0, comparison_coefficient = 0, movimentation_coefficient = 0, call_coefficient = 0;
    int seed = 0, num_of_keys = 0;
    std::string file_name, line;
    
    if (argc != 2) {
        std::cerr << "Erro: file name needed" << std::endl;
        return 1;
    }

   file_name = argv[1];

    std::ifstream file(file_name);
    
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return 1;
    }
    
    file >> seed;
    file >> threshold_cost;
    file >> comparison_coefficient;
    file >> movimentation_coefficient;
    file >> call_coefficient;
    file >> num_of_keys;
    
    srand48(seed);
    
    UniversalSorter universal_sorter(comparison_coefficient, movimentation_coefficient, call_coefficient);
    int *vet = new int[num_of_keys]; 

    for(int i=0;i<num_of_keys;i++){
        file >> vet[i];
    }
    std::cout<<"size "<<num_of_keys<<" seed "<<seed<<" breaks "<<universal_sorter.count_breaks(vet, num_of_keys)<<std::endl;
    //std::cout<<std::endl;
    
    int partition_threshold = universal_sorter.determine_partition_threshold(vet, num_of_keys, threshold_cost);
    universal_sorter.determine_break_threshold(partition_threshold, vet, num_of_keys, threshold_cost, seed);

    delete(vet);
    file.close();

    return 0;
}
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "UniversalSorter.hpp"

int main()
{

    float threshold_cost = 0, comparison_coefficient = 0, movimentation_coefficient = 0, call_coefficient = 0;
    int seed = 1, num_of_keys = 0;
    srand48(seed);
    
    std::cin >> threshold_cost >> comparison_coefficient >> movimentation_coefficient >> call_coefficient >> num_of_keys;
    
    UniversalSorter universal_sorter(comparison_coefficient, movimentation_coefficient, call_coefficient);
    
    int *vet = (int *)malloc(num_of_keys * sizeof(int));
    for (int i = 0; i < num_of_keys; ++i)
    {
        vet[i] = static_cast<int>(drand48() * num_of_keys);
    }

    int num_breaks = 0;
    num_breaks = universal_sorter.count_breaks(vet, num_of_keys);


    free(vet);

    return 0;
}
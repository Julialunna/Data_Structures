#ifndef UNIVERSAL_SORTER_HPP
#define UNIVERSAL_SORTER_HPP
#include "OperationsCounter.hpp"
#include "Sorter.hpp"

static const int max_quantity_of_partitions = 6;
struct PartitionStatistics{
    float cost;
    int num_of_comparisons;
    int num_of_calls;
    int num_of_movements;
    int partition_size;
};
struct BreaksStatistics{
    float cost;
    int num_of_comparisons;
    int num_of_calls;
    int num_of_movements;
    int partition_size;
};
class UniversalSorter{
    private:
    OperationsCounter operation_counter;
    Sorter sorter;
    float comparison_coefficient;
    float movimentation_coefficient;
    float call_coefficient;

    public:
    UniversalSorter(float comparison_coefficient,
    float movimentation_coefficient, float call_coefficient);
    int count_breaks(int *vet, int size);
    void universal_sorter(int *vector, int vector_size, int min_partition_size, int breaks_threshold);
    int determine_partition_threshold (int *v, int v_size, int cost_threshold);
    void print_statics(Statistics statistics);
    int find_min_cost(Statistics *statistics, int num_partitions);
    float calculate_cost ();
    void register_statistics(Statistics statistics [max_quantity_of_partitions], int num_partitions, int partition_size);
    void print_final_results(int num_partitions, int best_partition, float difference_max_min_cost);
    void find_new_range(int min_cost_index,  int *min_size_range , int *max_size_range, int num_sizes, int* step);
    int find_partition_size(int index, int min_partition_size, int step);
    int find_index_by_partition(int partition_size, int min_partition_size, int step);
    int determine_break_threshold(int partition_thershold, int* vet, int vet_size, int cost_threshold);
    void create_breaks(int *vet,int num_of_breaks, int vet_size);
};
#endif
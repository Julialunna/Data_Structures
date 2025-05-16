#ifndef UNIVERSAL_SORTER_HPP
#define UNIVERSAL_SORTER_HPP
#include "OperationsCounter.hpp"
#include "Sorter.hpp"

static const int max_quantity_of_partitions = 7;
struct PartitionStatistics{
    double cost;
    int num_of_comparisons;
    int num_of_calls;
    int num_of_movements;
    int partition_size;
};
struct BreaksStatistics{
    double cost;
    int num_of_comparisons;
    int num_of_calls;
    int num_of_movements;
    int num_breaks;
};
class UniversalSorter{
    private:
    OperationsCounter operation_counter;
    Sorter sorter;
    double comparison_coefficient;
    double movimentation_coefficient;
    double call_coefficient;

    public:
    UniversalSorter(double comparison_coefficient,
    double movimentation_coefficient, double call_coefficient);
    int count_breaks(int *vet, int size);
    void universal_sorter(int *vector, int vector_size, int min_partition_size, int breaks_threshold);
    int determine_partition_threshold (int *v, int v_size, double cost_threshold);
    void print_partition_statics(PartitionStatistics *partition_statistics);
    int find_min_cost(PartitionStatistics *statistics, int num_partitions);
    double calculate_cost ();
    void register_partition_statistics(PartitionStatistics statistics [max_quantity_of_partitions], int num_partitions, int partition_size);
    void print_final_results(int num_partitions, int best_partition, double difference_max_min_cost);
    void find_new_range(int min_cost_index,  int *min_size_range , int *max_size_range, int num_sizes, int* step);
    int find_partition_size(int index, int min_partition_size, int step);
    int find_index_by_partition(int partition_size, int min_partition_size, int step);
    void determine_break_threshold(int partition_thershold, int* vet, int vet_size, double cost_threshold, int seed);
    void shuffleVector(int *vet, int vet_size, int num_breaks, int seed);
    void register_break_statistics(BreaksStatistics *statistics_quick_sort, int num_breaks);
    void print_statics_quick(BreaksStatistics breaks_statistics);
    void print_statics_insertion(BreaksStatistics breaks_statistics);
    int find_min_cost_breaks(BreaksStatistics *statistics_quick_sort, BreaksStatistics *statistics_insertion_sort, int num_breaks);
    void print_break_thershold_result(int partition_size, double difference_max_min_size, int num_size_breaks);

};
#endif
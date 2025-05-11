#include "OperationsCounter.hpp"

struct Statics{
    float cost;

};
class UniversalSorter{
    private:
    OperationsCounter operation_counter;
    float comparison_coefficient;
    float movimentation_coefficient;
    float call_coefficient;

    public:
    UniversalSorter(float comparison_coefficient,
    float movimentation_coefficient, float call_coefficient);
    int count_breaks(int *vet, int size);
    void insertionSort(int v[], int l, int r);
    int median(int a, int b, int c);
    void swap(int *xp, int *yp);
    void partition3(int *A, int l, int r, int *i, int *j);
    void quickSort3Ins(int *A, int l, int r, int partition_threshold);
    void universal_sorter(int *vector, int vector_size, int min_partition_size, int breaks_threshold);
    int determine_partition_threshold (int *v, int v_size, int cost_threshold);
    void print_statics(float cost, int partition_size);
    int find_min_cost(float *costs, int num_partitions);
    float calculate_cost ();
    void print_results(int num_partitions, int best_partition, float difference_max_min_cost);
    void find_new_partition_range(int min_cost_index,  int *min_partition_size_range , int *max_partition_size_range, int num_partitions, int* step);
    int find_partition_size(int index, int min_partition_size, int step);
    int find_index_by_partition(int partition_size, int min_partition_size, int step);
};
#include "OperationsCounter.hpp"

typedef struct Statics{
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
    void print_statics();
};
#ifndef SORTER_HPP
#define SORTER_HPP
#include "OperationsCounter.hpp"

class Sorter{
    public:
    void insertionSort(item *v, int l, int r, OperationsCounter *operation_counter);
    item median(item a, item b, item c);
    void swap(item *xp, item *yp, OperationsCounter *operation_counter);
    void partition3(item *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter);
    void quickSort3Ins(item *A, int l, int r, int partition_threshold, OperationsCounter *operation_counter);
    void quickSort3(item *A, int l, int r, OperationsCounter *operation_counter);
    void partition(item *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter);
    void quickSort(item *A, int l, int r, OperationsCounter *operation_counter);
};
#endif
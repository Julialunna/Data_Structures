
#ifndef SORTER_HPP
#define SORTER_HPP
#include "OperationsCounter.hpp"
class Sorter{
    public:
    void insertionSort(int v[], int l, int r, OperationsCounter *s);
    int median(int a, int b, int c);
    void swap(int *xp, int *yp, OperationsCounter *s);
    void partition3(int *A, int l, int r, int *i, int *j, OperationsCounter *s);
    void quickSort3Ins(int *A, int l, int r, int partition_threshold, OperationsCounter *s);
    void partition(int *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter);
    void quickSort(int *A, int l, int r, OperationsCounter  *operation_counter);
};
#endif
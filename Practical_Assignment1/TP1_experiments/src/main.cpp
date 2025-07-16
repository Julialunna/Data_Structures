#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <chrono>
#include <tuple>
#include <iomanip>
#include "UniversalSorter.hpp"
#include "Sorter.hpp"
#include"OperationsCounter.hpp"

struct DataPoint
{
    int cmp;
    int move;
    int calls;
    double cost;
};

#define NUM_DATA 3

void linear_regression_qr(DataPoint *data, int n, double *a, double *b, double *c)
{
    // Monta matriz A (n x 3) e vetor y
    long double* A = new long double[n*3];
    long double* y = new long double[n];
    for(int i=0;i<n;++i) {
        A[i*3 + 0] = data[i].cmp;
        A[i*3 + 1] = data[i].move;
        A[i*3 + 2] = data[i].calls;
        y[i]      = data[i].cost;
    }
    // Q (n x 3) e R (3 x 3)
    long double* Q = new long double[n*3];
    long double R[3][3] = {{0}};

    // Gram-Schmidt
    for(int j=0;j<3;++j) {
        // v = A[:,j]
        long double* v = new long double[n];
        for(int i=0;i<n;++i) v[i] = A[i*3 + j];
        // Subtrai projeções
        for(int k=0;k<j;++k) {
            long double dot=0;
            for(int i=0;i<n;++i) dot += Q[i*3 + k] * A[i*3 + j];
            R[k][j] = dot;
            for(int i=0;i<n;++i) v[i] -= dot * Q[i*3 + k];
        }
        // Norm
        long double norm=0;
        for(int i=0;i<n;++i) norm += v[i]*v[i];
        norm = std::sqrt(norm);
        R[j][j] = norm;
        // Q[:,j] = v / norm
        for(int i=0;i<n;++i) Q[i*3 + j] = v[i]/norm;
        delete[] v;
    }
    // Compute Qt * y
    long double Qt_y[3] = {0};
    for(int j=0;j<3;++j) {
        long double sum=0;
        for(int i=0;i<n;++i) sum += Q[i*3 + j] * y[i];
        Qt_y[j] = sum;
    }
    // Solve R x = Qt_y by back substitution
    long double x[3] = {0};
    for(int i=2;i>=0;--i) {
        long double s = Qt_y[i];
        for(int j=i+1;j<3;++j) s -= R[i][j] * x[j];
        x[i] = s / R[i][i];
    }
    *a = (double)x[0];
    *b = (double)x[1];
    *c = (double)x[2];
    delete[] A; delete[] Q; delete[] y;
}

void copy_vet(item vet[VETSIZE], item vet_copy[VETSIZE])
{
    for (int i = 0; i < VETSIZE ; i++)
    {
        vet_copy[i] = vet[i];
    }
}

template <typename Func>
double medir_tempo_ms(Func func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();  
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count(); 
}

void create_disorder(UniversalSorter universal_sorter, item *vet, int break_threshold, int partition_threshold){
    if(VETDISORDER == 100){
        // for(int i =0;i<VETSIZE/2;i++){
        //     item temp = vet[i];
        //     vet[i] = vet[VETSIZE - 1 - i];
        //     vet[VETSIZE - 1 - i] = temp;
        // }
        universal_sorter.shuffleVector(vet, VETSIZE, VETSIZE-1, 1);
    }else if(VETDISORDER == 40){
        int num_breaks = 0.4 * VETSIZE;
        universal_sorter.shuffleVector(vet, VETSIZE, num_breaks, 1);
    }else if(VETDISORDER == 60){
        int num_breaks = 0.6 * VETSIZE;
        universal_sorter.shuffleVector(vet, VETSIZE, num_breaks, 1);
    }else if(VETDISORDER !=0){
        std::cerr<<"No valid disorder"<<std::endl;
    }
}

float calculate_cost(OperationsCounter operation_counter, double comparison_coefficient, double movement_coefficient, double call_coefficient){
    return (operation_counter.get_cmp() * comparison_coefficient + operation_counter.get_move() * movement_coefficient + operation_counter.get_calls() * call_coefficient);
}

int main()
{
    int i, j, p;
    item vet[VETSIZE], vet_copy[VETSIZE];
    OperationsCounter operation_counter;
    Sorter sorting_algorithms;
    float costs[4] = {0,0,0,0};
    int mult = (int) pow(10, KEYSIZE - 1);
    
    DataPoint data[4];
    
    srand48(1);
    //creating vector 
    for (i = 0; i < VETSIZE; i++)
    {
        
        for (j = (int)(drand48() * mult), p = KEYSIZE - 2; p >= 0; j /= 10, p--)
        {
            vet[i].key[p] = '0' + j % 10;
        }
        vet[i].key[KEYSIZE - 1] = 0;
        for (j = 0; j < REGISTERSIZE - 1; j++)
        {
            vet[i].payload[j] = '0' + j % 10;
        }
        vet[i].payload[REGISTERSIZE - 1] = 0;
    }

    for(int i =0;i<15;i++){
        std::cout<<vet[i].key<<std::endl;
        std::cout<<strcmp(vet[i].key, vet[i+1].key)<<std::endl;
    }
    
    //calculating comparison, movements and calls cost
    copy_vet(vet, vet_copy);
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    auto start0 = std::chrono::high_resolution_clock::now();
    sorting_algorithms.insertionSort(vet_copy, 0, VETSIZE - 1, &operation_counter);
    auto end0 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration0 = end0 - start0;
    costs[0] = duration0.count() * 1000000.0; 
    data[0] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[0]};
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[0]<<" "<<std::endl;
    operation_counter.resetcounter();

    
    copy_vet(vet, vet_copy);
    auto start1 = std::chrono::high_resolution_clock::now();
   sorting_algorithms.quickSort3Ins(vet_copy, 0, (VETSIZE /2) - 1, 10, &operation_counter);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    costs[1] = duration1.count() * 1000000.0; 
    data[1] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[1]};
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[1]<<" "<<std::endl;
    operation_counter.resetcounter();

    copy_vet(vet, vet_copy);
    auto start2 = std::chrono::high_resolution_clock::now();
    sorting_algorithms.quickSort3Ins(vet_copy, 0, (VETSIZE/3) - 1, 10,&operation_counter);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    costs[2] = duration2.count() * 1000000.0; 
    data[2] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[2]};
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[2]<<" "<<std::endl;
    operation_counter.resetcounter();

    
    copy_vet(vet, vet_copy);
    auto start3 = std::chrono::high_resolution_clock::now();
    sorting_algorithms.quickSort3Ins(vet_copy, 0, (VETSIZE/4) - 1,10, &operation_counter);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - start3;
    costs[3] = duration3.count() * 1000000.0; 
    data[3] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[3]};
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[3]<<" "<<std::endl;
    operation_counter.resetcounter();
    

    //double comparison_coefficient =  0.0250228175, movement_coefficient =-0.0114883741, call_coefficient =  0.0100893780;;
    double comparison_coefficient =  0.0144691489, movement_coefficient =0.0021319414, call_coefficient =  0.0476728123;

    UniversalSorter universal_sorter(comparison_coefficient, movement_coefficient, call_coefficient);
    
    double cost_threshold = 10.000000;
    int partition_threshold = universal_sorter.determine_partition_threshold(vet, VETSIZE, cost_threshold);
    int break_threshold = universal_sorter.determine_break_threshold(partition_threshold, vet, VETSIZE, cost_threshold, 1);
    break_threshold = 1;
    universal_sorter.universal_sorter(vet, VETSIZE, partition_threshold, break_threshold);
    for( int i =0;i<4;i++){
        std::cout<<"["<<data[i].cmp<<", "<<data[i].move<<", "<<data[i].calls<<"],"<<std::endl;
    }
    for( int i =0;i<4;i++){
        std::cout<<data[i].cost<<", "<<std::ends;
    }
    std::cout<<std::endl;
    
    create_disorder(universal_sorter, vet, break_threshold, partition_threshold);
    std::cout<<universal_sorter.count_breaks(vet, VETSIZE)<<std::endl;
    std::cout<<"KEYSIZE: "<<KEYSIZE<<" REGISTERSIZE: "<<REGISTERSIZE<<" VETSIZE: "<<VETSIZE<<" VETDISORDER: "<<VETDISORDER<<std::endl;
    operation_counter.resetcounter();
    
    std::cout<<"partition: "<<partition_threshold<<" break: "<<break_threshold<<std::endl;
    copy_vet(vet, vet_copy);
    universal_sorter.get_operation_counter()->resetcounter();
    universal_sorter.universal_sorter(vet_copy, VETSIZE, partition_threshold, break_threshold);
    float cost_universal_sorter = calculate_cost(*universal_sorter.get_operation_counter(), comparison_coefficient, movement_coefficient, call_coefficient);
    std::cout<<"Universal Sorter: "<<cost_universal_sorter<<" cmp: "<< universal_sorter.get_operation_counter()->get_cmp()<<" move: "<<universal_sorter.get_operation_counter()->get_move()<<" call: "<< universal_sorter.get_operation_counter()->get_calls()<<std::endl;
    
    operation_counter.resetcounter();
    copy_vet(vet, vet_copy);
    sorting_algorithms.quickSort(vet_copy, 0 , VETSIZE-1, &operation_counter);
    float cost_quick_sort = calculate_cost(operation_counter, comparison_coefficient, movement_coefficient, call_coefficient); 
    std::cout<<"Quick Sort: "<<cost_quick_sort<<" cmp: "<< operation_counter.get_cmp()<<" move: "<<operation_counter.get_move()<<" call: "<< operation_counter.get_calls()<<std::endl;
    
    operation_counter.resetcounter();
    copy_vet(vet, vet_copy);
    sorting_algorithms.insertionSort(vet_copy, 0, VETSIZE-1, &operation_counter);
    float cost_insertion_sort = calculate_cost(operation_counter, comparison_coefficient, movement_coefficient, call_coefficient);
    std::cout<<"Insertion Sort: "<<cost_insertion_sort<<" cmp: "<< operation_counter.get_cmp()<<" move: "<<operation_counter.get_move()<<" call: "<< operation_counter.get_calls()<<std::endl; 
    
    std::cout<<"cmp: "<<comparison_coefficient<<" move: "<<movement_coefficient<<" call: "<< call_coefficient<<std::endl;
}
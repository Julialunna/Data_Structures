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


#include <Eigen/Dense>

// Regressão linear via decomposição QR
// Regressão linear via decomposição QR
void fitLinearRegression(const double* X, const double* Y, int n, int p, Eigen::VectorXd& coefficients) {
    Eigen::MatrixXd Xmat(n, p + 1);
    Eigen::VectorXd Yvec(n);

    for (int i = 0; i < n; ++i) {
        Xmat(i, 0) = 1.0;
        for (int j = 0; j < p; ++j) {
            Xmat(i, j + 1) = X[i * p + j];
        }
        Yvec(i) = Y[i];
    }

    // Resolve min ||Xmat * coef - Yvec|| via QR decomposition
    coefficients = Xmat.colPivHouseholderQr().solve(Yvec);
}
struct DataPoint
{
    double cmp;
    double move;
    double calls;
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
    for (int i = 0; i < VETSIZE; i++)
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
        for(int i =0;i<VETSIZE/2;i++){
            item temp = vet[i];
            vet[i] = vet[VETSIZE - 1 - i];
            vet[VETSIZE - 1 - i] = temp;
        }
    }else if(VETDISORDER == 40){
        universal_sorter.shuffleVector(vet, VETSIZE, 0.4 * VETSIZE, 1);
    }else if(VETDISORDER == 60){
        universal_sorter.shuffleVector(vet, VETSIZE, 0.6 * VETSIZE, 1);
    }else if(VETDISORDER !=0){
        std::cerr<<"No valid disorder"<<std::endl;
    }
}

float calculate_cost(OperationsCounter operation_counter, double comparison_coefficient, double movement_coefficient, double call_coefficient){
    return (operation_counter.get_cmp() * comparison_coefficient + operation_counter.get_move() * movement_coefficient + operation_counter.get_calls() * call_coefficient);
}

 main()
{
    int i, j, p;
    long mult = (long) pow(10, KEYSIZE - 1);
    srand48(1);
    item vet[VETSIZE], vet_copy[VETSIZE];
    OperationsCounter operation_counter;
    Sorter sorting_algorithms;
    float costs[7];
    
    DataPoint *data = new DataPoint[7];
    
    srand48(1);
    //creating vector 
    for (i = 0; i < VETSIZE; i++)
    {
        for (int p = 0; p < KEYSIZE - 1; ++p)
            vet[i].key[p] = '0' + (rand() % 10);
        vet[i].key[KEYSIZE - 1] = '\0';
        for (j = 0; j < REGISTERSIZE - 1; j++)
        {
            vet[i].payload[j] = '0' + j % 10;
        }
        vet[i].payload[REGISTERSIZE - 1] = 0;
    }
    
    
    //calculating comparison, movements and calls cost
    copy_vet(vet, vet_copy);
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    costs[0] = medir_tempo_ms([&](){ sorting_algorithms.quickSort(vet_copy, 0, VETSIZE - 1, &operation_counter);});
    data[0] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[0]};
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[0]<<" "<<std::endl;
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    costs[1] = medir_tempo_ms([&](){ sorting_algorithms.quickSort(vet_copy, 0, VETSIZE- 1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[1]<<" "<<std::endl;
    data[1] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[1]};
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    costs[2] = medir_tempo_ms([&](){ sorting_algorithms.insertionSort(vet_copy, 0, VETSIZE - 1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[2]<<" "<<std::endl;
    data[2] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[2]};
    operation_counter.resetcounter();

    
    copy_vet(vet, vet_copy);
    costs[3] = medir_tempo_ms([&](){ sorting_algorithms.insertionSort(vet_copy, 0, VETSIZE-1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[3]<<" "<<std::endl;
    data[3] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[3]};
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    costs[4] = medir_tempo_ms([&](){ sorting_algorithms.quickSort(vet_copy, 0, VETSIZE - 1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[4]<<" "<<std::endl;
    data[4] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[4]};
    operation_counter.resetcounter();
    
    copy_vet(vet, vet_copy);
    costs[5] = medir_tempo_ms([&](){ sorting_algorithms.quickSort(vet_copy, 0, VETSIZE - 1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[5]<<" "<<std::endl;
    data[5] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[5]};
    operation_counter.resetcounter();

    copy_vet(vet, vet_copy);
    costs[6] = medir_tempo_ms([&](){ sorting_algorithms.insertionSort(vet_copy, 0, VETSIZE  - 1, &operation_counter);});
    std::cout<<operation_counter.get_cmp()<<", "<< operation_counter.get_move()<<", "<< operation_counter.get_calls()<<", "<< costs[6]<<" "<<std::endl;
    data[6] = {operation_counter.get_cmp(), operation_counter.get_move(), operation_counter.get_calls(), costs[6]};
    operation_counter.resetcounter();

    for( int i =0;i<7;i++){
        std::cout<<i<<" "<<data[i].cmp<<" "<<data[i].move<<" "<<data[i].calls<<" "<<data[i].cost<<std::endl;
    }

    int amostras = 7;
    double X[amostras * 3] = {
        data[0].cmp,  data[0].move,   data[0].calls,    
        data[1].cmp,  data[1].move,   data[1].calls,    
        data[2].cmp,  data[2].move,   data[2].calls,
        data[3].cmp,  data[3].move,   data[3].calls,
        data[4].cmp,  data[4].move,   data[4].calls,
        data[5].cmp,  data[5].move,   data[5].calls, 
        data[6].cmp,  data[6].move,   data[6].calls
    };

    double Y[amostras] = {data[0].cost, data[1].cost, data[2].cost, data[3].cost, data[4].cost, data[5].cost, data[6].cost};
    
    std::cout << "amostras = " << amostras
    << ", variaveis = " << 3 << std::endl;
    
    Eigen::VectorXd coefs;
    fitLinearRegression(X, Y, amostras, 3, coefs);
    
    std::cout << "Coeficientes calibrados:\n";
    std::cout << "intercepto: " << coefs[0] << std::endl;
    std::cout << "a (comparações): " << coefs[1] << " seg/op\n";
    std::cout << "b (movimentações): " << coefs[2] << " seg/op\n";
    std::cout << "c (chamadas): " << coefs[3]<<" seg/op\n";
    
    double comparison_coefficient =  coefs[1], movement_coefficient = coefs[2], call_coefficient =  coefs[3];
    
    //linear_regression_qr(data, 5, &comparison_coefficient, &movement_coefficient, &call_coefficient);
    
    UniversalSorter universal_sorter(coefs[1], coefs[2], coefs[3]);
    
    double cost_threshold = 10.000000;
    int partition_threshold = universal_sorter.determine_partition_threshold(vet, VETSIZE, cost_threshold);
    int break_threshold = universal_sorter.determine_break_threshold(partition_threshold, vet, VETSIZE, cost_threshold, 1);

    universal_sorter.universal_sorter(vet, VETSIZE, partition_threshold, break_threshold);

    create_disorder(universal_sorter, vet, break_threshold, partition_threshold);
    std::cout<<"cmp: "<<comparison_coefficient<<" move: "<<movement_coefficient<<" call: "<< call_coefficient<<std::endl;
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

}
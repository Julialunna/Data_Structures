#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <chrono>
#include <tuple>
#include <iomanip>
#include "UniversalSorter.hpp"

struct DataPoint
{
    int cmp;
    int move;
    int calls;
    double cost;
};

#define NUM_DATA 3

void linear_regression(DataPoint *data, int n, double *a, double *b, double *c)
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
    func(); // executa a função passada
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main()
{
    int i, j, p;
    long mult = (long)pow(10, KEYSIZE - 1);
    srand48(1);
    item vet[VETSIZE], vet_copy[VETSIZE];
    UniversalSorter universal_sorter(0.0121560, -0.0063780, 0.0172897);

    DataPoint *data = new DataPoint[NUM_DATA];

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

    double a = 0, b = 0, c = 0;
    double cost0 = 0, cost1 = 0, cost2 = 0;

    copy_vet(vet, vet_copy);
    cost0 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, VETSIZE - 1, 5, universal_sorter.get_operation_counter()); });
    data[0] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost0};
    universal_sorter.get_operation_counter()->resetcounter();
    cost1 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, (VETSIZE / 2) - 1, 5, universal_sorter.get_operation_counter()); });
    data[1] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost1};
    universal_sorter.get_operation_counter()->resetcounter();
    cost2 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, (VETSIZE / 3) - 1, 5, universal_sorter.get_operation_counter()); });
    data[2] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost2};
    universal_sorter.get_operation_counter()->resetcounter();

    linear_regression(data, NUM_DATA, &a, &b, &c);
    int partition_threshold = universal_sorter.determine_partition_threshold(vet, VETSIZE, 10.000000);
    universal_sorter.determine_break_threshold(partition_threshold, vet, VETSIZE, 10.000000, 1);
    for(int t=0;t<3;t++){
        std::cout<<data[t].cmp<<" "<<data[t].move<<" "<<data[t].calls<<" "<<data[t].cost<<std::endl;
    }
    std::cout << a << " " << b << " " << c << std::endl;
}
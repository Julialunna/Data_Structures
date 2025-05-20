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

void regressao_linear(DataPoint *data, int n, double *a, double *b, double *c)
{
    double sum_cmp = 0, sum_move = 0, sum_calls = 0, sum_cost = 0;
    double sum_cmp2 = 0, sum_move2 = 0, sum_calls2 = 0;
    double sum_cmp_move = 0, sum_cmp_calls = 0, sum_move_calls = 0;
    double sum_cmp_cost = 0, sum_move_cost = 0, sum_calls_cost = 0;

    for (int i = 0; i < n; ++i)
    {
        sum_cmp += data[i].cmp;
        sum_move += data[i].move;
        sum_calls += data[i].calls;
        sum_cost += data[i].cost;

        sum_cmp2 += data[i].cmp * data[i].cmp;
        sum_move2 += data[i].move * data[i].move;
        sum_calls2 += data[i].calls * data[i].calls;

        sum_cmp_move += data[i].cmp * data[i].move;
        sum_cmp_calls += data[i].cmp * data[i].calls;
        sum_move_calls += data[i].move * data[i].calls;

        sum_cmp_cost += data[i].cmp * data[i].cost;
        sum_move_cost += data[i].move * data[i].cost;
        sum_calls_cost += data[i].calls * data[i].cost;
    }

    // Monta o sistema de equacoes normais: A * X = B
    double A[3][3] = {
        {sum_cmp2, sum_cmp_move, sum_cmp_calls},
        {sum_cmp_move, sum_move2, sum_move_calls},
        {sum_cmp_calls, sum_move_calls, sum_calls2}};

    double B[3] = {sum_cmp_cost, sum_move_cost, sum_calls_cost};

    // Resolve sistema linear com eliminacao de Gauss
    double M[3][4];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            M[i][j] = A[i][j];
        M[i][3] = B[i];
    }

    for (int i = 0; i < 3; ++i)
    {
        double pivot = M[i][i];
        for (int j = 0; j < 4; ++j)
            M[i][j] /= pivot;

        for (int k = 0; k < 3; ++k)
        {
            if (k == i)
                continue;
            double factor = M[k][i];
            for (int j = 0; j < 4; ++j)
                M[k][j] -= factor * M[i][j];
        }
    }

    *a = M[0][3];
    *b = M[1][3];
    *c = M[2][3];
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

    DataPoint *data = new DataPoint[3];

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
    double cost0 = 0, cost2 = 0, cost3 = 0;

    copy_vet(vet, vet_copy);
    cost0 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, VETSIZE - 1, 5, universal_sorter.get_operation_counter()); });
    data[0] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost0};
    universal_sorter.get_operation_counter()->resetcounter();
    cost2 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, (VETSIZE / 2) - 1, 5, universal_sorter.get_operation_counter()); });
    data[1] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost2};
    universal_sorter.get_operation_counter()->resetcounter();
    cost3 = medir_tempo_ms([&]()
                           { universal_sorter.get_sorter().quickSort3Ins(vet_copy, 0, (VETSIZE / 3) - 1, 5, universal_sorter.get_operation_counter()); });
    data[2] = {universal_sorter.get_operation_counter()->get_cmp(), universal_sorter.get_operation_counter()->get_move(), universal_sorter.get_operation_counter()->get_calls(), cost3};
    universal_sorter.get_operation_counter()->resetcounter();

    regressao_linear(data, 3, &a, &b, &c);
    int partition_threshold = universal_sorter.determine_partition_threshold(vet, VETSIZE, 10.000000);
    universal_sorter.determine_break_threshold(partition_threshold, vet, VETSIZE, 10.000000, 1);
    for(int t=0;t<3;t++){
        std::cout<<data[t].cmp<<" "<<data[t].move<<" "<<data[t].calls<<" "<<data[t].cost<<std::endl;
    }
    std::cout << a << " " << b << " " << c << std::endl;
}
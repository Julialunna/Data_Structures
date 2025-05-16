#include "UniversalSorter.hpp"
#include <unistd.h>
#include <cmath>
#include <iomanip>
// #include "OperationsCounter.hpp"

// this function has a cost of O(n)! actually O(n-1) exactly

UniversalSorter::UniversalSorter(double comp_coefficient,
                                 double mov_coefficient, double call_coefficient) : comparison_coefficient(comp_coefficient),
                                                                                  movimentation_coefficient(mov_coefficient), call_coefficient(call_coefficient) {}

// O(n)
int UniversalSorter::count_breaks(int *vet, int size)
{
  int result = 0;
  for (int i = 1; i < size; i++)
  {
    if (vet[i - 1] > vet[i])
    {
      result++;
    }
  }
  return result;
}

// O(1)
void UniversalSorter::universal_sorter(int *v, int v_size, int min_partition_size, int breaks_threshold)
{
  int num_breaks = this->count_breaks(v, v_size);

  if (num_breaks < breaks_threshold)
  {
    this->sorter.insertionSort(v, 0, v_size - 1, &operation_counter);
  }
  else
  {
    if (v_size > min_partition_size)
    {
      this->sorter.quickSort3Ins(v, 0, v_size - 1, min_partition_size,  &operation_counter);
    }
    else
    {
      this->sorter.insertionSort(v, 0, v_size - 1, &operation_counter);
    }
  }
}

// O(1)
double UniversalSorter::calculate_cost()
{
  double cost = this->comparison_coefficient * this->operation_counter.get_cmp() + this->movimentation_coefficient * this->operation_counter.get_move() + this->call_coefficient * this->operation_counter.get_calls();
  return cost;
}

// O(1)
void UniversalSorter::print_partition_statics(PartitionStatistics *partition_statistics)
{
  std::cout << "mps " << partition_statistics->partition_size << " cost " << std::fixed << std::setprecision(9) << partition_statistics->cost << " cmp " << partition_statistics->num_of_comparisons << " move " << partition_statistics->num_of_movements << " calls " << partition_statistics->num_of_calls << std::endl;
}

void UniversalSorter::register_partition_statistics(PartitionStatistics statistics[max_quantity_of_partitions], int num_partitions, int partition_size)
{
  statistics[num_partitions].cost = this->calculate_cost();
  statistics[num_partitions].num_of_calls = this->operation_counter.get_calls();
  statistics[num_partitions].num_of_comparisons = this->operation_counter.get_cmp();
  statistics[num_partitions].num_of_movements = this->operation_counter.get_move();
  statistics[num_partitions].partition_size = partition_size;
}

// O(1)
void UniversalSorter::print_final_results(int num_partitions, int best_partition, double difference_max_min_cost)
{

  std::cout << "nummps " << num_partitions << " limParticao " << best_partition << " mpsdiff " << std::fixed << std::setprecision(6) << difference_max_min_cost << std::endl;
}

// O(n)
int UniversalSorter::find_min_cost(PartitionStatistics *statistics, int num_partitions)
{
  int min_cost_index = 0;
  for (int i = 1; i < num_partitions; i++)
  {
    if (statistics[min_cost_index].cost > statistics[i].cost)
    {
      min_cost_index = i;
    }
  }
  return min_cost_index;
}

int UniversalSorter::find_partition_size(int index, int min_partition_size, int step)
{
  return min_partition_size + index * step;
}

int UniversalSorter::find_index_by_partition(int partition_size, int min_partition_size, int step)
{
  return (partition_size - min_partition_size) / step;
}

void UniversalSorter::find_new_range(int min_cost_index, int *min_size_range, int *max_size_range, int num_sizes, int *step)
{
  int new_min_index = 0, new_max_index = 0;
  if (min_cost_index == 0)
  {
    new_min_index = 0;
    new_max_index = 2;
  }
  else if (min_cost_index == num_sizes - 1)
  {
    new_min_index = num_sizes - 3;
    new_max_index = num_sizes - 1;
  }
  else
  {
    new_min_index = min_cost_index - 1;
    new_max_index = min_cost_index + 1;
  }

  *max_size_range = this->find_partition_size(new_max_index, *min_size_range, *step);
  *min_size_range = this->find_partition_size(new_min_index, *min_size_range, *step);

  *step = (int)((*max_size_range - *min_size_range) / 5);

  if (*step == 0)
  {
    *step = *step + 1;
  }
}

// min partition size
int UniversalSorter::determine_partition_threshold(int *v, int v_size, double cost_threshold)
{
  int min_partition_size_range = 2, max_partition_size_range = v_size,
  step = (int)((max_partition_size_range - min_partition_size_range) / 5), best_partition = 0, *v_copy = new int[v_size], min_cost_index = 0, current_index = 0;
  int num_partitions = this->find_index_by_partition(max_partition_size_range, min_partition_size_range, step) + 1;

  float difference_max_min_cost = cost_threshold + 1;
  PartitionStatistics *statistics;

  int iter = 0, i = 0;

  while (difference_max_min_cost > cost_threshold && num_partitions >= 5)
  {

    num_partitions = this->find_index_by_partition(max_partition_size_range, min_partition_size_range, step) + 1;
    current_index = 0;
    statistics = new PartitionStatistics[num_partitions];
    std::cout<<std::endl;
    std::cout << "iter " << iter << std::endl;
    
    for (i = min_partition_size_range; i <= max_partition_size_range; i += step)
    {
      for (int j = 0; j < v_size; j++)
      {
        v_copy[j] = v[j];
      }

      this->universal_sorter(v_copy, v_size, i, 0);

      this->register_partition_statistics(statistics, current_index, i);
      this->print_partition_statics(&statistics[current_index]);

      current_index++;
      this->operation_counter.resetcounter();
    }

    min_cost_index = this->find_min_cost(statistics, num_partitions);
    best_partition = this->find_partition_size(min_cost_index, min_partition_size_range, step);

    int last_min_partition_size_range = min_partition_size_range;
    int last_step = step;
    this->find_new_range(min_cost_index, &min_partition_size_range, &max_partition_size_range, num_partitions, &step);

    difference_max_min_cost = fabs(statistics[this->find_index_by_partition(max_partition_size_range, last_min_partition_size_range,
                                                                            last_step)]
                                       .cost -
                                   statistics[this->find_index_by_partition(min_partition_size_range, last_min_partition_size_range,
                                                                            last_step)]
                                       .cost);

    this->print_final_results(num_partitions, best_partition, difference_max_min_cost);
    iter++;
    delete[] statistics;
  }
  delete[] v_copy;
  return best_partition;
}

void UniversalSorter::shuffleVector(int *vet, int vet_size, int num_breaks, int seed)
{
  srand48(seed);
  int index1 = 0, index2 = 0, temp;

  for (int i = 0; i < num_breaks; i++)
  {
    while (index1 == index2)
    {
      index1 = (int)(drand48() * vet_size);
      index2 = (int)(drand48() * vet_size);
    }
    if (index1 < vet_size && index2 < vet_size)
    {
      temp = vet[index1];
      vet[index1] = vet[index2];
      vet[index2] = temp;
      index1 = index2 = 0;
    }
  }
}
void UniversalSorter::print_statics_quick(BreaksStatistics breaks_statistics)
{
  std::cout << "qs lq " << breaks_statistics.num_breaks << " cost " << std::fixed << std::setprecision(9) << breaks_statistics.cost << " cmp " << breaks_statistics.num_of_comparisons << " move " << breaks_statistics.num_of_movements << " calls " << breaks_statistics.num_of_calls << std::endl;
}
void UniversalSorter::print_statics_insertion(BreaksStatistics breaks_statistics)
{
  std::cout << "in lq " << breaks_statistics.num_breaks << " cost " << std::fixed << std::setprecision(9) << breaks_statistics.cost << " cmp " << breaks_statistics.num_of_comparisons << " move " << breaks_statistics.num_of_movements << " calls " << breaks_statistics.num_of_calls << std::endl;
}

void UniversalSorter::register_break_statistics(BreaksStatistics *statistics_quick_sort, int num_breaks)
{
  statistics_quick_sort->cost = this->calculate_cost();
  statistics_quick_sort->num_of_calls = this->operation_counter.get_calls();
  statistics_quick_sort->num_of_comparisons = this->operation_counter.get_cmp();
  statistics_quick_sort->num_of_movements = this->operation_counter.get_move();
  statistics_quick_sort->num_breaks = num_breaks;
}

int UniversalSorter::find_min_cost_breaks(BreaksStatistics *statistics_quick_sort, BreaksStatistics *statistics_insertion_sort, int num_breaks)
{
  int min_cost_index = 0;
  double difference = 0;
  double best_difference = fabs(statistics_quick_sort[0].cost - statistics_insertion_sort[0].cost);

  for (int i = 1; i < num_breaks; i++)
  {
    difference = fabs(statistics_quick_sort[i].cost - statistics_insertion_sort[i].cost);
    if (best_difference > difference)
    {
      min_cost_index = i;
      best_difference = difference;
    }
    
  }
  return min_cost_index;
}

void UniversalSorter::print_break_thershold_result(int partition_size, double difference_max_min_size, int num_size_breaks)
{
  std::cout << "numlq " << num_size_breaks << " limQuebras " << partition_size << " lqdiff " << std::fixed << std::setprecision(6) << difference_max_min_size << std::endl;
  
}

void UniversalSorter::determine_break_threshold(int partition_thershold, int *vet, int vet_size, double cost_threshold, int seed)
{
  int min_num_breaks_range = 1, max_num_breaks_range = vet_size / 2,
  step = (max_num_breaks_range - min_num_breaks_range) / 5, num_breaks = 5, iter = 0, i = 0, min_cost_index = 0, current_index = 0;

  float difference_max_min_cost = cost_threshold + 1;

  BreaksStatistics *statistics_quick_sort, *statistics_insertion_sort;

  this->universal_sorter(vet, vet_size, partition_thershold, 0);
  this->operation_counter.resetcounter();


  while (difference_max_min_cost > cost_threshold && num_breaks >= 5)
  {
    num_breaks = this->find_index_by_partition(max_num_breaks_range, min_num_breaks_range, step) + 1;

    std::cout<<std::endl;
    current_index = 0;
    std::cout << "iter "<<iter << std::endl;

    statistics_insertion_sort = new BreaksStatistics[num_breaks];
    statistics_quick_sort = new BreaksStatistics[num_breaks];

    for (i = min_num_breaks_range; i <= max_num_breaks_range; i += step)
    {
      this->shuffleVector(vet, vet_size, i, seed);
      this->sorter.quickSort3Ins(vet, 0, vet_size - 1, partition_thershold, &this->operation_counter);
      this->register_break_statistics(&statistics_quick_sort[current_index], i);
      this->print_statics_quick(statistics_quick_sort[current_index]);
      this->operation_counter.resetcounter();
      
      this->shuffleVector(vet, vet_size, i, seed);
      this->sorter.insertionSort(vet, 0, vet_size - 1, &this->operation_counter);
      this->register_break_statistics(&statistics_insertion_sort[current_index], i);
      this->print_statics_insertion(statistics_insertion_sort[current_index]);
      this->operation_counter.resetcounter();
      current_index++;
    }
    
    min_cost_index = this->find_min_cost_breaks(statistics_quick_sort, statistics_insertion_sort, num_breaks);
    int last_min_num_breaks_range = min_num_breaks_range;
    int last_step = step;
    this->find_new_range(min_cost_index, &min_num_breaks_range, &max_num_breaks_range, num_breaks, &step);
    
    difference_max_min_cost = fabs(statistics_insertion_sort[this->find_index_by_partition(max_num_breaks_range, last_min_num_breaks_range,
    last_step)].cost -statistics_insertion_sort[this->find_index_by_partition(min_num_breaks_range, last_min_num_breaks_range,
    last_step)].cost);

    this->print_break_thershold_result(this->find_partition_size(min_cost_index, last_min_num_breaks_range, last_step), difference_max_min_cost, num_breaks);
    delete[] statistics_insertion_sort;
    delete[] statistics_quick_sort;
    iter++;
  }
}

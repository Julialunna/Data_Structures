#include "UniversalSorter.hpp"
#include <cmath>
// #include "OperationsCounter.hpp"

// this function has a cost of O(n)! actually O(n-1) exactly
int const max_quantity_of_partitions = 6;
struct Statistics{
    float cost;
    int num_of_comparisons;
    int num_of_calls;
    int num_of_movements;
    int partition_size;
};

UniversalSorter::UniversalSorter(float comp_coefficient,
  float mov_coefficient, float call_coefficient) : comparison_coefficient(comp_coefficient), 
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
float UniversalSorter::calculate_cost()
{
  float cost = this->comparison_coefficient * this->operation_counter.get_cmp() + this->movimentation_coefficient * this->operation_counter.get_move() + this->call_coefficient * this->operation_counter.get_calls();
  return cost;
}

// O(1)
void UniversalSorter::print_statics(float cost, int partition_size)
{
  std::cout << "mps " << partition_size << " cost " << cost << " cmp " << this->operation_counter.get_cmp() << " move " << this->operation_counter.get_move() << " calls " << this->operation_counter.get_calls() << std::endl;
}

void UniversalSorter::register_statistics(Statistics statistics [max_quantity_of_partitions], int num_partitions, int partition_size){
  statistics[num_partitions].cost = this->calculate_cost();
  statistics[num_partitions].num_of_calls = this->operation_counter.get_calls();
  statistics[num_partitions].num_of_comparisons = this->operation_counter.get_cmp();
  statistics[num_partitions].num_of_movements = this->operation_counter.get_move();
  statistics[num_partitions].partition_size = partition_size;
}

// O(1)
void UniversalSorter::print_final_results(int num_partitions, int best_partition, float difference_max_min_cost)
{

  std::cout << "nummps " << num_partitions << " lim particao " << best_partition << " mps diff " << difference_max_min_cost << std::endl;
}

// O(n)
int UniversalSorter::find_min_cost(float *costs, int num_partitions)
{
  int min_cost_index = 0;
  for (int i = 1; i < num_partitions; i++)
  {
    if (costs[min_cost_index] > costs[i])
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
int UniversalSorter::determine_partition_threshold(int *v, int v_size, int cost_threshold)
{
  int min_partition_size_range = 2, max_partition_size_range = v_size,
  step = (max_partition_size_range - min_partition_size_range) / 5, num_partitions = 5, best_partition = 0, *v_copy = new int[v_size], min_cost_index = cost_threshold +1;

  float difference_max_min_cost = cost_threshold + 1;
  Statistics statistics [max_quantity_of_partitions];

  int iter = 0, i = 0;

  while (difference_max_min_cost > cost_threshold && num_partitions >= 5)
  {

    num_partitions = 0;
    std::cout << "iter " << iter << std::endl;

    for (i = min_partition_size_range; i <= max_partition_size_range; i += step)
    {
      for (int j = 0; j < v_size; j++)
      {
        v_copy[j] = v[j];
      }
      this->universal_sorter(v_copy, v_size, i, 0);

      
      this->register_statistics(statistics, num_partitions, i);
      this->print_statics(costs[num_partitions], i);

      num_partitions++;
      this->operation_counter.resetcounter();
    }

    min_cost_index = this->find_min_cost(costs, num_partitions);
    best_partition = this->find_partition_size(min_cost_index, min_partition_size_range, step);

    int last_min_partition_size_range = min_partition_size_range;
    int last_step = step;
    this->find_new_range(min_cost_index, &min_partition_size_range, &max_partition_size_range, num_partitions, &step);

    difference_max_min_cost = fabs(costs[this->find_index_by_partition(max_partition_size_range, last_min_partition_size_range,
    last_step)] -
    costs[this->find_index_by_partition(min_partition_size_range, last_min_partition_size_range,
    last_step)]);

    this->print_final_results(num_partitions, best_partition, difference_max_min_cost);
    iter++;
  }
  return best_partition;
}

void UniversalSorter::create_breaks(int *vet, int num_of_breaks, int vet_size)
{
  int breaks = 0, i = 0;
  int new_index = vet_size - i - 1;

  while (breaks < num_of_breaks && i + 2 < vet_size)
  {
    if (vet[i] != vet[i + 1])
    {
      int temp = vet[i];
      vet[i] = vet[i + 1];
      vet[i + 1] = temp;
      breaks++;
    }
    i = i + 2;
  }
}

void print_statics_quick(int num_breaks, float cost){
  
}

int UniversalSorter::determine_break_threshold(int partition_thershold, int *vet, int vet_size, int cost_threshold)
{
  int min_num_breaks_range = 2, max_num_breaks_range = vet_size,
  step = (max_num_breaks_range - min_num_breaks_range) / 5, num_breaks = 5, best_num_of_breaks = 0,
  *vet_copy = new int[vet_size], iter = 0, i = 0;

  float costs_quicksort[max_quantity_of_partitions], costs_insertionsort[max_quantity_of_partitions], min_cost_index = 0,
  difference_max_min_cost = cost_threshold + 1;

  for (int j = 0; j < vet_size; j++){
    vet_copy[j] = vet[j];
  }

  this->universal_sorter(vet_copy, vet_size, partition_thershold, 0);

  this->create_breaks(vet_copy, 20, vet_size);

  while (difference_max_min_cost > cost_threshold && num_breaks >= 5)
  {
    num_breaks = 0;
    std::cout << iter << std::endl;
    break;
    for (i = min_num_breaks_range; i <= max_num_breaks_range; i += step)
    {

      num_breaks++;
    }

    int last_min_num_breaks_range = min_num_breaks_range;
    int last_step = step;
    this->find_new_range(min_cost_index, &min_num_breaks_range, &max_num_breaks_range, num_breaks, &step);

    difference_max_min_cost = fabs(costs_insertionsort[this->find_index_by_partition(max_num_breaks_range, last_min_num_breaks_range,
    last_step)] -
    costs_insertionsort[this->find_index_by_partition(min_num_breaks_range, last_min_num_breaks_range,
    last_step)]);

    iter++;
  }
}

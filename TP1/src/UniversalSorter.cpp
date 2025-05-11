#include "UniversalSorter.hpp"
#include <cmath>
// #include "OperationsCounter.hpp"

// this function has a cost of O(n)! actually O(n-1) exactly
int const max_quantity_of_partitions = 6;

UniversalSorter::UniversalSorter(float comp_coefficient,
  float mov_coefficient, float call_coefficient):comparison_coefficient(comp_coefficient), movimentation_coefficient(mov_coefficient), call_coefficient(call_coefficient){}
 
//O(n)  
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

void UniversalSorter::insertionSort(int v[], int l, int r)
{
  int j;
  this->operation_counter.inccalls(1);

  for (int i = l + 1; i < r + 1; i++)
  {
    this->operation_counter.incmove(1);
    int round_item = v[i];
    j = i - 1;

    this->operation_counter.inccmp(1);
    while (j >= 0 && round_item < v[j])
    {
      this->operation_counter.inccmp(1);

      v[j + 1] = v[j];
      this->operation_counter.incmove(1);

      j--;
    }
    this->operation_counter.incmove(1);
    v[j + 1] = round_item;
  }
  return;
}

int UniversalSorter::median(int a, int b, int c)
{
  if ((a <= b) && (b <= c))
    return b; // a b c
  if ((a <= c) && (c <= b))
    return c; // a c b
  if ((b <= a) && (a <= c))
    return a; // b a c
  if ((b <= c) && (c <= a))
    return c; // b c a
  if ((c <= a) && (a <= b))
    return a; // c a b
  return b;   // c b a
}

void UniversalSorter::swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  this->operation_counter.incmove(3);
}

void UniversalSorter::partition3(int *A, int l, int r, int *i, int *j)
{
  this->operation_counter.inccalls(1);
  int medium;
  *i = l;
  *j = r;
  medium = A[(*i + *j) / 2];
  int pivot = median(A[l], medium, A[r]);
  do
  {
    while (pivot > A[*i])
    {
      this->operation_counter.inccmp(1);
      (*i)++;
    }
    while (pivot < A[*j])
    {
      this->operation_counter.inccmp(1);
      (*j)--;
    }
    this->operation_counter.inccmp(1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j]);
      (*i)++;
      (*j)--;
    }
    this->operation_counter.inccmp(1);
  } while (*i <= *j);
}

// e se eu só usar asssim e deixar a decisão para o uso de insertion em quickSort3Ins em vez de no Ordenador universal? posso passar o limiar como parâmetro
void UniversalSorter::quickSort3Ins(int *A, int l, int r, int partition_threshold)
{

  int i, j;

  this->operation_counter.inccalls(1);

  partition3(A, l, r, &i, &j);

  if (l < j)
  {
    if (j - l <= partition_threshold)
    {
      insertionSort(A, l, j);
    }
    else
    {
      quickSort3Ins(A, l, j, partition_threshold);
    }
  }

  if (i < r)
  {
    if (r - i <= partition_threshold)
    {
      insertionSort(A, i, r);
    }
    else
    {
      quickSort3Ins(A, i, r, partition_threshold);
    }
  }
}

//O(1)
void UniversalSorter::universal_sorter(int *v, int v_size, int min_partition_size, int breaks_threshold)
{
  int num_breaks = this->count_breaks(v, v_size);
  breaks_threshold = 2;
  if (num_breaks < breaks_threshold)
  {
    this->insertionSort(v, 0, v_size - 1);
  }
  else
  {
    if (v_size > min_partition_size)
    {
      this->quickSort3Ins(v, 0, v_size - 1, min_partition_size);
    }
    else
    {
      this->insertionSort(v, 0, v_size - 1);
    }
  }
}

//O(1)
float UniversalSorter::calculate_cost (){
  float cost = this->comparison_coefficient * this->operation_counter.get_cmp() + this->movimentation_coefficient * this->operation_counter.get_move() + this->call_coefficient * this->operation_counter.get_calls();
  return cost;
}

//O(1)
void UniversalSorter::print_statics(float cost, int partition_size){
  std::cout<<"mps "<<partition_size<<" cost "<<cost<<" cmp "<<this->operation_counter.get_cmp()<< " move "<<this->operation_counter.get_move()<< " calls "<< this->operation_counter.get_calls()<<std::endl;
}

//O(1)
void UniversalSorter::print_results(int num_partitions, int best_partition, float difference_max_min_cost){

  std::cout <<"nummps "<<num_partitions<< " lim particao "<< best_partition << " mps diff "<< difference_max_min_cost<< std::endl;
}

//O(n)
int UniversalSorter::find_min_cost(float *costs, int num_partitions){
  int min_cost_index = 0;
  for(int i=1;i<num_partitions;i++){
    if(costs[min_cost_index] > costs[i]){
      min_cost_index = i;
    }
  }
  return min_cost_index;
}

int UniversalSorter::find_partition_size(int index, int min_partition_size, int step){
  return min_partition_size + index * step;
}

int UniversalSorter::find_index_by_partition(int partition_size, int min_partition_size, int step){
  return (partition_size - min_partition_size) / step;
}
void UniversalSorter::find_new_partition_range(int min_cost_index,  int *min_partition_size_range , int *max_partition_size_range, int num_partitions, int* step){
  int new_min_index =0, new_max_index=0;
  if(min_cost_index == 0){
    new_min_index = 0;
    new_max_index = 2;
  }else if(min_cost_index == num_partitions -1){
    new_min_index = num_partitions-3;
    new_max_index= num_partitions -1; 
  }else{
    new_min_index = min_cost_index-1;
    new_max_index = min_cost_index+1;
  }

  *max_partition_size_range = this->find_partition_size(new_max_index, *min_partition_size_range, *step);
  *min_partition_size_range = this->find_partition_size(new_min_index, *min_partition_size_range, *step);


  *step = (int)((*max_partition_size_range - *min_partition_size_range) / 5);

  if( *step == 0){
    *step = *step+1;
  }
}


//min partition size
int UniversalSorter::determine_partition_threshold (int *v, int v_size, int cost_threshold){
  int min_partition_size_range = 2, max_partition_size_range = v_size, 
  step = (max_partition_size_range - min_partition_size_range) / 5, num_partitions = 5, best_partition =0,  *v_copy = new int[v_size];
  
  float costs[max_quantity_of_partitions], min_cost_index = 0,
  difference_max_min_cost = cost_threshold+1;

  int iter = 0, i=0;

  while(difference_max_min_cost > cost_threshold && num_partitions >= 5){

    num_partitions = 0;
    std::cout<<"iter "<<iter<<std::endl;
    
    for(i = min_partition_size_range; i<=max_partition_size_range; i+= step){
      for(int j=0;j<v_size;j++){
        v_copy[j] = v[j];
      }  
      this->universal_sorter(v_copy, v_size, i, v_size); 
      

      costs[num_partitions] = this->calculate_cost();
      this->print_statics(costs[num_partitions], i);

      num_partitions++;
      this->operation_counter.resetcounter();

    }  

    min_cost_index = this->find_min_cost(costs, num_partitions);
    best_partition = this->find_partition_size(min_cost_index, min_partition_size_range, step);

    int last_min_partition_size_range = min_partition_size_range;
    int last_step = step;
    this->find_new_partition_range(min_cost_index, &min_partition_size_range, &max_partition_size_range, num_partitions, &step);


    difference_max_min_cost = fabs(costs[this->find_index_by_partition(max_partition_size_range, last_min_partition_size_range,
    last_step)] - costs[this->find_index_by_partition(min_partition_size_range, last_min_partition_size_range,
    last_step)]) ;

    this->print_results(num_partitions, best_partition, difference_max_min_cost);
    iter++;
  }  
  return best_partition;
}  








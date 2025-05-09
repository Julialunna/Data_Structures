#include "UniversalSorter.hpp"
// #include "OperationsCounter.hpp"

// this function has a cost of O(n)! actually O(n-1) exactly
int const max_quantity_of_partitions = 6;

UniversalSorter::UniversalSorter(float comp_coefficient,
  float mov_coefficient, float call_coefficient):comparison_coefficient(comp_coefficient), movimentation_coefficient(mov_coefficient), call_coefficient(call_coefficient){} 
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
    if (r - i <= 50)
    {
      insertionSort(A, i, r);
    }
    else
    {
      quickSort3Ins(A, i, r, partition_threshold);
    }
  }
}

void UniversalSorter::universal_sorter(int *v, int v_size, int min_partition_size, int breaks_threshold)
{
  int num_breaks = this->count_breaks(v, v_size);
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

float UniversalSorter::calculate_cost (){
  int cost = this->comparison_coefficient * this->operation_counter.get_cmp() + this->movimentation_coefficient * this->operation_counter.get_move() + this->call_coefficient * this->operation_counter.get_calls();
  return cost;
}


void UniversalSorter::print_statics(int cost, int partition_size){
  std::cout<<"mps "<<partition_size<<" cost "<<cost<<" cmp "<<this->operation_counter.get_cmp()<< " move "<<this->operation_counter.get_move()<< " calls "<< this->operation_counter.get_calls()<<std::endl;
}


//min partition size
int UniversalSorter::determine_partition_threshold (int *v, int v_size, int cost_threshold){
  int min_partition_size_range = 2, max_partition_size_range = v_size, 
  step = (max_partition_size_range - min_partition_size_range) / 5, 
  difference_max_min_cost = cost_threshold+1, num_partitions = 5;
  
  float costs[max_quantity_of_partitions];

  int iter = 0;

  while(difference_max_min_cost > cost_threshold && num_partitions >= 5){
    num_partitions = 0;
    std::cout<<iter<<std::endl;
    for(int i = min_partition_size_range; i<=max_partition_size_range; i+= step){
      this->universal_sorter(v, v_size, i, v_size); 

      costs[num_partitions] = this->calculate_cost();
      this->print_statics(costs[num_partitions], i);

      num_partitions++;
      this->operation_counter.resetcounter();
    }
    this->find_min_cost(costs);
    iter++;
  }
}

int UniversalSorter::find_min_cost(float *costs){
  
}








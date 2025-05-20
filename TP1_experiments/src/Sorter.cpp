#include "Sorter.hpp"
#include "OperationsCounter.hpp"

//sort vector using insertionsort algorithm
void Sorter::insertionSort(item *v, int l, int r, OperationsCounter *operation_counter)
{
  int j;
  operation_counter->inccalls(1);
  for (int i = l + 1; i < r + 1; i++)
  {
    operation_counter->incmove(1);
    item round_item = v[i];
    j = i - 1;

    operation_counter->inccmp(1);
    while (j >= 0 && round_item < v[j])
    {
      operation_counter->inccmp( 1);
      v[j + 1] = v[j];
      operation_counter->incmove( 1);
      j--;
    }
    operation_counter->incmove(1);
    v[j + 1] = round_item;
  }
  return;
}

item Sorter::median(item a, item b, item c){


  if ((a <= b) && (b <= c))
    return b; // a b c
  
  if ((a <= c) && (c <= b))
    return c; // a c b

  if ((b <= a) && (a <= c))
    return a; // b a c
 
  if ((b <= c) && (c <= a))
    return c; // b c 
  
  if ((c <= a) && (a <= b))
    return a; // c a b
  return b;   // c b a
}

void Sorter::swap(item *xp, item *yp, OperationsCounter *operation_counter){
    item temp = *xp;
    *xp = *yp;
    *yp = temp;
    operation_counter->incmove(3);
}


void Sorter::partition3(item *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter){
 operation_counter->inccalls(1);
  item medium;
  *i = l;
  *j = r;
  medium = A[(*i + *j) / 2];
  item pivot = median(A[l], medium, A[r]);
  do
  {
    while (pivot > A[*i])
    {
      operation_counter->inccmp(1);
      (*i)++;
    }
    while (pivot < A[*j])
    {
      operation_counter->inccmp(1);
      (*j)--;
    }
    operation_counter->inccmp(1);
    if (*i<= *j)
    {
      swap(&A[*i], &A[*j], operation_counter);
      (*i)++;
      (*j)--;
    }
    operation_counter->inccmp(1);
  } while (*i <= *j);
}

//sort vector using quick sort algorith with median of 3 and using insertion sort to partitions whose size is lower than partition threshold
void Sorter::quickSort3Ins(item *A, int l, int r, int partition_threshold, OperationsCounter *operation_counter){
  int i, j;

  operation_counter->inccalls(1);

  this->partition3(A, l, r, &i, &j, operation_counter);


  if (l < j)
  {
    if (j - l < partition_threshold)
    {
      this->insertionSort(A, l, j, operation_counter);
    }
    else
    {
      this->quickSort3Ins(A, l, j, partition_threshold, operation_counter);
    }
  }

  if (i < r)
  {
    if (r - i < partition_threshold)
    {
      this->insertionSort(A, i, r, operation_counter);
    }
    else
    {
      this->quickSort3Ins(A, i, r, partition_threshold, operation_counter);
    }
  }

}

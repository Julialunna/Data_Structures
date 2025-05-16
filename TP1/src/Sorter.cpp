#include "Sorter.hpp"
#include "OperationsCounter.hpp"
void Sorter::insertionSort(int v[], int l, int r, OperationsCounter *operation_counter)
{
  int j;
  operation_counter->inccalls(1);
  for (int i = l + 1; i < r + 1; i++)
  {
    operation_counter->incmove(1);
    int round_item = v[i];
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

int Sorter::median(int a, int b, int c){


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

void Sorter::swap(int *xp, int *yp, OperationsCounter *operation_counter){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    operation_counter->incmove(3);
}


void Sorter::partition3(int *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter){
 operation_counter->inccalls(1);

  int medium;
  *i = l;
  *j = r;
  medium = A[(*i + *j) / 2];
  int pivot = median(A[l], medium, A[r]);
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
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], operation_counter);
      (*i)++;
      (*j)--;
    }
    operation_counter->inccmp(1);
  } while (*i <= *j);
}

void Sorter::quickSort3Ins(int *A, int l, int r, int partition_threshold, OperationsCounter *operation_counter){
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

void Sorter::partition(int *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter)
{
  operation_counter->inccalls(1);
  int pivot;
  *i = l;
  *j = r;
  pivot = A[(*i + *j) / 2];
  do
  {
    while (pivot > A[*i])
    {
      operation_counter->inccmp(1);
      (*i)++;
    }
    operation_counter->inccmp(1);
    while (pivot < A[*j])
    {
      operation_counter->inccmp(1);
      (*j)--;
    }
    operation_counter->inccmp(1);
    
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], operation_counter);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

void Sorter::quickSort(int *A, int l, int r, OperationsCounter  *operation_counter)
{
  int i, j;

  operation_counter->inccalls( 1);

  partition(A, l, r, &i, &j, operation_counter);
  if (l < j)
  {
    quickSort(A, l, j, operation_counter);
  }
  if (i < r)
  {
    quickSort(A, i, r, operation_counter);
  }
}
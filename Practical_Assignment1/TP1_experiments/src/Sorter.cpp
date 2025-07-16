#include "Sorter.hpp"
#include "OperationsCounter.hpp"
#include <cstring>
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
    while (j >= 0 && strcmp(round_item.key, v[j].key) < 0 )
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


  if (strcmp(a.key,b.key) <= 0 && strcmp(b.key,c.key) <= 0)
    return b; // a b c
  
  if (strcmp(a.key,c.key) <= 0 && strcmp(c.key,b.key) <= 0)
    return c; // a c b

  if (strcmp(b.key,a.key) <= 0 && strcmp(a.key,c.key) <= 0)
    return a; // b a c
 
  if (strcmp(b.key,c.key) <= 0 && strcmp(c.key,a.key) <= 0)
    return c; // b c 
  
  if (strcmp(c.key,a.key) <= 0 && strcmp(a.key,b.key) <= 0)
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
    while (strcmp(pivot.key, A[*i].key) > 0)
    {
      operation_counter->inccmp(1);
      (*i)++;
    }
    while (strcmp(pivot.key, A[*j].key) < 0)
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

void Sorter::partition(item *A, int l, int r, int *i, int *j, OperationsCounter *operation_counter)
{
  operation_counter->inccalls(1);

  item pivot;
  *i = l;
  *j = r;
  pivot = A[(*i + *j) / 2];
  do
  {
    while (strcmp(pivot.key, A[*i].key) > 0)
    {
      operation_counter->inccmp(1);
      (*i)++;
    }
    operation_counter->inccmp(1);
    while (strcmp(pivot.key, A[*j].key) < 0)
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


// quicksort with median of 3
void Sorter::quickSort3(item *A, int l, int r, OperationsCounter *operation_counter)
{
  int i, j;
  operation_counter->inccalls(1);

  this->partition3(A, l, r, &i, &j, operation_counter);
 
  if (l < j)
  {
    quickSort3(A, l, j,operation_counter);
  }
  if (i < r)
  {
    quickSort3(A, i, r, operation_counter);
  }
}


void Sorter::quickSort(item *A, int l, int r, OperationsCounter *operation_counter)
{
  int i, j;

  operation_counter->inccalls(1);

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
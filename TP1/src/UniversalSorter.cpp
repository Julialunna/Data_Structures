#include "UniversalSorter.hpp"
//#include "OperationsCounter.hpp"

// this function has a cost of O(n)! actually O(n-1) exactly
int UniversalSorter::count_breaks(int *vet, int size){
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

void insertionSort(int v[], int l, int r, OperationsCounter *s)
{
  int j;
  s->inccalls(1);

  for (int i = l + 1; i < r + 1; i++)
  {
    s->incmove(1);
    int round_item = v[i];
    j = i - 1;

    s->inccmp(1);
    while (j >= 0 && round_item < v[j])
    {
        s->inccmp(1);

      v[j + 1] = v[j];
      s->incmove(1);
      
      j--;
    }
    s->incmove(1);
    v[j + 1] = round_item;
  }
  return;
}

int median(int a, int b, int c)
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

void swap(int *xp, int *yp, OperationsCounter *s)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  s->incmove(3);
}

void partition3(int *A, int l, int r, int *i, int *j, OperationsCounter *s)
{
  s->inccalls(1);
  int medium;
  *i = l;
  *j = r;
  medium = A[(*i + *j) / 2];
  int pivot = median(A[l], medium, A[r]);
  do
  {
    while (pivot > A[*i])
    {
      s->inccmp(1);
      (*i)++;
    }
    while (pivot < A[*j])
    {
        s->inccmp(1);
      (*j)--;
    }
    s->inccmp(1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }
    s->inccmp(1);
  } while (*i <= *j);
}


//e se eu só usar asssim e deixar a decisão para o uso de insertion em quickSort3Ins em vez de no Ordenador universal? posso passar o limiar como parâmetro 
void quickSort3Ins(int *A, int l, int r, OperationsCounter *s)
{
  
  int i, j;
  s->inccalls(1);

  partition3(A, l, r, &i, &j, s);

  if(l<j){
    if (j - l <= 50)
  {
    insertionSort(A, l, j, s);
  }else
  {
    quickSort3Ins(A, l, j, s);
  }
  }
  

  if(i < r){
    if (r - i  <= 50)
    {
      insertionSort(A, i, r, s);
    }else
    {
      quickSort3Ins(A, i, r, s);
    }

  }
}




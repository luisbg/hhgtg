#include <stdlib.h>
#include <stdio.h>

static void swap (int *a, int *b);
static int get_pivot (int low, int high);
static int partition (int *l, int low, int high);
void quicksort (int *l, int low, int high);


void
print_list (int *l, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}

static void
swap (int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static int
get_pivot (int low, int high)
{
  return (low + high) / 2;
}

static int
partition (int *l, int low, int high)
{
  int c;
  int middle;

  int k = get_pivot (low, high);
  int pivot = l[k];
  swap (&l[low], &l[k]);        // move pivot out of array to order

  c = low + 1;
  middle = high;
  while (c <= middle)           // run the array
  {
    while ((c <= high) && (l[c] <= pivot))      // before pivot
      c++;
    while ((middle >= low) && (l[middle] > pivot))      // after pivot
      middle--;
    if (c < middle)
      swap (&l[c], &l[middle]);
  }

  swap (&l[low], &l[middle]);   // bring the pivot to its place

  return middle;
}

void
quicksort (int *l, int low, int high)
{
  if (low >= high)
    return;

  int middle;

  middle = partition (l, low, high);
  quicksort (l, low, middle - 1);
  quicksort (l, middle + 1, high);
}

int
main ()
{
  int l[50];
  int size = 50;
  int c;
  for (c = 0; c < size; c++)
    l[c] = rand () % 100;

  printf ("out of order:\n");
  print_list (l, size - 1);

  printf ("in order:\n");
  quicksort (l, 0, size - 1);
  print_list (l, size - 1);
}

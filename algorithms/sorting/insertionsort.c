#include <stdlib.h>
#include <stdio.h>

void insertionsort (int *ar, int ar_size);

static void
print_array (int *l, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}


void
insertion_sort (int *ar, int ar_size)
{
  int c, j, tmp;

  for (c = 1; c < ar_size; c++) {
    tmp = ar[c];
    j = c - 1;
    while (tmp < ar[j] && j >= 0) {
      ar[j + 1] = ar[j];

      j--;
    }

    ar[j + 1] = tmp;
    // print_array (ar, ar_size);
  }

}


int
main ()
{
  int ar[50];
  int size = 50;
  int c;
  for (c = 0; c < size; c++)
    ar[c] = rand () % 100;

  printf ("out of order:\n");
  print_array (ar, size);

  printf ("in order:\n");
  insertion_sort (ar, size);
  print_array (ar, size);
}

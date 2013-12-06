/* Counting Sort. O(n) where n is the size of the range of values        */
/* Useful when the range of values is small relative to the size of list */

#include <stdio.h>
#include <stdlib.h>


void
print_list (int *l, int size)
{
  int c;
  for (c = 0; c < size; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}

void
count_sort (int size, int *list, int low, int high)
{
  int *count_ar = (int *) malloc ((high - low) * sizeof (int));
  int c, d, value, range;

  range = high - low;
  // Initialize all elements of count array to 0
  for (c = 0; c < range; c++) {
    count_ar[c] = 0;
  }

  // Go through the list incrementing the count of each value seen
  for (c = 0; c < size; c++) {
    value = list[c] - low;
    count_ar[value]++;
  }

  // Go through the count array and move the seen values to sorted list
  d = 0;
  for (c = 0; c < range; c++) {
    while (count_ar[c] > 0) {
      list[d++] = c + low;
      count_ar[c]--;
    }
  }

  free (count_ar);

  return;
}

int
main ()
{
  int size = 25;
  int l[25];
  int c;
  for (c = 0; c < size; c++) {
    l[c] = (rand () % 25) + 25;
  }

  printf ("out of order: \n");
  print_list (l, size);

  printf ("in order: \n");
  count_sort (size, l, 25, 50);
  print_list (l, size);

  return 0;
}

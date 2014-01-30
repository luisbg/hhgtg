/* Recursive Binary Search */


#include <stdio.h>


static int middle (int *list, int key, int low, int high);
static int interpolation_search (int *list, int key, int low, int high);
int search (int *list, int key, int low, int high);


static int step = 0;


static int
middle (int *list, int key, int low, int high)
{
  return (low + high) / 2;
}

static int
interpolation_search (int *list, int key, int low, int high)
{
  return low + (key - list[low]) * (high - low) / (list[high] - list[low]);
}

int
search (int *list, int key, int low, int high)
{
  // printf ("step: %d :: %d %d\n", step++, low, high);

  // int p = middle (list, key, low, high);
  int p = interpolation_search (list, key, low, high);

  if (key == list[p])           // base case: key found
    return p;

  // ERROR checks
  if (low == p)                 // element not in the list
    return -1;

  if (low > high)               // limits out of order
    return -2;

  if (list[low] > list[high])   // list not sorted
    return -3;

  if (key < list[p])
    search (list, key, low, p - 1);
  else
    search (list, key, p + 1, high);
}

void
print (int *list, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", list[c]);
  }
  printf ("\n");
}


int
main ()
{
  int size = 10;
  int list[10] = { 0, 1, 3, 5, 7, 11, 13, 17, 19, 23 };

  print (list, size);
  printf ("pos of %d is %d\n", 3, search (list, 3, 0, size - 1));

  printf ("pos of %d is %d\n", 18, search (list, 18, 0, size - 1));
}

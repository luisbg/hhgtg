#include <stdio.h>


static int step = 0;


int middle (int *l, int key, int low, int high)
{
  return (low + high) / 2;
}

int interpolation_search (int *l, int key, int low, int high)
{
  return low + (key - l[low]) * (high-low) / (l[high] - l[low]);
}

int search (int *l, int key, int low, int high)
{
  // printf ("step: %d\n", step++);

  // int p = middle (l, key, low, high);
  int p = interpolation_search (l, key, low, high);

  if (l[p] == key)
    return p;

  if ((high - low) < 1)
    return -1;

  if (key < l[p])
    search (l, key, low, p - 1);
  else
    search (l, key, p + 1, high);
}

void print (int *l, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}


int main ()
{
  int size = 10;
  int l[10] = { 0, 1, 3, 5, 7, 11, 13, 17, 19, 23 };

  print (l, size);
  printf ("pos of %d is %d\n", 3, search (l, 3, 0, size-1));
}

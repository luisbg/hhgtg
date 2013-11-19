#include <stdio.h>

unsigned long
factorial (int n)
{
  if (n == 0)
    return 1;

  return n * factorial (n - 1);
}


int
main ()
{
  int set[10] = { 1, 2, 3, 5, 8, 10, 12, 15, 18, 20 };
  int c;

  for (c = 0; c < 10; c++) {
    printf ("factorial of %d: %ld\n", set[c], factorial (set[c]));
  }
}

#include <stdio.h>
#include <stdlib.h>


int
fibonacci_recursive (int i)     // O(n^2)
{
  if (i < 0)
    return -1;

  if (i == 0 || i == 1)
    return i;

  return fibonacci_recursive (i - 1) + fibonacci_recursive (i - 2);
}

unsigned long long
fibonacci_dynamic (unsigned long long i, unsigned long long fib[])      // O(n)
{
  if (i < 0)
    return -1;

  if (i == 0 || i == 1)
    return i;

  // return cache
  if (fib[i] != 0)
    return fib[i];

  // cache result
  fib[i] = fibonacci_dynamic (i - 1, fib) + fibonacci_dynamic (i - 2, fib);
  return fib[i];
}

unsigned long long
fibonacci_iterative (int i)
{
  if (i < 0)
    return -1;

  if (i == 0)
    return 0;

  unsigned long long a = 0, b = 1, tmp;

  for (int c = 1; c < i; c++) {
    tmp = a;
    a = b;
    b = tmp + b;
  }

  return b;
}

int
main ()
{
  int seq[10] = { 1, 2, 3, 4, 5, 10, 25, 50, 75, 100 };

  int c;
  for (c = 0; c < 10; c++) {
    unsigned long long *fib = (unsigned long long *) calloc (seq[c] + 1,
        sizeof (unsigned long long));
    printf ("fibonnaci number %d: %lld\n", seq[c],
        fibonacci_dynamic (seq[c], fib));
    free (fib);

    // printf("%lld\n", fibonacci_iterative (seq[c]));
  }
}

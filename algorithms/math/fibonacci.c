#include <stdio.h>


int
fibonacci_recursive (int i)     // O(n^2)
{
  if (i == 0)
    return 0;
  if (i == 1)
    return 1;

  return fibonacci_recursive (i - 1) + fibonacci_recursive (i - 2);
}

int fib[50] = { 0 };

int
fibonacci_dynamic (int i)       // O(n)
{
  if (i == 0)
    return 0;
  if (i == 1)
    return 1;

  // return cache
  if (fib[i] != 0)
    return fib[i];

  // cache result
  fib[i] = fibonacci_dynamic (i - 1) + fibonacci_dynamic (i - 2);
  return fib[i];
}

int
main ()
{
  int seq[10] = { 1, 2, 3, 4, 5, 10, 20, 40, 42, 48 };

  int c;
  for (c = 0; c < 10; c++) {
    printf ("fibonnaci number %d: %d\n", seq[c], fibonacci_dynamic (seq[c]));
  }
}

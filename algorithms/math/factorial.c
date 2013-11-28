#include <stdio.h>
#include <stdlib.h>

unsigned long
factorial (int n)
{
  if (n == 0)
    return 1;

  return n * factorial (n - 1);
}

unsigned long
do_all_factorials (int n, unsigned long *results, int level)
{
  if (n > 1)                    // recursive case
    results[level] = n * do_all_factorials (n - 1, results, level + 1);
  else {
    results[level] = 1;
    return 1;
  }
}

unsigned long *
all_factorials (int n)
{
  unsigned long *results = (unsigned long *) malloc (n *
      sizeof (unsigned long));
  do_all_factorials (n, results, 0);
  return results;
}

unsigned long
factorial_iterative (int n)
{
  int c;
  unsigned long ret = 1;
  for (c = n; c > 1; c--)       // 0 or 1 fall through
    ret *= c;
  return ret;
}

int
main ()
{
  int set[10] = { 1, 2, 3, 5, 8, 10, 12, 15, 18, 20 };
  int c;

  for (c = 0; c < 10; c++) {
    if (c % 2 == 0)
      printf ("factorial of %d: %ld\n", set[c], factorial (set[c]));
    else
      printf ("factorial of %d: %ld\n", set[c], factorial_iterative (set[c]));
  }

  int n = 20;
  int lvl;
  unsigned long *results = (unsigned long *) malloc (n *
      sizeof (unsigned long));
  results = all_factorials (n);
  for (c = 0; c < 20; c++) {
    lvl = (n - c) % n;
    if (!lvl)
      lvl = 20;
    printf ("%d: %ld\n", lvl, results[c]);
  }
}

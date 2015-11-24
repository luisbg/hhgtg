#include <stdio.h>
#include <stdlib.h>


/* recursive power: raise base to n-th power; n >= 0 || n < 0 */
double
power (double b, int n)
{
  if (n == 0)
    return 1.0;

  if (n > 0)
    return (b * power (b, n - 1));

  if (n < 0)
    return (power (1 / b, -1 * n));

  return 1.0;
}

/* test power function */
int
main ()
{
  int i;
  for (i = -5; i < 10; ++i)
    printf ("%d: 2^x= %.2f   -3^x= %.2f\n", i, power (2, i), power (-3, i));

  return 0;
}

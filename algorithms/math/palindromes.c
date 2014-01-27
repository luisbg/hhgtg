/* A palindromic number reads the same both ways. The largest palindrome made */
/* from the product of two 2-digit numbers is 9009 = 91 × 99. */
/* Find the largest palindrome made from the product of two 3-digit numbers. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
  FALSE, TRUE
} bool;

bool is_palindrome (int num)
{
  int num_digits;
  int tmp = num;
  int th;
  int i;

  for (num_digits = 0; tmp > 0; num_digits++) {
    tmp = tmp / 10;
  }

  int *digits = (int *) malloc (num_digits * sizeof (int));

  tmp = num_digits;
  for (i = 0; tmp > 0; tmp--) {
    th = pow (10, tmp - 1);
    digits[i] = num / th;
    num = num % th;
    i++;
  }

  tmp = num_digits - 1;
  i = 0;
  while (i < tmp) {
    if (digits[i] != digits[tmp])
      return FALSE;

    i++;
    tmp--;
  }

  free(digits);

  return TRUE;
}

unsigned long biggest_palindrome (int top)
{
  int c, d;
  unsigned long biggest = 0;
  unsigned long prod;

  for (d = top; d > (sqrt(top) * 2); d--) {
    for (c = top; c > (sqrt(top) * 2); c--) {
      prod = c * d;
      if (is_palindrome (prod))
        break;
    }

    if (prod > biggest) {
      biggest = prod;
      printf ("%d, %d\n", d, c);
    }
  }


  return biggest;
}

int main ()
{
  printf ("largest palindrome of two digit numbers: %d\n",
      biggest_palindrome (999));

  return 0;
}

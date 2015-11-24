/* Write a function to compute the binary representation of an integer. Return
 * the representation as a number. Assume the input will be a positive integer
 * only.
 *
 * Examples:
 * computeBinary(6) ==> 110
 * computeBinary(8) ==> 1000
 */

#include <stdio.h>


int
dec_to_binary (int num)
{
  int bin = 0;
  int digit = 1;

  while (num > 0) {
    bin = ((num % 2) * digit) + (bin);
    num = num / 2;
    digit = digit * 10;
  }

  return bin;
}

/* test compute_binary */
int
main ()
{
  int i;
  for (i = 0; i < 32; i++)
    printf ("%2d :: \t%6d\n", i, dec_to_binary (i));

  return 0;
}

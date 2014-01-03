#include <stdlib.h>
#include <stdio.h>
#include <math.h> /* needed for sqrt() */

typedef enum
{
  FALSE, TRUE
} bool;

bool is_it_prime_naive (int n)
{
  int c;  // counter
  int sqr;  // square root of n

  if (n < 2)
    return FALSE;

  sqr = (int) sqrt(n);  // assuming it is in int range since square root of an int
  for (c = 2; c <= sqr; c++) {
    if (n % c == 0)
      return FALSE;
  }

  return TRUE;
}

bool is_it_prime_eratosthenes (int n)
{
  int c, d; // counters
  if (n < 2)
    return FALSE;


  int sqr = (int) sqrt(n); // square root of n
  bool *primes = (bool *) malloc (n * sizeof (bool));

  for (c = 0; c < n; c++)  // array of primes n might be divisible by
    primes[c] = TRUE;

  for (c = 4; c < sqr; c += 2) { // set all odd numbers past 2 as non-prime
    primes[c] = FALSE;
  }

  for (c = 2; c <= sqr; c++) { // run through primes and multiples of them.
    if (primes[c]) {           // mark the multiples as not primes.
      if (n % c == 0)
        return FALSE;
      else {
        for (d = 2; (d * c) < sqr; d++) {
          primes[d*c] = FALSE;
        }
      }
    }
  }

  return TRUE;
}

int main ()
{
  int n;
  int max = 1000; // speed test with 1 thousand
  int found = 0;

  printf ("list %d first primes:\n", max);
  for (n = 1; found < max; n++) {
    if (is_it_prime_naive (n)) {
    // if (is_it_prime_eratosthenes (n)) {
      printf ("%d ", n);
      found++;
    }
  }

  printf ("\n");
}

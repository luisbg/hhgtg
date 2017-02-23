#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;


bool
is_it_prime (int n)
{
  if (n < 2)
    return FALSE;

  for (int c = 2; c * c <= n; c++) {
    if (n % c == 0)
      return FALSE;
  }

  return TRUE;
}

// Eratosthenes works to check small numbers. For big numbers there could be
// memory issues.
// Specially suited when a cache needs to be generated to check if a series of
// numbers are prime.
void
generate_eratosthenes (int max, bool * primes)
{
  primes[0] = FALSE;
  primes[1] = FALSE;
  for (int c = 2; c < max; c++) // init all to prime
    primes[c] = TRUE;

  for (int c = 2; c * c < max; c++) {   // run through primes and multiples of them.
    if (primes[c]) {            // mark the multiples as not primes.
      for (int d = c + c; d < max; d += c) {
        primes[d] = FALSE;
      }
    }
  }

}

bool
is_it_prime_eratosthenes (int n, bool * primes)
{
  return primes[n];
}

int main ()
{
  int n;
  int max = 1000; // speed test with 1 thousand
  int found = 0;

  bool *primes = (bool *) malloc (max * 8 * sizeof (bool));
  generate_eratosthenes (max * 8, primes);

  printf ("list %d first primes:\n", max);
  for (n = 1; found < max; n++) {
    if (is_it_prime_eratosthenes (n, primes)) {
      printf ("%d ", n);
      found++;
    }
  }

  free (primes);
  return 0;
}

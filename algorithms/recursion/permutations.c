/* Implement a routine that prints all possible orderings of the characters in
 * a string. In other words, print all permutations that use all the characters
 * from the original string. For example, given the string “hat”, your function
 * should print the strings “tha”, “aht”, “tah”, “ath”, “hta”, and “hat”. Treat
 * each character in the input string as a distinct character, even if it is
 * repeated. Given the string “aaa”, your routine should print “aaa” six times.
 * You may print the permutations in any order you choose.
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  FALSE, TRUE
} bool;

// Based on Heap's Algorithm from
// Introduction to the Design and Analysis of Algorithms by Levitin

void
print (char *v, int size)
{
  int c;
  if (v) {
    for (c = 0; c < size; c++) {
      printf ("%c", v[c]);
    }
    printf ("\n");
  }
}

void
swap (char *i, char *j)
{
  char t;
  t = *i;
  *i = *j;
  *j = t;
}

void
heap_permute (char **str, int n, int size)
{
  int i;
  if (n == 1)
    print (*str, size);
  else {
    for (i = 0; i < n; i++) {
      heap_permute (str, n - 1, size);
      if (n % 2 == 1)           // if n is odd
        swap (&(*str)[0], &(*str)[n - 1]);
      else                      // if n is even
        swap (&(*str)[i], &(*str)[n - 1]);
    }
  }
}


int
main ()
{
  int size = 3;
  char *str = (char *) malloc (size * sizeof (char));
  char *tmp = "hat";
  int c;
  for (c = 0; c < size; c++)
    str[c] = tmp[c];

  heap_permute (&str, size, size);

  printf ("\n");

  size = 4;
  tmp = "four";
  for (c = 0; c < size; c++)
    str[c] = tmp[c];

  heap_permute (&str, size, size);
}

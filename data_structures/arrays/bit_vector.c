/*  The array can be viewed as a subset of the domain (e.g. {0, 1, 2, ..., n−1}),
 * where a 1 bit indicates a number in the set and a 0 bit a number not in the
 * set. This set data structure uses about n/w words of space, where w is the
 * number of bits in each machine word.
 */

#include <stdio.h>
#include <stdlib.h>


int *
vector_init (int size)
{
  int i;
  int * vector = (int *) malloc ((size >> 5) * sizeof (int));    // divide by 32

  for (i = 0; i < (size >> 5); i++)
    vector[i] = 0;

  return vector;
}

int
vector_get (int * bitvector, int pos)
{
  int word_num = (pos >> 5);   // divide by 32
  int bit_num = (pos & 0x1F);  // mod by 32

  return (bitvector[word_num] & (1 << bit_num)) != 0;
}

void
vector_set (int * bitvector, int pos)
{
  int word_num = (pos >> 5);   // divide by 32
  int bit_num = (pos & 0x1F);  // mod by 32

  bitvector[word_num] |= (1 << bit_num);
}


int main ()
{
  int i, r, set = 10, max = 30000;

  int * vector = vector_init (max);

  for (i = 0; i < set; i++) {
    r = rand () % max;
    printf ("set number %d\n", r);
    vector_set (vector, r);

    printf ("%d is: %c\n", r, vector_get (vector, r)? '1': '0');
    printf ("%d is: %c\n\n", r + 1, vector_get (vector, r + 1)? '1': '0');
  }

  return 0;
}


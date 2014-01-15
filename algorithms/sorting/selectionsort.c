/* Selection Sort
 *
 * Despite it's brute-force approach, selection sort outperforms more
 * sophisticated algorithms when sorting files with huge items and small
 * keys. The cost of moving data dominates the cost of making comparisons.
 * No algorithm can sort a file with substantially less data movement than
 * selection sort.
*/

#include <stdlib.h>
#include <stdio.h>


typedef int Item;
#define less(A, B) (A < B)
#define exch(A, B) { Item t = A; A = B; B = t; }
#define RANDMAX 100

void selection_sort (Item a[], int l, int r);


void
selection_sort (Item a[], int l, int r)
{
  int i, j;

  for (i = l; i < r; i++) {
    int min = i;

    for (j = i + 1; j <= r; j++)
      if (less (a[j], a[min]))
        min = j;
    exch (a[i], a[min]);
  }
}


int
main (int argc, char *argv[])
{
  int i;
  int N = atoi (argv[1]);

  int *a = malloc (N * sizeof (int));

  printf ("sorting %d random numbers from 0 to %d:\n", N, RANDMAX);
  for (i = 0; i < N; i++)
    a[i] = rand () % RANDMAX;

  selection_sort (a, 0, N - 1);

  for (i = 0; i < N; i++)
    printf ("%3d ", a[i]);
  printf ("\n");

  return 0;
}

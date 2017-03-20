/* Given an index k, return the kth row of the Pascal's triangle. */
/* https://en.wikipedia.org/wiki/Pascal's_triangle */

#include <stdio.h>
#include <stdlib.h>


void
populate_pascal (int size, int grid[size][size])
{
  // first column is all 1
  for (int c = 0; c < size; c++)
    grid[c][0] = 1;

  for (int r = 1; r < size; r++) {
    for (int c = 1; c < size; c++) {
      grid[r][c] = grid[r - 1][c - 1] + grid[r - 1][c];
    }
  }
}

void
print_grid (int size, int grid[size][size])
{
  for (int r = 0; r < size; r++) {
    for (int c = 0; c < size; c++) {
      printf ("%d", grid[r][c]);
    }
    printf ("\n");
  }
}

int *
get_row (int rowIndex, int *returnSize)
{
  int pasc_size = rowIndex + 1;
  int pasc[pasc_size][pasc_size];
  for (int r = 0; r < pasc_size; r++)
    for (int c = 0; c < pasc_size; c++)
      pasc[r][c] = 0;

  populate_pascal (pasc_size, pasc);

  // print_grid (pasc_size, pasc);

  int *ret = (int *) malloc (pasc_size * sizeof (int));
  for (int c = 0; c < pasc_size; c++)
    ret[c] = pasc[rowIndex][c];

  *returnSize = pasc_size;
  return ret;
}

void
print_pascal_row (int r)
{
  int size;
  int *row = get_row (r, &size);

  for (int c = 0; c < size; c++) {
    printf ("%d ", row[c]);
  }
  printf ("\n");
}

int
main ()
{
  printf ("Third row of Pascal's triangle:\n");
  print_pascal_row (3);

  printf ("Fifth row of Pascal's triangle:\n");
  print_pascal_row (5);

  printf ("Tenth row of Pascal's triangle:\n");
  print_pascal_row (10);

  return 0;
}

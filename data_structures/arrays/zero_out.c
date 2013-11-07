/* Write an algorithm such that if an element in an MxN matrix is 0, its      */
/* row and column are set to 0.                                               */

#include <stdlib.h>
#include <stdio.h>

typedef enum
{ FALSE, TRUE } bool;

void
zero_out (int m, int n, int matrix[m][n])
{
  int x, y;
  bool *row_ok = malloc (m * sizeof (bool));
  for (y = 0; y < m; y++) {
    row_ok[y] = TRUE;
  }
  bool *col_ok = malloc (n * sizeof (bool));
  for (x = 0; x < n; x++) {
    col_ok[x] = TRUE;
  }

  int z;
  for (x = 0; x < m; x++) {
    for (y = 0; y < n; y++) {
      if (col_ok[x] && row_ok[y]) {
        if (matrix[x][y] == 0) {
          for (z = 0; z < m; z++) {
            matrix[z][y] = 0;
          }

          for (z = 0; z < n; z++) {
            matrix[x][z] = 0;
          }

          row_ok[x] = FALSE;
          col_ok[y] = FALSE;
        }
      }
    }
  }

  free (row_ok);
  free (col_ok);
}

void
show_array (int m, int n, int arr[m][n])
{
  int x, y;
  for (x = 0; x < m; x++) {
    for (y = 0; y < n; y++) {
      printf ("%d ", arr[x][y]);
    }
    printf ("\n");
  }

  printf ("\n");
}

int
main ()
{
  int matrix[6][5] = { {1, 2, 3, 4, 5},
  {6, 0, 8, 9, 10},
  {11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20},
  {21, 22, 23, 0, 25},
  {26, 27, 28, 29, 30}
  };
  show_array (6, 5, matrix);

  zero_out (6, 5, matrix);
  show_array (6, 5, matrix);
}

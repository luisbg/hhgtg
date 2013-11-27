/* Lattice Paths
 *
 * Starting in the top left corner of a 2×2 grid, and only being able to move
 * to the right and down, there are exactly 6 routes to the bottom right corner.
 *
 * How many such routes are there through a 20×20 grid?
 *
 * Project Euler #15
 */

#include <stdio.h>

void travel_grid (int size, unsigned long grid[size][size]);

unsigned long lattice_paths (int size, unsigned long grid[size][size]) {
  int c, r;

  grid[0][0] = 0;

  for (c = 1; c < size; c++) {
    grid[c][0] = 1;
    grid[0][c] = 1;
  }

  for (r = 1; r < size; r++) {
    for (c = 1; c < size; c++) {
      grid[c][r] = grid[c-1][r] + grid[c][r-1];
    }
  }

  // travel_grid (size, grid); 

  return grid[size -1][size - 1]; 
}

unsigned long lattice_combinatronics (int size, unsigned long grid[size][size])
{
  unsigned long paths = 1;
  int i;
 
  size--; // based on grid (edges traveled) and not array (spaces traveled)
  for (i = 0; i < size; i++) {
    paths *= (2 * size) - i;
    paths /= i + 1;
  }

  return paths;
}

void travel_grid (int size, unsigned long grid[size][size]) {
  int c, r;
  for (r = 0; r < size; r++) {
    for (c = 0; c < size; c++) {
      printf ("%ld ", grid[c][r]);
    }
    printf ("\n");
  }

  return;
}

int main () {
  unsigned long grid[21][21];
  unsigned long paths;

  paths = lattice_paths (21, grid);

  printf ("paths: %ld\n", paths);

  return 0;
} 

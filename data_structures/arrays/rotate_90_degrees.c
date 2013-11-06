#include <stdlib.h>
#include <stdio.h>


void show_array (int size, int arr[size][size]) {
  int x, y;
  for (x = 0; x < size; x++) {
    for (y = 0; y < size; y++) {
      printf("%d ", arr[x][y]);
    }
    printf("\n");
  }

  printf("\n");
}

void rotate_90_degrees (int size, int arr[size][size], int new[size][size]) {
  new = malloc (size * size * sizeof(int));

  int x, y;
  int new_y;
  for (x = 0; x < size; x++) {
    for (y = 0; y < size; y++) {
      if (x <= size)
        new_y = (size-1) - x;
      else
        new_y = x - (size-1);

      new[x][y] = arr[y][new_y];
    }
  }

  show_array(4, new);
}


int main () {
  int arr[4][4] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
  int rot[4][4];

  show_array(4, arr);

  rotate_90_degrees (4, arr, rot);
}

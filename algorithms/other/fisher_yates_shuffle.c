#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static void swap (int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void shuffle (int size, int set[size]) {
  int i;

  for (i = 0; i < (size - 1); i++) {
    swap (&set[i], &set[rand () % size]);
  }
}


int main () {
  int size = 16;
  int set[16];
  int i;

  /* use time as seed for pseud-randomness */
  srand(time(NULL));

  /* new sorted deck */
  for (i = 0; i < size; i++)
    set[i] = i + 1;

  printf ("sorted set: \t\t\t");
  for (i = 0; i < size; i++)
    printf (" %2d", set[i]);
  printf ("\n");

  shuffle (size, set);

  printf ("fisher yates shuffled set: \t");
  for (i = 0; i < size; i++)
    printf (" %2d", set[i]);
  printf ("\n");

  return 0;
}


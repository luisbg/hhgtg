/* Inspired by FireCode problem 11 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void print_array (int arrayList[], int sz);

void rotate_left(int arraylist[], int sz, int k){
    int rc, r, save_first;

    // iterate the amount of rotations needed
    for (rc = 0; rc < k; rc++) {
        // move all once to the left
        save_first = arraylist[0];
        for (r = 0; r < (sz - 1); r++)
            arraylist[r] = arraylist[r + 1];
        arraylist[sz - 1] = save_first;
    }
}

void print_array (int arrayList[], int sz)
{
  int i;

  for (i = 0; i < sz; i++)
      printf ("%3d ", arrayList[i]);

  printf ("\n");
}

void generate_list (int arrayList[], int sz)
{
  int i;

  for (i = 0; i < sz; i++)
    arrayList[i] = i;
}

int main ()
{
  int sz = 10;
  int array[10];
  int k;

  /* use time as seed for pseud-randomness */
  srand(time(NULL));

  printf ("original list:\n");
  generate_list (array, sz);
  print_array (array, sz);

  k = rand () % (sz * 2);
  printf ("list rotated by %d:\n", k);
  rotate_left (array, sz, k);
  print_array (array, sz);

  return 0;
}

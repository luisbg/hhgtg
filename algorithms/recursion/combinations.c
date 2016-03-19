/* Non-unique combinations of X values in Y digits
 * Also known as Multisubsets
 * or k-combination with repetitions, or k-multicombination
 *
 * https://en.wikipedia.org/wiki/Combination
 */

#include <stdlib.h>
#include <stdio.h>

void print_combo (int digits, int step[digits])
{
  int i;

  for (i = 0; i < digits; i++) {
    printf("%d ", step[i]);
  }
  printf("\n");
}

void generate_recurse (int digits, int step[digits], int set_size,
                       int set[set_size], int level)
{
  int i;

  if (level == digits) {
    print_combo (digits, step);
    return;
  }

  for (i = 0; i < set_size; i++) {
    step[level] = set[i];
    generate_recurse (digits, step, set_size, set, level + 1);
  }
}

void generate_combinations (int digits, int step[digits], int set_size,
                            int set[set_size])
{
  generate_recurse (digits, step, set_size, set, 0);
}

int
main ()
{
  int digits = 2;
  int step[digits];
  int set_size = 8;
  int num_set[set_size];
  int i;

  for (i = 0; i < set_size; i++) {
    num_set[i] = i;
  }

  /* generate combination of octal numbers */
  generate_combinations (digits, step, set_size, num_set);

  return 0;
}

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

void generate_recurse (int digits, int step[digits], int range, int level)
{
  int i;

  if (level == digits) {
    print_combo (digits, step);
    return;
  }

  for (i = 0; i <= range; i++) {
    step[level] = i;
    generate_recurse (digits, step, range, level + 1);
  }
}

void generate_combinations (int digits, int step[digits], int range)
{
  generate_recurse (digits, step, range, 0);
}

int
main ()
{
  int digits = 4;
  int step[digits];
  int range = 3;

  generate_combinations (digits, step, range);

  return 0;
}

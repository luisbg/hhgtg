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
    (step[i] < 10) ? printf("%d ", step[i]) : printf("%c ", step[i]);
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

  printf("\n");

  /* generate padlock combinations when it is 4 wheels of A to C */
  digits = 3;
  set_size = 3;
  int second_step[digits];
  int letter_set[set_size];

  for (i = 0; i < set_size; i++) {
    letter_set[i] = 'A' + i;
  }

  generate_combinations (digits, second_step, set_size, letter_set);

  return 0;
}

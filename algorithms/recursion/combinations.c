/* Non-unique combinations of X values in Y positions
 * Also known as Multisubsets
 * or k-combination with repetitions, or k-multicombination
 *
 * https://en.wikipedia.org/wiki/Combination
 */

#include <stdlib.h>
#include <stdio.h>

void
print_combo (int positions, int combo[positions])
{
  int i;

  for (i = 0; i < positions; i++) {
    (combo[i] < 10) ? printf ("%d ", combo[i]) : printf ("%c ", combo[i]);
  }
  printf ("\n");
}

void
generate_recurse (int positions, int combo[positions], int set_size,
    int set[set_size], int level)
{
  int i;

  if (level == positions) {
    print_combo (positions, combo);
    return;
  }

  for (i = 0; i < set_size; i++) {
    combo[level] = set[i];
    generate_recurse (positions, combo, set_size, set, level + 1);
  }
}

void
generate_combinations (int positions, int combo[positions], int set_size,
    int set[set_size])
{
  generate_recurse (positions, combo, set_size, set, 0);
}

int
main ()
{
  int positions = 2;
  int combo[positions];
  int set_size = 8;
  int num_set[set_size];
  int i;

  for (i = 0; i < set_size; i++) {
    num_set[i] = i;
  }

  /* generate combination of octal numbers */
  generate_combinations (positions, combo, set_size, num_set);

  printf ("\n");

  /* generate padlock combinations when it is 4 wheels of A to C */
  positions = 3;
  set_size = 3;
  int second_combo[positions];
  int letter_set[set_size];

  for (i = 0; i < set_size; i++) {
    letter_set[i] = 'A' + i;
  }

  generate_combinations (positions, second_combo, set_size, letter_set);

  return 0;
}

/* Non-unique combinations of X values in Y positions
 * Also known as Multisubsets
 * or k-combination with repetitions, or k-multicombination
 *
 * https://en.wikipedia.org/wiki/Combination
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

/* only supports combinations of 3 positions */
void
iterative_combinations (int set_size, int set[set_size], int positions)
{
  int n;
  int val[3];
  int c[3];
  int pos;

  /* init c[] */
  for (n = 0; n < set_size; ++n) {
    c[n] = 0;
    val[n] = 0;
  }

  /* generate combinations */
  for (n = 0; n < pow (set_size, positions); n++) {
    printf ("%c %c %c\n", set[val[0]], set[val[1]], set[val[2]]);

    pos = 0;
    c[2]++;
    if (c[2] == pow (set_size, pos)) {
      c[2] = 0;
      val[2]++;
      if (val[2] == set_size)
        val[2] = 0;
    }

    pos++;
    c[1]++;
    if (c[1] == pow (set_size, pos)) {
      c[1] = 0;
      val[1]++;
      if (val[1] == set_size)
        val[1] = 0;
    }

    pos++;
    c[0]++;
    if (c[0] == pow (set_size, pos)) {
      c[0] = 0;
      val[0]++;
      if (val[0] == set_size)
        val[0] = 0;
    }
  }
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

  printf ("generate combination of octal numbers\n");
  generate_combinations (positions, combo, set_size, num_set);

  positions = 3;
  set_size = 3;
  int second_combo[positions];
  int letter_set[set_size];

  for (i = 0; i < set_size; i++) {
    letter_set[i] = 'A' + i;
  }

  printf ("\ngenerate padlock combinations when it is 4 wheels of A to C\n");
  generate_combinations (positions, second_combo, set_size, letter_set);

  for (i = 0; i < set_size; i++) {
    letter_set[i] = 'X' + i;
  }

  printf ("\ngenerate padlock combinations iteratively\n");
  iterative_combinations (set_size, letter_set, positions);

  return 0;
}

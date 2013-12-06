/* Slice array in 3 groups: low, middle and high */

#include <stdio.h>
#define SIZE 15


static int
islow (char c)
{
  if (c <= 'j') {
    // printf("%c is low\n", c);
    return 1;
  }
  return 0;
}

static int
ismedium (char c)
{
  if (c > 'j' && c <= 'q')
    return 1;
  return 0;
}

static int
ishigh (char c)
{
  if (c > 'q')
    return 1;
  return 0;
}

int
sort (char *array, int size)
{
  int low = 0;
  int high = size - 1;
  int i;
  char c;
  for (i = 0; i < size && i < high;) {
    if (islow (array[i])) {
      c = array[low];
      array[low] = array[i];

      // printf("array[%d] = %c\n", low, array[i]);
      array[i] = c;
      low++;
    }
    if (ishigh (array[i])) {
      c = array[high];
      array[high] = array[i];
      array[i] = c;
      high--;
    }

    /* If is medium, then move along always, medium will fall into place by itself */
    if (ismedium (array[i]))
      i++;

    /* Incrementing i when islow (first if) doesn't solve the problem, because we already swapped.
     * If the character islow, we should check that it is in the beginning, before low pointer*/
    if (low > i)
      i++;
  }
}

int
main ()
{
  char array[SIZE] = "btenxlwadzubnmw";
  int i;

  for (i = 0; i < SIZE; i++)
    printf ("%c ", array[i]);
  printf ("\n");

  sort (array, SIZE);

  for (i = 0; i < SIZE; i++)
    printf ("%c ", array[i]);
  printf ("\n");

  return 0;
}

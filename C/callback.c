#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* The calling function takes a single callback as a parameter.
 *
 * You could use this to add a callback function in the event table
 * of an event-driven system
 */
void
print_a_number (int (*number_source) (void))
{
  printf ("%d\n", number_source ());
}

/* A possible callback */
int
generate_key (void)
{
  return (rand () % 89999) + 10000;
}

/* Here we call print_a_number() with two different callbacks. */
int
main (void)
{
  srand (time (NULL));

  printf ("Random number: ");
  print_a_number (&rand);

  printf ("5 digit key: ");
  print_a_number (&generate_key);

  return 0;
}

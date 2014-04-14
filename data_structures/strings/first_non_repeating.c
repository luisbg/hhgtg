#include <stdio.h>
#include <stdlib.h>


char
first_non_repeat (char *in)
{
  int *charcount = (int *) calloc (2 << sizeof (char), sizeof (int));
  int len;
  int i;

  for (i = 0; in[i]; i++) {
    charcount[in[i]]++;
  }

  len = i - 1;
  for (i = 0; i < len; i++) {
    if (charcount[in[i]] == 1) {
      return in[i];
    }
  }

  return '\0';
}

int
main ()
{
  char *str = "this is the best";
  printf ("the first non-repeating character of: %s\nis: %c\n",
      str, first_non_repeat ("this is the best"));

  return 0;
}

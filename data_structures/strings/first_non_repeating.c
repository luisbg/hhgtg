#include <stdio.h>
#include <stdlib.h>


int
str_len (char *str)
{
  int l = 0;
  while (str[l] != '\0') {
    l++;
  }

  return l;
}

char
first_non_repeat (char *in)
{
  int i;
  int *charcount = (int *) calloc (2 << sizeof (char), sizeof (int));
  int len = str_len (in);

  for (i = 0; i < len; i++) {
    charcount[in[i]]++;
  }

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

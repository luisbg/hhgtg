#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{ FALSE, TRUE } bool;

void
string_sort (char *s, int length)
{
  char tmp;
  int i, j;

  for (i = 0; i < length - 1; i++) {
    for (j = i + 1; j < length; j++) {
      if (s[i] > s[j]) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
      }
    }
  }
}

bool
permutation (char *first, char *second)
{
  int c;
  for (c = 0; first[c]; c++) {
  }
  int len = c;

  for (c = 0; second[c]; c++) {
  }
  int len_second = c;

  if (len != len_second)
    return FALSE;

  char *sorted_first = (char *) malloc (len * sizeof (char));
  strcpy (sorted_first, first);
  char *sorted_second = (char *) malloc (len * sizeof (char));
  strcpy (sorted_second, second);

  string_sort (sorted_first, len);
  string_sort (sorted_second, len);

  for (c = 0; c < len; c++) {
    if (sorted_first[c] != sorted_second[c])
      return FALSE;
  }

  return TRUE;
}


int
main ()
{
  char *a = "dad ";
  char *b = " add";
  printf ("%s:%s :: permutation? %s\n", a, b, permutation (a,
          b) ? "yes" : "no");
  a = "troll";
  b = "hunter";
  printf ("%s:%s :: permutation? %s\n", a, b, permutation (a,
          b) ? "yes" : "no");
  a = "same length ";
  b = "not the same";
  printf ("%s:%s :: permutation? %s\n", a, b, permutation (a,
          b) ? "yes" : "no");
  a = "radar";
  b = "radar";
  printf ("%s:%s :: permutation? %s\n", a, b, permutation (a,
          b) ? "yes" : "no");
}

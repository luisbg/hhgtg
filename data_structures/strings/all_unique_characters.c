/* Algorithm to determine if a string has all unique characters.              */
/* What if you cannot use additional data structures?                         */

#include <stdio.h>

typedef enum
{ FALSE, TRUE } bool;

bool
all_unique_characters (char *str)
{
  if (str == NULL)
    return TRUE;

  int c;
  int n;
  for (c = 0; str[c] != 0; c++) {
    for (n = c + 1; str[n] != 0; n++) {
      if (str[c] == str[n]) {
        return FALSE;
      }
    }
  }

  return TRUE;
}

int
main ()
{
  char *test = "";
  printf ("%s :: unique characters: %s\n", test,
      all_unique_characters (test) ? "yes" : "no");
  test = "hello";
  printf ("%s :: unique characters: %s\n", test,
      all_unique_characters (test) ? "yes" : "no");
  test = "world";
  printf ("%s :: unique characters: %s\n", test,
      all_unique_characters (test) ? "yes" : "no");
}

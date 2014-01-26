/* Given two strings, decide if one is an anagram of the other. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ASCII_SIZE 256

static int count;

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
anagram_by_sort (char *first, char *second)
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

int *
letter_counter (char *str, int len)
{
  int *ret = (int *) malloc (ASCII_SIZE * sizeof (int));
  int c;
  for (c = 0; c < ASCII_SIZE; c++) {
    ret[c] = 0;
  }

  for (c = 0; c < len; c++) {
    ret[str[c]]++;
  }

  return ret;
}

bool
anagram_by_count (char *first, char *second)
{
  int len = strlen (first);
  if (len != strlen (second))
    return FALSE;

  int *first_count;
  first_count = letter_counter (first, len);
  int *second_count;
  second_count = letter_counter (second, len);

  int c;
  if (len > ASCII_SIZE) {
    for (c = 0; c < ASCII_SIZE; c++) {
      if (first_count[c] != second_count[c])
        return FALSE;
    }
  } else {
    int l;
    for (c = 0; c < len; c++) {
      l = first[c];
      if (first_count[l] != second_count[l])
        return FALSE;
    }
  }

  free (first_count);
  free (second_count);

  return TRUE;
}

bool
anagram (char *first, char *second)
{
  count++;

  if (count % 2 == 0)
    return anagram_by_sort (first, second);
  else
    return anagram_by_count (first, second);
}

int
main ()
{
  count = 0;

  char *a = "dad ";
  char *b = " add";
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  a = "troll";
  b = "hunter";
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  a = "same length ";
  b = "not the same";
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  a = "radar";
  b = "radar";
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
  printf ("%s:%s :: anagram? %s\n", a, b, anagram (a,
          b) ? "yes" : "no");
}

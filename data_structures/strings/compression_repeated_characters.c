/* Basic string compression using the counts of repeated characters.          */
/* For example the string aabccccaaa would become a5b1c4.                     */
/* If the 'compressed' string would not become smaller than the original      */
/* string, return the original string.                                        */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256

typedef enum
{ FALSE, TRUE } bool;

char *
compress_string (char *str, int len)
{
  int chars[ASCII_SIZE] = { 0 };

  int c;
  int nss = 0;
  for (c = 0; c < len; c++) {
    if (chars[str[c]] == 0) {   /* a new character */
      nss += 2;                 /* needs to spaces in the compressed str */
    }

    chars[str[c]]++;

    if (chars[str[c]] >= 10)    /* one more if a two digit number */
      nss++;
  }

  printf ("%d %d\n", nss, len);
  if (nss < len) {
    char tmp;
    char *new = (char *) malloc (nss * sizeof (char));

    int pos = 0;
    for (c = 0; c < ASCII_SIZE; c++) {
      if (chars[c] > 0) {
        new[pos++] = c;
        if (chars[c] < 10) {
          sprintf (&tmp, "%d", chars[c]);
          new[pos++] = tmp;
        } else {
          sprintf (&tmp, "%d", chars[c] / 10);
          new[pos++] = tmp;
          sprintf (&tmp, "%d", chars[c] % 10);
          new[pos++] = tmp;
        }
      }
    }
    new[pos] = '\0';

    return new;
  } else {
    return str;
  }
}


int
main ()
{
  char *test = "aabbbcddeeeeeeeeeeee";
  printf ("%s :: compressed :: %s\n", test, compress_string (test,
          strlen (test)));

  test = "abbccdde";
  printf ("%s :: compressed :: %s\n", test, compress_string (test,
          strlen (test)));

}

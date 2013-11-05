#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{FALSE, TRUE} bool;

char* reverse (char * str) {
  int len;
  for (len = 0; str[len]; len++) {
  }

  char * new = (char *) malloc (len * sizeof(char *));
  new[len] = 0;

  int c = 0;
  for (len--; len >= 0; len--) {
    new[c] = str[len];
    c++;
  }

  return new;
}

void reverse_in_place (char * str) {
  char* end = str;
  char tmp;
  if (str) {
    while (*end) {    /* find end of the string */
      end++;
    }
    end--;   /* set one char back, since last char is null */


    /* swap characters from start and end until pointers */
    /* meet in the middle */
    while (str < end) {
      tmp = *str;
      *str++ = *end;
      *end-- = tmp;
      str++;
    }
  }
}

int main ()
{
  char * test = "testing";
  printf("%s ", test);
  char * first = reverse(test);
  printf(":: %s\n", first);

  char * empty = "";
  printf("%s\n", reverse(empty));
}

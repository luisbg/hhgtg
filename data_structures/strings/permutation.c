#include <stdio.h>

typedef enum
{FALSE, TRUE} bool;

bool permutation (char * first, char * second) {
  if (!first || !second)
    return FALSE;

  int len_first = 0;
  int len_second = 0;
  while (first[len_first]) {
    len_first++;
  }

  while (second[len_second]) {
    len_second++;
  }

  if (len_first == 0 || len_first > len_second)
    return FALSE;

  int f;
  int s;
  for (s = 0; second[s]; s++) {
    for (f = 0; first[f] && first[f] == second[s]; f++) {
      s++;
    }

    if (!first[f]) {
      return TRUE;
    }
  }

  return FALSE;
}


int main() {
  char * first = "first";
  char * second = "we should find the first inside the second";

  printf("%s :: %s\npermutated %s\n", first, second,
         permutation(first, second)? "yes": "no");

  first = "first";
  second = "we shouldn't find it inside the second";

  printf("%s :: %s\npermutated %s\n", first, second,
         permutation(first, second)? "yes": "no");

  first = NULL;
  printf("%s :: %s\npermutated %s\n", first, second,
         permutation(first, second)? "yes": "no");

  first = "";
  printf("%s :: %s\npermutated %s\n", first, second,
         permutation(first, second)? "yes": "no");
}

/* Write a function that reverses the order of the words in a string. For
 * example, your function should transform the string “Do or do not, there is
 * no try.” to “try. no is there not, do or Do”. Assume that all words are space
 * delimited and treat punctuation the same as letters.
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  FALSE, TRUE
} bool;

bool reverse_order_words_elegant (char **phrase);
bool reverse_order_words_general (char **phrase);
static void copy_str_split (char *phrase, char **out, int c, int d, int start);
static void reverse_string (char **phrase, int start, int end);

bool
reverse_order_words_elegant (char **phrase)
{
  int c = 0, end = 0, size;

  while ((*phrase)[c] != '\0')
    c++;
  size = c;
  c = 0;

  reverse_string (phrase, c, size - 1); // revese the entire string

  while (end < size) {
    if ((*phrase)[end] != ' ') {        // start of word
      c = end;
      while (end < size && (*phrase)[end] != ' ')
        end++;

      end--;                    // go back to end of word and not the space
      reverse_string (phrase, c, end);  // reverse word back to original
    }

    end++;                      // advance to next token
  }

  return TRUE;
}

bool
reverse_order_words_general (char **phrase)
{
  int c, end, n_start, size;

  c = 0;
  while ((*phrase)[c] != '\0')
    c++;
  size = c;
  end = size - 1;
  n_start = 0;

  char *tmp = (char *) malloc ((size + 1) * sizeof (char));

  for (c = size - 1; c >= 0; c--) {
    if ((*phrase)[c] == ' ') {
      copy_str_split (*phrase, &tmp, c + 1, end, n_start);
      n_start += (end - c) + 1;
      end = c - 1;
    }
  }

  copy_str_split (*phrase, &tmp, 0, end, n_start);
  tmp[size] = '\0';

  *phrase = tmp;

  return TRUE;
}

static void
reverse_string (char **phrase, int start, int end)
{
  char tmp;
  while (end > start) {
    tmp = (*phrase)[start];
    (*phrase)[start] = (*phrase)[end];
    (*phrase)[end] = tmp;

    start++;
    end--;
  }
}

static void
copy_str_split (char *phrase, char **out, int c, int end, int pos)
{
  while (c <= end) {
    (*out)[pos++] = phrase[c++];
  }
  (*out)[pos] = ' ';
}


int
main ()
{
  char *phrase = (char *) malloc (30 * sizeof (char));
  char *tmp = "Do or do not, there is no try.";
  int c;
  for (c = 0; tmp[c] != '\0'; c++) {
    phrase[c] = tmp[c];
  }

  printf ("original: %s\n", phrase);
  reverse_order_words_elegant (&phrase);
  printf ("reversed: %s\n", phrase);

  return 0;
}

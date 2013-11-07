#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct linked_list
{                               /* has collision by separate chaining */
  char key[16];                 /* with head records in the bucket    */
  char word[32];                /* array                              */
  struct linked_list *next;
} linked_list;

typedef enum
{ FALSE, TRUE } bool;


int
hash (char *key)
{
  return key[0] % 16;
}

void
insert_list (linked_list * l, char key[], char word[])
{
  if (strcmp (l->key, "") == 0) {
    strcpy (l->key, key);
    strcpy (l->word, word);
    l->next = NULL;
  } else {
    while (l->next != NULL) {
      l = l->next;
    }

    linked_list *new_node;      /* temporary pointer */
    new_node = malloc (sizeof (linked_list));

    strcpy (new_node->key, key);
    strcpy (new_node->word, word);
    new_node->next = NULL;

    l->next = new_node;
  }

  printf ("inserted %s->%s\n", key, word);
}

char *
get_list (linked_list l, char *key)
{
  if (strcmp (l.key, key) == 0) {
    return l.word;
  } else {
    linked_list *pl = l.next;
    while (pl != NULL) {
      if (strcmp (pl->key, key) == 0) {
        return pl->word;
      }

      pl = pl->next;
    }
  }

  return "";
}

bool
insert_hash_table (linked_list * t, char key[], char word[])
{
  int h = hash (key);
  insert_list (&t[h], key, word);
}

char *
get_from_table (linked_list * t, char key[])
{
  int h = hash (key);
  return get_list (t[h], key);
}

int
main ()
{
  linked_list table[32] = { 0 };

  printf ("created table\n");

  insert_hash_table (table, "first", "work it");
  insert_hash_table (table, "second", "make it");
  /* skip third for testing getting onstored keys */
  insert_hash_table (table, "fourth", "make us");
  insert_hash_table (table, "fifth", "harder");
  insert_hash_table (table, "sixth", "better");
  insert_hash_table (table, "seventh", "faster");
  insert_hash_table (table, "eighth", "stronger");
  insert_hash_table (table, "ninth", "more than");
  insert_hash_table (table, "tenth", "hour");

  char *k = "first";
  printf ("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "second";
  printf ("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "third";
  if (get_from_table (table, k) == "")
    printf ("the key: %s -> isn't stored\n", k);
  k = "sixth";                  /* sixth collides with second */
  printf ("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "seventh";                /* seventh collides with second and sixth */
  printf ("the key: %s -> has word: %s \n", k, get_from_table (table, k));

  int c;
  for (c = 0; c < 32; c++) {
    if (strcmp (table[c].key, "") != 0) {
      printf ("table head records %d: %s->%s\n", c, table[c].key,
          table[c].word);
    }
  }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct linked_list {            /* has collision by separate chaining */
  char key[16];                         /* with head records in the bucket    */
  char word[32];                        /* array                              */
  struct linked_list * next;
} linked_list;

typedef enum
{ FALSE, TRUE} bool;


int hash(char * key) {
  return 5;
}

void insert_list (linked_list *l, char key[], char word[]) {
  if (strcmp(l->key, "") == 0) {
    strcpy(l->key, key);
    strcpy(l->word, word);
    l->next = NULL;
  } else {
    while (l->next != NULL) {
      l = l->next;
    }

    linked_list *new_node;                         /* temporary pointer */
    new_node = malloc(sizeof(linked_list));

    strcpy(new_node->key, key);
    strcpy(new_node->word, word);
    new_node->next = NULL;

    l->next = new_node;
  }

  printf("inserted %s->%s\n", key, word);
}

char * get_list (linked_list l, char * key) {
  if (strcmp(l.key, key) == 0) {
    return l.word;
  } else {
    linked_list *pl = l.next;
    while (pl != NULL) {
      if (strcmp(pl->key, key) ==0) {
        return pl->word;
      }

      pl = pl->next;
    }
  }

  return "";
}

bool insert_hash_table (linked_list *t, char key[], char word[]) {
  int h = hash(key);
  insert_list (&t[h], key, word);
}

char * get_from_table (linked_list *t, char key[]) {
  int h = hash(key);
  return get_list (t[h], key);
}

int main () {
  linked_list table[32] = {0};

  printf("created table\n");

  insert_hash_table (table, "first", "work it");
  insert_hash_table (table, "second", "make it");
  insert_hash_table (table, "fourth", "make us");
  insert_hash_table (table, "fifth", "harder");

  char *k = "first";
  printf("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "second";
  printf("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "third";
  printf("the key: %s -> has word: %s \n", k, get_from_table (table, k));
  k = "fifth";
  printf("the key: %s -> has word: %s \n", k, get_from_table (table, k));
}

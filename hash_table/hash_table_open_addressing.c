#include <stdio.h>

typedef enum
{FALSE, TRUE} bool;

typedef struct hash_table {            /* has collision by wrapping around to */
  int key[32];                         /* next free row                       */
  int content[32];
  bool used[32];
} hash_table;


int hash (int key) {
  return key % 32;
}

void insert (hash_table *t, int key, int cont) {
  printf("insert key: %d; content: %d\n", key, cont);

  int p = hash(key);
  while (t->used[p]) {
    p++;
    if (p == 32)
      p = 0;
  }

  t->key[p] = key;
  t->content[p] = cont;
  t->used[p] = TRUE;
}

int get (hash_table *t, int key) {
  int p = hash(key);
  while (t->key[p] != key) {
    p++;
    if (p == 32)
      p = 0;
  }

  return t->content[p];
}

int main () {
  hash_table t;
  int c;
  for (c = 0; c < 32; c++) {
    t.key[c] = 0;
    t.content[c] = 0;
    t.used[c] = FALSE;
  }

  /* no collisions block */
  insert(&t, 1, 100);
  insert(&t, 2, 200);
  insert(&t, 4, 400);
  insert(&t, 8, 800);
  insert(&t, 16, 1600);
  printf("\n");

  /* collisions block */
  insert(&t, 32, 3200);
  insert(&t, 64, 6400);
  insert(&t, 128, 12800);
  printf("\n");

  /* checks */
  printf("key: %d; content: %d\n", 2, get (&t, 2));
  printf("key: %d; content: %d\n", 8, get (&t, 4));
  printf("key: %d; content: %d\n", 16, get (&t, 16));
  printf("key: %d; content: %d\n", 32, get (&t, 32));
  printf("key: %d; content: %d\n", 64, get (&t, 64));
  printf("key: %d; content: %d\n", 128, get (&t, 128));
  printf("\n");

  /* show entire hash table contents */
  for (c = 0; c < 32; c++) {
    printf("row: %d; key: %d; content: %d\n", c, t.key[c], t.content[c]);
  }
}

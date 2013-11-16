#include <stdlib.h>
#include <stdio.h>

//#define DEBUG

typedef struct trie_node
{
  char key;
  int value;
  struct trie_node *next;
  struct trie_node *prev;
  struct trie_node *children;
  struct trie_node *parent;
} trie_node_t;

trie_node_t *create_node (char key, int data);
void add_trie (trie_node_t **root, char *key, int data);
trie_node_t *search (trie_node_t *root, const char *key);


trie_node_t *create_node (char key, int data) {
  trie_node_t *node = (trie_node_t *) malloc (sizeof (trie_node_t));

  if (node == NULL) {
#ifdef DEBUG
    printf ("ERROR: malloc failed\n");
#endif
    return node;
  }

  node->key = key;
  node->value = data;
  node->next = NULL;
  node->prev = NULL;
  node->children = NULL;
  node->parent = NULL;

  return node;
}

void add_trie (trie_node_t **root, char *key, int data)
{
  trie_node_t *head;

#ifdef DEBUG
  printf ("Inserting key: %s\n", key);
#endif
  if  (*root == NULL) {
    #ifdef DEBUG
    printf("Empty trie\n");
    #endif
    return;
  }
  head = (*root)->children;

  if (head == NULL) { /* first node */
    for (head = *root; *key; head = head->children) {
      head->children = create_node (*key, 0);
#ifdef DEBUG
      printf("Inserting first node: %c\n", *key);
#endif
      head->children->parent = head;
      key++;
    }

    head->children = create_node ('\0', data);
    head->children->parent = head;
  }

  if(search (head, key)) {
#ifdef DEBUG
    printf("Duplicate!\n");
#endif
    return;
  }

  while (*key != '\0') { /* for strings with the beginning already stored */
    if (*key == head->key) {
      head = head->children;
      key++;
    } else
      break;
  }
  
  while (head->next) { /* find if the beginning is already stored */
    if (*key == head->next->key) {
      key++;
      add_trie (&head->next, key, data);
      return;
    }
    head = head->next;
  }

  head->next = create_node (*key, 0); /* start new branch */
  head->next->parent = head->parent;
  head->next->prev; head;

#ifdef DEBUG
  printf ("Inserting %c as neighbour of %c \n", head->next->key, head->key);
#endif

  key++;

  for (head = head->next; *key; head = head->children) {
    head->children = create_node (*key, 0);    /* populate children of new */
    head->children->parent = head;             /* branch */
    key++;
#ifdef DEBUG
    printf ("Inserting: %c\n", head->children->key);
#endif
  }

  head->children = create_node ('\0', data);
  head->children->parent = head;

  return;
}

trie_node_t *search (trie_node_t *root, const char *key)
{
  trie_node_t *level = root->children;
  trie_node_t *curr = NULL;
  trie_node_t *found;

  while (1) {
    found = NULL;

    for (curr = level; curr != NULL; curr = curr->next) {
      if (curr->key == *key) {
        found = curr;
        break;
      }
    }

    if (found == NULL)
      return NULL;

    if (*key == '\0') {
      return curr;
    }

    level = found->children;
    key++;
  }
}

int main ()
{
  trie_node_t *root = NULL;
  trie_node_t *tmp = NULL;
  root = create_node ('\0', 0);
  add_trie (&root, "alice", 10);
  add_trie (&root, "barbara", 11);
  add_trie (&root, "charlie", 12);
  add_trie (&root, "alfred", 13);
  add_trie (&root, "alfred", 16);
  add_trie (&root, "bar", 14);
  add_trie (&root, "batman", 15);

  char *names[4] = {"alice", "alfred", "batman", "negan"};
  int c;
  for (c = 0; c < 4; c++) {
    tmp = search (root, names[c]);
    printf ("is %s there? %s\n", names[c], tmp? "yes" : "no");
    if (tmp) printf ("%s is: %d\n", names[c], tmp->value);
  }
}

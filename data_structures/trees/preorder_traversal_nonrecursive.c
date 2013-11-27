#include <stdlib.h>
#include <stdio.h>

typedef struct tree
{
  int key;
  struct tree *left;
  struct tree *right;
} tree;

typedef struct queue
{
  struct queue *next;
  struct tree *data;
} queue;

typedef enum
{
  FALSE, TRUE
} bool;


void insert (tree ** leaf, int key);
bool preorder_traverse (tree *t);
bool enqueue (queue **q, tree *node);
bool dequeue (queue **q, tree **node);


bool preorder_traverse (tree *t) {
  if (!t)
    return TRUE;
  
  queue *q = (queue *) malloc (sizeof (queue));
  tree *tmp = NULL;
  
  enqueue (&q, t);
  while (q) {
    dequeue (&q, &tmp);
    if (tmp) {
      printf ("%d -> ", tmp->key);
      if (tmp->right) {
        enqueue (&q, tmp->right);
      }
      if (tmp->left) {
        enqueue (&q, tmp->left);
      }
    }
  }

  printf ("\n"); 
 
  return TRUE;
}

bool enqueue (queue **t, tree *node)
{
  queue *new_element = (queue *) malloc (sizeof (queue));
  if (!new_element)
    return FALSE;
  new_element->data = node;
  new_element->next = NULL;

  if (*t)
    new_element->next = *t;

  *t = new_element;
  return TRUE;
}

bool dequeue (queue **t, tree **node)
{
  *node = (*t)->data;
  *t = (*t)->next;
}

/* insert a key into the tree */
void
insert (tree ** leaf, int key)
{
  if (!*leaf) {
    *leaf = (tree *) malloc (sizeof (tree));
    if (!*leaf)
      return;

    (*leaf)->key = key;
    (*leaf)->left = NULL;
    (*leaf)->right = NULL;

    return;
  }

  if (key < (*leaf)->key) {
    insert (&(*leaf)->left, key);

  } else {
    insert (&(*leaf)->right, key);
  }
}


int
main ()
{
  tree *root = NULL;

  insert (&root, 5);
  insert (&root, 2);
  insert (&root, 8);
  insert (&root, 1);
  insert (&root, 3);
  insert (&root, 4);
  insert (&root, 6);
  insert (&root, 9);
  insert (&root, 10);
  insert (&root, 7);

  printf ("pre-order traverse: ");
  preorder_traverse (root);
}

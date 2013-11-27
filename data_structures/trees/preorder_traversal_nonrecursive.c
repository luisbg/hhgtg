#include <stdlib.h>
#include <stdio.h>

typedef struct tree
{
  int key;
  struct tree *left;
  struct tree *right;
} tree;

typedef struct stack
{
  struct stack *next;
  struct tree *data;
} stack;

typedef enum
{
  FALSE, TRUE
} bool;


void insert (tree ** leaf, int key);
bool preorder_traverse (tree *t);
bool push (stack **q, tree *node);
bool pop (stack **q, tree **node);


bool preorder_traverse (tree *t) {
  if (!t)
    return TRUE;
  
  stack *q = (stack *) malloc (sizeof (stack));
  tree *tmp = NULL;
  
  push (&q, t);
  while (q) {
    pop (&q, &tmp);
    if (tmp) {
      printf ("%d -> ", tmp->key);
      if (tmp->right) {
        push (&q, tmp->right);
      }
      if (tmp->left) {
        push (&q, tmp->left);
      }
    }
  }

  printf ("\n"); 
 
  return TRUE;
}

bool push (stack **t, tree *node)
{
  stack *new_element = (stack *) malloc (sizeof (stack));
  if (!new_element)
    return FALSE;
  new_element->data = node;
  new_element->next = NULL;

  if (*t)
    new_element->next = *t;

  *t = new_element;
  return TRUE;
}

bool pop (stack **t, tree **node)
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

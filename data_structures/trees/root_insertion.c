#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;

typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} node;


node * root_insert_node (node ** leaf, int key);
static node * rotate_right (node **leaf);
static node * rotate_left (node **leaf);
bool validate_tree (struct node * leaf);
void show (node * leaf, int h);


/* insert a key into the tree */
node *
root_insert_node (node ** leaf, int key)
{
  printf ("node insert %d\n", key);
  node *run = *leaf;

  if (!run) {
    node *new_node = (node *) malloc (sizeof (node));

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    *leaf = new_node;
    return *leaf;
  }

  if (key < run->key) {
    run->left = root_insert_node (&run->left, key);
    run = rotate_right (&run);
  } else {
    run->right = root_insert_node (&run->right, key);
    run = rotate_left (&run);
  }

  return run;
}

static node *
rotate_right (node **leaf)
{
  node *run = *leaf;

  node *x = run->left;
  run->left = x->right;
  x->right = run;

  return x;
}

static node *
rotate_left (node **leaf)
{
  node *run = *leaf;

  node *x = run->right;
  run->right = x->left;
  x->left = run;

  return x;
}

bool
validate_tree (struct node * leaf)
{
  if (leaf) {
    if (leaf->left)
      if (leaf->key < leaf->left->key)
        return FALSE;
    if (leaf->right)
      if (leaf->key > leaf->right->key)
        return FALSE;

    if (!validate_tree (leaf->left))
      return FALSE;
    if (!validate_tree (leaf->right))
      return FALSE;
  }

  return TRUE;
}

void
print_node (int key, int h)
{
  int i;

  for (i = 0; i < h; i++)
    printf ("    ");

  printf ("%d\n", key);
}

void
show (node * leaf, int h)
{
  if (!leaf) {
    // print_node ('*', h);
    return;
  }

  show (leaf->right, h + 1);
  print_node (leaf->key, h);
  show (leaf->left, h + 1);
}

int
main ()
{
  node *root = NULL;

  root_insert_node (&root, 8);
  root_insert_node (&root, 10);
  root_insert_node (&root, 4);
  root_insert_node (&root, 6);
  root_insert_node (&root, 7);

  printf ("show tree:\n");
  show (root, 0);
  printf ("validated?: %s\n", validate_tree (root) ? "yes\n" : "no\n");

  root_insert_node (&root, 9);
  root_insert_node (&root, 5);
  root_insert_node (&root, 3);
  root_insert_node (&root, 1);
  root_insert_node (&root, 2);

  printf ("show tree:\n");
  show (root, 0);
  printf ("validated?: %s\n", validate_tree (root) ? "yes\n" : "no\n");

  return 0;
}

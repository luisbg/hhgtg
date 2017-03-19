/* Given the value of two nodes in a binary search tree, find the lowest
 * (nearest) common ancestor. You may assume that both values already
 * exist in the tree.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
  struct tree *left;
  struct tree *right;
  int value;
} tree;

typedef enum
{
  FALSE, TRUE
} bool;


bool has_node (tree * root, int value);
bool lowest_common_ancestor (tree * t, int val_a, int val_b, tree ** ancestor);
void add_to_tree (tree ** t, int value);


/* check if this node has val in the children tree */
bool
has_node (tree * root, int value)
{
  if (root == NULL)
    return FALSE;

  if (root->value == value)
    return TRUE;

  bool left = has_node (root->left, value);
  bool right = has_node (root->right, value);

  return (left || right);
}

/* find the lowest common ancestor of two values in a binary search tree */
bool
lowest_common_ancestor (tree * t, int val_a, int val_b, tree ** ancestor)
{
  if (t == NULL)
    return FALSE;

  tree *runner = t;
  while (runner) {
    if (has_node (runner->left, val_a) && has_node (runner->left, val_b))
      runner = runner->left;
    else if (has_node (runner->right, val_a) && has_node (runner->right, val_b))
      runner = runner->right;
    else {
      *ancestor = runner;
      break;
    }
  }

  return TRUE;
}

/* find the lowest common ancestor of two values in a binary search tree */
bool
lowest_common_ancestor_bts (tree * t, int val_a, int val_b, tree ** ancestor)
{
  int tree_val;

  while (t) {                   // loop until tree_val is split between < a and > b
    tree_val = t->value;

    if (tree_val > val_a && tree_val > val_b) {
      t = t->left;
    } else if (tree_val < val_a && tree_val < val_b) {
      t = t->right;
    } else {
      *ancestor = t;
      return TRUE;
    }
  }

  return FALSE;
}

/* add a value to the binary search tree */
void
add_to_tree (tree ** t, int value)
{
  tree *run = NULL;

  if (!*t) {
    tree *new_node = (tree *) malloc (sizeof (tree));
    if (!new_node)
      return;

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    *t = new_node;
    return;
  }

  run = *t;
  if (value <= run->value)
    add_to_tree (&run->left, value);
  else
    add_to_tree (&run->right, value);
}


int
main ()
{
  tree *t = NULL;
  tree *anc_f = NULL;
  tree *anc_s = NULL;
  int a, b;

  add_to_tree (&t, 20);

  add_to_tree (&t, 10);
  add_to_tree (&t, 30);

  add_to_tree (&t, 5);
  add_to_tree (&t, 15);


  add_to_tree (&t, 12);
  add_to_tree (&t, 13);
  add_to_tree (&t, 14);

  a = 5;
  b = 14;
  if (lowest_common_ancestor (t, 5, 14, &anc_f))
    printf ("lowest common ancestor of %d and %d: %d\n", a, b, anc_f->value);
  else
    printf ("values not found\n");

  a = 15;
  b = 12;
  if (lowest_common_ancestor (t, 15, 12, &anc_f))
    printf ("lowest common ancestor of %d and %d: %d\n", a, b, anc_f->value);
  else
    printf ("values not found\n");

  a = 5;
  b = 30;
  if (lowest_common_ancestor_bts (t, 5, 30, &anc_s))
    printf ("lowest common ancestor of %d and %d: %d\n", a, b, anc_s->value);
  else
    printf ("values not found\n");

  return 0;
}

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

typedef struct queue_t
{
  struct queue_t *next;
  struct tree *data;
} queue_t;

typedef enum
{
  FALSE, TRUE
} bool;


bool lowest_common_ancestor (tree * t, int val_a, int val_b, tree ** ancestor);
bool common_path (queue_t * pa, queue_t * pb, tree ** common);
bool add_to_tree (tree ** t, int value);
bool enqueue (queue_t ** t, tree * node);
bool dequeue (queue_t ** t, tree ** node);
void print_queue (queue_t * t);


bool
lowest_common_ancestor (tree * t, int val_a, int val_b, tree ** ancestor)
{
  queue_t *path_to_a = NULL;
  queue_t *path_to_b = NULL;
  tree *run = t;

  while (run) {
    enqueue (&path_to_a, run);

    if (run->value == val_a)
      break;

    if (val_a < run->value)
      run = run->left;
    else
      run = run->right;
  }

  run = t;
  while (run) {
    enqueue (&path_to_b, run);

    if (run->value == val_b)
      break;

    if (val_b < run->value)
      run = run->left;
    else
      run = run->right;
  }

  print_queue (path_to_a);
  print_queue (path_to_b);

  common_path (path_to_a, path_to_b, ancestor);
  return TRUE;
}

bool
common_path (queue_t * pa, queue_t * pb, tree ** common)
{
  tree *tmp_a, *tmp_b;
  *common = NULL;

  dequeue (&pa, &tmp_a);
  dequeue (&pb, &tmp_b);

  while (tmp_a->value == tmp_b->value) {
    *common = tmp_a;

    dequeue (&pa, &tmp_a);
    dequeue (&pb, &tmp_b);
  }

  return TRUE;
}

bool
enqueue (queue_t ** t, tree * node)
{
  // printf ("enq: %d\n", node->value);

  queue_t *run = *t;
  queue_t *new_element = (queue_t *) malloc (sizeof (queue_t));
  new_element->data = node;
  new_element->next = NULL;

  if (!*t) {
    *t = new_element;
    return TRUE;
  }

  while (run->next)
    run = run->next;

  run->next = new_element;;
  return TRUE;
}

bool
dequeue (queue_t ** t, tree ** node)
{
  if (!*t)
    return FALSE;

  *node = (*t)->data;
  *t = (*t)->next;

  // printf ("deq: %d\n", (*node)->value);
  return TRUE;
}

void
print_queue (queue_t * t)
{
  printf ("print queue: ");

  while (t) {
    printf ("%d: ", t->data->value);
    t = t->next;
  }
  printf ("\n");
}

bool
add_to_tree (tree ** t, int value)
{
  tree *run = NULL;

  if (!*t) {
    tree *new_node = (tree *) malloc (sizeof (tree));
    if (!new_node)
      return FALSE;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    *t = new_node;
    return TRUE;
  }

  run = *t;
  if (value <= run->value) {
    add_to_tree (&run->left, value);
  } else {
    add_to_tree (&run->right, value);
  }
}


int
main ()
{
  tree *t = NULL;
  tree *anc = NULL;
  add_to_tree (&t, 20);

  add_to_tree (&t, 8);
  add_to_tree (&t, 22);

  add_to_tree (&t, 4);
  add_to_tree (&t, 12);


  add_to_tree (&t, 10);
  add_to_tree (&t, 14);

  if (lowest_common_ancestor (t, 4, 14, &anc))
    printf ("lowest common ancestor: %d\n", anc->value);
  else
    printf ("values not found\n");

  return 0;
}

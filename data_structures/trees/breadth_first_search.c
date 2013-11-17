#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;

typedef struct tree_node
{
  int key;
  struct tree_node *left;
  struct tree_node *right;
} tree_node;

typedef struct queue_node
{
  tree_node *data;
  struct queue_node *next;
} queue_node;

typedef struct queue
{
  queue_node *head;
  queue_node *last;
} queue;


void tree_insert (tree_node ** leaf, int key);
void tree_traverse (tree_node * leaf);
static void enqueue (queue * q, tree_node * data);
static tree_node *dequeue (queue * q);
void breadth_first_traverse (tree_node * leaf);
tree_node *breadth_first_search (tree_node * leaf, int key);


/* insert a key into the tree */
void
tree_insert (tree_node ** leaf, int key)
{
  if (*leaf == NULL) {
    *leaf = (tree_node *) malloc (sizeof (tree_node));
    (*leaf)->key = key;

    (*leaf)->left = NULL;
    (*leaf)->right = NULL;

  } else if (key < (*leaf)->key) {
    tree_insert (&(*leaf)->left, key);

  } else if (key > (*leaf)->key) {
    tree_insert (&(*leaf)->right, key);
  }
}

void
tree_traverse (tree_node * leaf)
{
  if (leaf != NULL) {
    tree_traverse (leaf->left);
    printf ("%d .", leaf->key);
    tree_traverse (leaf->right);
  }
}

static void
enqueue (queue * q, tree_node * data)
{
  queue_node *new = (queue_node *) malloc (sizeof (queue_node));
  new->data = data;
  new->next = NULL;

  if (q->head != NULL) {
    q->last->next = new;
    q->last = new;
  } else {
    q->head = new;
    q->last = new;
  }
}

static tree_node *
dequeue (queue * q)
{
  tree_node *dq = NULL;

  if (q->head != NULL) {
    dq = q->head->data;
    q->head = q->head->next;
  }

  return dq;
}

void
breadth_first_traverse (tree_node * leaf)
{
  queue tmp_q;                  // temporary queue
  tmp_q.head = NULL;
  tmp_q.last = NULL;
  tree_node *traverse = NULL;   // points to node we are processing

  if (leaf == NULL)
    return;                     // nothing to traverse

  enqueue (&tmp_q, leaf);       // put something in the queue initially

  while (tmp_q.head != NULL) {
    traverse = dequeue (&tmp_q);
    printf ("%d ", traverse->key);

    if (traverse->left != NULL)
      enqueue (&tmp_q, traverse->left);
    if (traverse->right != NULL)
      enqueue (&tmp_q, traverse->right);
  }

  printf ("\n");
}

tree_node *
breadth_first_search (tree_node * leaf, int key)
{
  queue tmp_q;
  tmp_q.head = NULL;
  tmp_q.last = NULL;
  tree_node *traverse = NULL;

  if (leaf == NULL)
    return;

  enqueue (&tmp_q, leaf);

  while (tmp_q.head != NULL) {
    traverse = dequeue (&tmp_q);
    if (traverse->key == key)
      return traverse;

    if (traverse->left != NULL)
      enqueue (&tmp_q, traverse->left);
    if (traverse->right != NULL)
      enqueue (&tmp_q, traverse->right);
  }

  return NULL;
}


int
main ()
{
  tree_node *root = NULL;

  int values[10] = { 5, 2, 8, 1, 3, 4, 6, 9, 10, 7 };
  int c;
  for (c = 0; c < 10; c++) {
    printf ("insert: %d\n", values[c]);
    tree_insert (&root, values[c]);
  }

  printf ("in-order traverse: ");
  tree_traverse (root);
  printf ("\n");

  printf ("breadth first traverse: ");
  breadth_first_traverse (root);

  for (c = -2; c < 14; c += 3) {
    printf ("%d found? %s\n", c, (breadth_first_search (root,
                c)) ? "yes" : "no");
  }

  return 0;
}

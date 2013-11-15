#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} node;

typedef enum
{
  FALSE, TRUE
} bool;

bool visit[10] = { 0 };

void insert (node ** leaf, int key);
void traverse (node * leaf);
void depth_first_traverse (node * leaf);
bool depth_first_search (node * leaf, int key);
static bool visited (node * leaf);

/* insert a key into the tree */
void
insert (node ** leaf, int key)
{
  if (*leaf == NULL) {
    *leaf = (node *) malloc (sizeof (node));
    (*leaf)->key = key;

    (*leaf)->left = NULL;
    (*leaf)->right = NULL;

  } else if (key < (*leaf)->key) {
    insert (&(*leaf)->left, key);

  } else if (key > (*leaf)->key) {
    insert (&(*leaf)->right, key);
  }
}

void
traverse (node * leaf)
{
  if (leaf != NULL) {
    traverse (leaf->left);
    printf ("%d .", leaf->key);
    traverse (leaf->right);
  }
}

void
depth_first_traverse (node * leaf)
{
  if (!visited (leaf)) {
    printf ("%d .", leaf->key);
    depth_first_traverse (leaf->left);
    depth_first_traverse (leaf->right);
  }
}

bool
depth_first_search (node * leaf, int key)
{
  if (!visited (leaf)) {
    if (leaf->key == key)
      return TRUE;

    depth_first_search (leaf->left, key);
    depth_first_search (leaf->right, key);
  }
}

static bool
visited (node * leaf)
{
  if (leaf != NULL) {
    int c = leaf->key;

    if (!visit[c]) {
      visit[c] = TRUE;
      return FALSE;
      }
  }

  return TRUE;
}

int
main ()
{
  node *root = NULL;

  int c;
  for (c = 0; c < 10; c++) {
    visit[c] = FALSE;
  }

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

  printf ("in-order traverse: ");
  traverse (root);
  printf ("\n");

  printf ("depth first traverse: ");
  depth_first_traverse (root);
  printf ("\n");

  printf ("depth first search: ");
  printf ("%d %s\n", 5, depth_first_search (root, 5) ? "found" : "not found");
}
